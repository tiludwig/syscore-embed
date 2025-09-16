#pragma once

template <class T>
class LockGuard
{
public:
    LockGuard(T& mutex)
        : m_mutex{&mutex}
    {
        m_mutex->lock();
    }

    ~LockGuard()
    {
        m_mutex->unlock();
    }
private:
    T* m_mutex = nullptr;
};