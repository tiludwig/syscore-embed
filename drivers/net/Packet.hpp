#pragma once

#include <array>
#include <cstdint>

namespace net
{

using IPv4 = std::array<std::uint8_t, 4>;

template <std::uint16_t N>
struct Packet
{
    static constexpr std::uint16_t CAPACITY = N;

    IPv4 ip;
    std::uint16_t port;
    std::uint16_t len;
    alignas(std::uint16_t) std::uint8_t buffer[N];
};

}
