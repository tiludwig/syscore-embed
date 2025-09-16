#pragma once

#include <cstdint>

struct SemaphoreData;

class Semaphore
{
public:
    Semaphore();
    Semaphore(uint32_t count);

    ~Semaphore();

    Semaphore(const Semaphore&) = delete;
    Semaphore(Semaphore&&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;
    Semaphore& operator=(Semaphore&&) = delete;

    void reset(uint32_t count);

    bool signal();
    bool wait();
    bool wait(uint32_t timeout);
private:
    SemaphoreData* m_data;
};
