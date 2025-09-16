target_sources(syscore 
    PUBLIC 
        FILE_SET kernel_headers
        TYPE HEADERS
        FILES
            Semaphore.hpp
            Mutex.hpp
            LockGuard.hpp
)

add_subdirectory(win32)