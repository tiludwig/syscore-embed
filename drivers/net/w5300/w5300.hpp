#pragma once

#include <array>
#include <cstdint>
#include "Queue.hpp"

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

enum class ChannelState
{
    CLOSED,
    OPEN,
    BOUND,
};

struct w5300_tx_data
{
    const uint8_t* data = nullptr;
    const uint8_t* end = nullptr;
    uint16_t len = 0;
    uint16_t dstPort = 0;
    ipv4 dstIP = {0,0,0,0};

    void clear()
    {
        data = nullptr;
        end = nullptr;
        len = 0;
        dstPort = 0;
        dstIP = {0,0,0,0};
    }
};

struct w5300_rx_data
{

};

struct w5300_channel
{
    ChannelState state = ChannelState::CLOSED;
    
    Queue<w5300_tx_data, 1> txQueue;
    Queue<w5300_rx_data, 8> rxQueue;

    volatile uint8_t pending_irq = 0;
    sem_t txDoneSemaphore;
};

class w5300
{
public:
    int init(int pin, const mac& mac_addr, const ip_config& ip_cfg);
    int reset();

    int create_udp_channel();
    int close(int ch);
    int bind(int ch, uint16_t port);
    int sendto(int ch, const uint8_t* data, uint16_t len, const ipv4& ip, uint16_t port);
    int recvfrom(int ch, uint8_t* buffer, uint16_t len, ipv4* ip, uint16_t* port);

    void interruptHandler();
    void loop();

private:
    bool isValidChannel(int channel) const;
    int sendNextChunk(uint8_t hwChannel, w5300_tx_data& tx_data);
    void channelInterruptHandler(uint8_t hwChannel);
    void channelDeferedHandler(uint8_t hwChannel);
    void channelTxCompleteHandler(uint8_t hwChannel);
    void channelHwTimeoutHandler(uint8_t hwChannel);
    void channelRxReadyHandler(uint8_t hwChannel);

    bool m_initialized = false;
    int m_pin = -1;

    std::array<w5300_channel, 8> m_hw_channels;
    mac m_mac_addr;
    ip_config m_ip_config;

    sem_t m_driver_sem;
};

}  // namespace wiznet
