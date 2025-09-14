target_sources(syscore 
    PRIVATE 
        FILE_SET w5300_headers
        TYPE HEADERS
        FILES w5300.hpp
    PRIVATE
        w5300.cpp
)
