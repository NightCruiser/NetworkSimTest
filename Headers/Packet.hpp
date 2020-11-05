#ifndef PACKET_HPP
#define PACKET_HPP
#include <cstdint>
class Packet {
public:
        virtual ~Packet() {}
        virtual uint32_t GetDestination() = 0; /*For sure 4bytes we will use adresses*/
        virtual bool Handshake(uint32_t) = 0;
};
#endif //PACKET_HPP