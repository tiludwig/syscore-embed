target_sources(syscore 
    PRIVATE 
        FILE_SET kernel_headers
        TYPE HEADERS
        FILES
            Semaphore.hpp
            Mutex.hpp
            LockGuard.hpp
)

add_subdirectory(win32)