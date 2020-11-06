#include "../../Headers/TcpPacket.hpp"
TcpPacket::TcpPacket(uint32_t sender, uint32_t destination, std::string message, unsigned size) 
        : senders_address_(sender), destination_address_(destination), message_(message), size_(size), received_(false) {}

uint32_t TcpPacket::GetDestination() {
        return destination_address_;
} /*For sure 4bytes we will use adresses*/
uint32_t TcpPacket::GetDestinationMac() {
        return destination_mac_;
}
uint32_t TcpPacket::GetSendersMac() {
        return 0;
}
size_t TcpPacket::GetSize() {
        return size_;
}
std::string TcpPacket::GetMessage() {
        return message_;
}
bool TcpPacket::Handshake(uint32_t) {
        received_ = true;
}