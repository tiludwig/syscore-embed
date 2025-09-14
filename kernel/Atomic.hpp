#pragma once

#include <cstddef>
#define ATOMIC_SECTION_BEGIN();
#define ATOMIC_SECTION_END();

template <class T>
class AtomicVar
{
public:
    AtomicVar() = default;
    AtomicVar(const T & v) : m_value{v} {}

    inline void store(const T& v)
    {
        ATOMIC_SECTION_BEGIN();
        m_value = v;
        ATOMIC_SECTION_END();
    }

    inline T load() const
    {
        ATOMIC_SECTION_BEGIN();
        T tmp = m_value;
        ATOMIC_SECTION_END();

        return tmp;
    }

private:
    volatile T m_value;
};

template <>
class AtomicVar<std::size_t>
{
public:
    AtomicVar() = default;
    AtomicVar(const std::size_t & v) : m_value{v} {}

    inline void store(const std::size_t& v)
    {
        m_value = v;
    }

    inline std::size_t load() const
    {
        return m_value;
    }

private:
    volatile std::size_t m_value;
};
