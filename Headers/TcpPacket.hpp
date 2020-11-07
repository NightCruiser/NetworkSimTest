#ifndef TCPPACKET_HPP
#define TCPPACKET_HPP
#include "Packet.hpp"
#include <mutex>
class TcpPacket : public Packet {
public:
        TcpPacket(uint32_t, uint32_t, std::string, unsigned);
        uint32_t GetDestination(); /*For sure 4bytes we will use adresses*/
        uint32_t GetDestinationMac();
        uint32_t GetSendersMac();
        unsigned GetSize();
        std::string GetMessage();
        bool Handshake(uint32_t);
        bool GetDeliveryStatus();
private:
        uint32_t senders_address_;
        uint32_t destination_address_;
        std::string message_;
        unsigned size_;
        uint32_t senders_mac_;
        uint32_t destination_mac_; 
        bool received_;
        std::mutex packet_mtx_;
}; 
#endif //TCPPACKET_HPP
