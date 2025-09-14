target_sources(syscore 
    PRIVATE 
        FILE_SET kernel_headers
        TYPE HEADERS
        FILES
            Semaphore.hpp
            Mutex.hpp
            Queue.hpp
            RingBuffer.hpp
            Atomic.hpp
)