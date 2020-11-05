#ifndef TCPPACKET_HPP
#define TCPPACKET_HPP
#include "Packet.hpp"
class TcpPacket : public Packet {
public:
        uint32_t GetDestination(); /*For sure 4bytes we will use adresses*/
        uint32_t GetDestinationMac();
        uint32_t GetSendersMac();
        size_t GetSize();
        std::string GetMessage();
        bool Handshake(uint32_t);
private:
        unsigned size_;
        uint32_t senders_mac_;
        uint32_t destination_mac_; 
        uint32_t senders_address_;
        uint32_t destinatio_address_;
        bool recieved_;
}; 
#endif //TCPPACKET_HPP
