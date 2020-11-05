#ifndef TCPPACKET_HPP
#define TCPPACKET_HPP
#include "Packet.hpp"
class TcpPacket : public Packet {
private:
        unsigned size_;
        uint32_t senders_mac_;
        uint32_t destination_mac_; 
        uint32_t senders_address_;
        uint32_t destinatio_address_;
        bool recieved_;
}; 
#endif //TCPPACKET_HPP
