#pragma once

#include <cstdint>
#include <cstring>
#include "kernel/Semaphore.hpp"
#include "Packet.hpp"

namespace net
{

template <class T>
class PacketQueue;

template <std::uint16_t N>
class PacketQueue<Packet<N>>
{
public:
    using PacketType = Packet<N>;

    ~PacketQueue()
    {
        if (m_buffer != nullptr)
            delete [] m_buffer;
    }

    bool create(std::size_t capacity)
    {
        if (m_buffer != nullptr)
            return false;

        m_head = 0;
        m_tail = 0;
        m_capacity = capacity;
        m_buffer = new (std::nothrow) PacketType[capacity];
        if (m_buffer == nullptr)
            return false;

        // set free slots to capacity and available items to 0
        m_semAvailableItems.reset(0);
        m_semFreeSlots.reset(capacity);
        return true;
    }

    bool enqueue(const std::uint8_t* data, std::uint16_t len, const IPv4& ip, std::uint16_t port)
    {
        if (data == nullptr)
            return false;
    
        if (len >= PacketType::CAPACITY)
            return false;

        m_semFreeSlots.wait();
        std::size_t idx = m_head % m_capacity;
        m_head = m_head + 1;
        
        m_buffer[idx].ip = ip;
        m_buffer[idx].port = port;
        m_buffer[idx].len = len;
        std::memcpy(m_buffer[idx].buffer, data, len);

        m_semAvailableItems.signal();
        return true;
    }

    bool dequeue(std::uint8_t* buffer, std::uint16_t& len, IPv4& ip, std::uint16_t& port)
    {
        if (buffer == nullptr)
            return false;

        m_semAvailableItems.wait();
        std::size_t idx = m_tail % m_capacity;
        m_tail = m_tail + 1;

        std::uint16_t bytesToCopy = std::min(len, m_buffer[idx].len);

        ip = m_buffer[idx].ip;
        port = m_buffer[idx].port;
        len = bytesToCopy;
        std::memcpy(buffer, m_buffer[idx].buffer, bytesToCopy);

        m_semFreeSlots.signal();
        return true;
    }

    PacketType* peek()
    {
        // try wait for any items to become available. Will not block.
        if (m_head == m_tail)
            return nullptr;

        std::size_t idx = m_tail % m_capacity;
        return &m_buffer[idx];
    }

    void remove()
    {
        m_semAvailableItems.wait();
        m_tail = m_tail + 1;
        m_semFreeSlots.signal();
    }

    PacketType* reserve()
    {
        // wait for free slot
        m_semFreeSlots.wait();

        // reserve the slot
        std::size_t idx = m_head % m_capacity;
        m_head = m_head + 1;

        // do not commit the slot yet
        return &m_buffer[idx];
    }

    void commit()
    {
        m_semAvailableItems.signal();
    }

private:
    Semaphore m_semFreeSlots;
    Semaphore m_semAvailableItems;

    std::size_t m_head = 0;
    std::size_t m_tail = 0;
    std::size_t m_capacity = 0;
    PacketType* m_buffer = nullptr;
};

}