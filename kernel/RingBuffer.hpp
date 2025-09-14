#pragma once

#include <array>
#include <cstddef>
#include "Atomic.hpp"

template <class T, std::size_t CAPACITY>
class RingBuffer
{
public:
    // Push returns false if buffer is full
    bool push(const T& item) {
        if (full())
            return false;

        auto wrIdx = m_writeIdx.load();
        m_buffer[wrIdx % CAPACITY] = item;
        m_writeIdx.store(wrIdx + 1);

        return true;
    }

    // Pop returns false if buffer is empty
    bool pop(T& out)
    {
        if (empty())
            return false;

        auto rdIdx = m_readIdx.load();
        out = m_buffer[rdIdx % CAPACITY];
        m_readIdx.store(rdIdx + 1);
        
        return true;
    }

    bool empty() const
    {
        auto rdIdx = m_readIdx.load();
        auto wrIdx = m_writeIdx.load();

        return rdIdx == wrIdx;
    }

    bool full() const
    {
        auto rdIdx = m_readIdx.load();
        auto wrIdx = m_writeIdx.load();

        return ((wrIdx - rdIdx) >= CAPACITY);
    }

    T* peek() {
        if (empty())
            return nullptr;

        return &m_buffer[m_readIdx.load() % CAPACITY];
    }

    std::size_t size() const {
        return m_writeIdx.load() - m_readIdx.load();
    }

    constexpr std::size_t capacity() const { return CAPACITY; }

private:
    std::array<T, CAPACITY> m_buffer;
    AtomicVar<std::size_t> m_writeIdx = 0;
    AtomicVar<std::size_t> m_readIdx = 0;
};