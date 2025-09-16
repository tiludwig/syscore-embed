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

}  // namespace wiznet
