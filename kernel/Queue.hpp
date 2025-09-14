#pragma once

#include <cstddef>
#include "RingBuffer.hpp"
#include "Semaphore.hpp"

template <class T, std::size_t CAPACITY>
class Queue
{
public:
    Queue() : m_semAvailableItems{0}, m_semFreeSlots{CAPACITY} {}

    bool enqueue(const T& item)
    {
        m_semFreeSlots.wait();         // wait for free slot
        m_buffer.push(item);           // guaranteed to succeed
        m_semAvailableItems.signal();  // signal new item
        return true;
    }

    bool dequeue(T& item)
    {
        m_semAvailableItems.wait();  // wait for item
        m_buffer.pop(item);          // guaranteed to succeed
        m_semFreeSlots.signal();     // signal free slot
        return true;
    }

    T* peek()
    {
        return m_buffer.peek();
    }

    std::size_t size() const { return m_buffer.size(); }
    constexpr std::size_t capacity() const { return CAPACITY; }

private:
    RingBuffer<T, CAPACITY> m_buffer;
    sem_t m_semAvailableItems;
    sem_t m_semFreeSlots;
};
