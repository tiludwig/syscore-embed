#include "w5300.hpp"

namespace vendor
{
uint32_t sendto(int ch, const uint8_t* data, uint16_t len, const uint8_t* ip, uint16_t port);
uint16_t getIR();
void setIR(uint16_t value);

uint8_t getSn_IR(uint8_t sock);
void setSn_IR(uint8_t sock, uint8_t value);
}  // namespace vendor

namespace wiznet
{

void w5300::interruptHandler()
{
    // read and acknowledge device interrupt
    uint16_t ir = vendor::getIR();
    vendor::setIR(ir);

    while (ir != 0) {
        for (size_t i = 0; i < m_hw_channels.size(); i++) {
            channelInterruptHandler(i);
        }

        // re-read the interrupt status register in case new interrupts happened
        uint16_t ir = vendor::getIR();
        vendor::setIR(ir);  // acknowledge those interrupts as well
    }
}

void w5300::channelInterruptHandler(uint8_t hwChannel)
{
    // read and acknowledge channel interrupt
    uint8_t snIR = vendor::getSn_IR(hwChannel);
    vendor::setSn_IR(hwChannel, snIR);

    // remember the interrupt for defered processing
    m_hw_channels[hwChannel].pending_irq |= snIR;
}

int w5300::init(int pin, const mac& mac_addr, const ip_config& ip_cfg)
{
    if (m_initialized)
        return -1;  //

    // set initialized to true to guard against reinitialization
    m_initialized = true;

    // store configuration
    m_pin = pin;
    m_mac_addr = mac_addr;
    m_ip_config = ip_cfg;

    // reset the wiznet
    reset();

    return 0;
}

int w5300::reset()
{
    // Todo: loop over all channels and close them
    return -1;
}

int w5300::create_udp_channel()
{
    for (size_t i = 0; i < m_hw_channels.size(); i++) {
        if (m_hw_channels[i].state == ChannelState::CLOSED) {
            // Todo: set registers in order to open channel
            m_hw_channels[i].state = ChannelState::OPEN;
            m_hw_channels[i].pending_irq = 0;
            return i;
        }
    }

    return -1;
}

int w5300::close(int ch)
{
    if (!isValidChannel(ch))
        return -1;

    // Todo: set registers to close channel
    return 0;
}

int w5300::bind(int ch, uint16_t port)
{
    if (!isValidChannel(ch))
        return -1;

    // Todo: set registers to bind channel to port
    return 0;
}

int w5300::sendto(int ch, const uint8_t* data, uint16_t len, const ipv4& ip, uint16_t port)
{
    if (!isValidChannel(ch))
        return -1;

    w5300_tx_data new_tx_data;
    new_tx_data.data = data;
    new_tx_data.end = data + len;
    new_tx_data.dstIP = ip;
    new_tx_data.dstPort = port;
    new_tx_data.len = len;

    // put into tx queue (will block until successfuly enqueue new tx data)
    m_hw_channels[ch].txQueue.enqueue(new_tx_data);

    // wait for tx complete. This only works, because the tx queue has a capacity of one.
    // otherwise we need to have one semaphore per queue slot
    m_hw_channels[ch].txDoneSemaphore.wait();

    return len;
}


}  // namespace wiznet
