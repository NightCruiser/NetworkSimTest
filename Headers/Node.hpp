#ifndef NODE_HPP
#define NODE_HPP
#include <utility>
#include <list>
#include <string>
#include <memory>
#include <cstdint>
#include "Channel.hpp"
#include "TwistedPair.hpp"
#include "AddressPool.hpp"
/*#include "Packet.hpp" //new
#include "Channel.hpp" //new */
enum channels_ {twisted_pair = 1, optical, wifi, m_4g, m_5g};
enum nodes_ {router = 1, client};
//typedef enum queues_ {first = 1, second = 2} queue;
class Channel; //new Forward declaration avoiding circular dependency

class Node {
public:
        virtual ~Node() {}
        virtual void Stop() = 0;
        virtual bool ReceivePacket(std::shared_ptr<Packet>) = 0;
        virtual bool Start() = 0;
        virtual bool SendPacket(uint32_t, std::shared_ptr<Packet>) = 0;
        virtual bool RequestConnection(uint32_t, channels_, unsigned) = 0; /*Here the connection initiator should specify recieve/transmit queues of channel*/
        virtual bool ApproveConnection(std::shared_ptr<Channel>, queue) = 0;
        virtual bool GeneratePacket() = 0;
        virtual bool RequestAddressesFromDhcp() = 0;
        virtual uint32_t CastAddress() = 0;
        virtual bool SetAddress(uint32_t) = 0;
        virtual bool SetGateway(uint32_t) = 0;
        virtual uint32_t GetAddress() = 0;
        virtual std::string GetName() = 0;
        virtual uint32_t GetGateweay() = 0;
        virtual uint32_t GetMac() = 0;        
};

#endif //NODE_HPP*/