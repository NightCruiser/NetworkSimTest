#ifndef PACKET_HPP
#define PACKET_HPP
#include <cstdint>
#include <string>
/**
 * Packet class represents a simple packet
 * */
class Packet {
public:
        virtual ~Packet() {}
        virtual uint32_t GetDestination() = 0; /*For sure 4bytes we will use adresses*/
        virtual uint32_t GetDestinationMac() = 0;
        virtual uint32_t GetSendersMac() = 0;
        virtual unsigned GetSize() = 0;
};
#endif //PACKET_HPP