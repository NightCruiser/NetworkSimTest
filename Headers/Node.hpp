#ifndef NODE_HPP
#define NODE_HPP
#include <utility>
#include <list>
#include <string>
#include <memory>
#include "Channel.hpp"
class Node {
public:
        virtual ~Node() {}
        virtual bool RecievePacket() = 0;
        virtual bool RecievePacket(std::shared_ptr<Packet>) = 0;
        virtual bool Start() = 0;
        virtual bool SendPacket(uint32_t, std::shared_ptr<Packet>) = 0;
        virtual bool RequestConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>) = 0; /*Here the connection initiator should specify recieve/transmit queues of channel*/
        virtual bool ApproveConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>) = 0;
        virtual bool GeneratePacket() = 0;
        virtual uint32_t RequestAddressesFromDhcp() = 0;
        virtual uint32_t CastAddresses() = 0;
        virtual bool SetAddress(uint32_t) = 0;
        virtual bool SetGateway(uint32_t) = 0;
        virtual uint32_t GetAddress() = 0;
        virtual std::string GetName() = 0;
        virtual uint32_t GetGateweay() = 0;
        virtual uint32_t GetMac() = 0;
};

#endif //NODE_HPP