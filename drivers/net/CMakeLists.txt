
target_sources(syscore 
    PRIVATE 
        FILE_SET net_headers
        TYPE HEADERS
        FILES 
            Packet.hpp
            PacketQueue.hpp
)


add_subdirectory(w5300)