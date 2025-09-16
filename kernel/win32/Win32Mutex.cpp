#include <Windows.h>
#include <synchapi.h>
#include "Mutex.hpp"

struct MutexData
{
    HANDLE hMutex = NULL;;
};

Mutex::Mutex()
{
    m_data = new MutexData();
    m_data->hMutex = CreateMutex(NULL, FALSE, NULL);
}

Mutex::~Mutex()
{
    if (m_data->hMutex != NULL)
        CloseHandle(m_data->hMutex);

    delete m_data;
}

void Mutex::lock()
{
    WaitForSingleObject(m_data->hMutex, INFINITE);
}

void Mutex::unlock()
{
    ReleaseMutex(m_data->hMutex);
}
