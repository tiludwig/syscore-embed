#pragma once

#include <array>
#include <cstdint>

namespace wiznet
{

using ipv4 = std::array<std::uint8_t, 4>;
using maskv4 = std::array<std::uint8_t, 4>;
using mac = std::array<std::uint8_t, 8>;

struct ip_config
{
    ipv4 ip_addr = {0,0,0,0};
    maskv4 subnet = {0,0,0,0};
    ipv4 gateway = {0,0,0,0};
};

class w5300
{

};

}  // namespace wiznet
