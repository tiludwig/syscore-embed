
#include <Windows.h>
#include <handleapi.h>
#include <synchapi.h>
#include <winbase.h>
#include "kernel/Semaphore.hpp"

struct SemaphoreData
{
    HANDLE hSemaphore = NULL;
};

Semaphore::Semaphore()
    : Semaphore(0)
{
}

Semaphore::Semaphore(uint32_t count)
{
    m_data = new SemaphoreData();
    reset(count);
}

Semaphore::~Semaphore()
{
    CloseHandle(m_data->hSemaphore);
    delete m_data;
}

void Semaphore::reset(uint32_t count)
{
    if (m_data->hSemaphore != NULL)
        CloseHandle(m_data->hSemaphore);

    m_data->hSemaphore = CreateSemaphore(NULL, count, INFINITE, NULL);
}

bool Semaphore::signal()
{
    return ReleaseSemaphore(m_data->hSemaphore, 1, NULL);
}

bool Semaphore::wait()
{
    DWORD result = WaitForSingleObject(m_data->hSemaphore, INFINITE);
    if (result != WAIT_OBJECT_0)
        return false;

    return true;
}

bool Semaphore::wait(uint32_t timeout)
{
    DWORD result = WaitForSingleObject(m_data->hSemaphore, timeout);
    if (result != WAIT_OBJECT_0)
        return false;

    return true;
}