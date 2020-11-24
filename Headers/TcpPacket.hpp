#ifndef TCPPACKET_HPP
#define TCPPACKET_HPP
#include "Packet.hpp"

/**
 * TcpPacket Class represents a simple packet for now
 * In the future might be extended
 * */

class TcpPacket : public Packet {
public:
        TcpPacket(uint32_t, uint32_t, unsigned);
        uint32_t GetDestination(); /*For sure 4bytes we will use adresses*/
        uint32_t GetDestinationMac();
        uint32_t GetSendersMac();
        unsigned GetSize();
private:
        uint32_t senders_address_;
        uint32_t destination_address_;
        unsigned size_;
        uint32_t senders_mac_;
        uint32_t destination_mac_; 
        bool received_;
}; 
#endif //TCPPACKET_HPP
