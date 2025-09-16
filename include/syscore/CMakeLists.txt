target_sources(syscore 
    PUBLIC 
        FILE_SET pub_kernel_headers
        TYPE HEADERS
        FILES
            kernel/Semaphore.hpp
            kernel/Mutex.hpp
            kernel/LockGuard.hpp
)
