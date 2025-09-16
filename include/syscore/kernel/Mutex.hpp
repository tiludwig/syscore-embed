#pragma once

struct MutexData;

class Mutex
{
public:
    Mutex();
    ~Mutex();

    Mutex(const Mutex&) = delete;
    Mutex(Mutex&&) = delete;
    Mutex& operator=(const Mutex&) = delete;
    Mutex& operator=(Mutex&&) = delete;

    void lock();
    void unlock();
private:
    MutexData* m_data = nullptr;
};