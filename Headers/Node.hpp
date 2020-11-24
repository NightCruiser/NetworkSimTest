#ifndef NODE_HPP
#define NODE_HPP
#include <utility>
#include <list>
#include <string>
#include <memory>
#include <cstdint>
#include "Channel.hpp"
#include "Wired.hpp"
#include "AddressPool.hpp"

/**
 * Node class is an interface for all the nodes
 * In our case RouterCore(represents switch) and Client(represents Host)
 * Contains the definitions of structures that are used for parsing/building
 * */

enum channels_ {cat3, cat5, cat6, cat7, optical}; /*USELESS NOW*/
enum nodes_ {router = 1, client};

class Channel; //new Forward declaration avoiding circular dependency

/*Structure to store nodes for building network*/
struct NodeConfig {
        std::string name_;
        uint32_t address_;
        std::pair<double, double> location_;
        nodes_ type_;
        unsigned id_;
        uint32_t mac_;
};
/*Structure to store connections for building network*/
struct Connections {
        uint32_t initiator_mac_;
        uint32_t target_mac_;
        double velocity_;
        unsigned bandwidth_;
        unsigned length_;
};

/*Structure to store events, used in map of events*/
struct Event {
        uint32_t sender_address_;
        uint32_t target_address_;
        unsigned size_;
};

class Node {
public:
        virtual ~Node() {}
        virtual bool ReceivePacket(std::shared_ptr<Packet>) = 0;
        virtual bool SendPacket(uint32_t, std::shared_ptr<Packet>) = 0;
        virtual bool RequestConnection(std::shared_ptr<Node>&, std::shared_ptr<Connections>&) = 0; /*Here the connection initiator should specify recieve/transmit queues of channel*/
        virtual bool ApproveConnection(std::shared_ptr<Channel>&, queue) = 0;
        virtual bool GeneratePacket() = 0;
        virtual bool SetAddress(uint32_t) = 0;
        virtual uint32_t GetAddress() = 0;
        virtual std::string GetName() = 0;
        virtual uint32_t GetMac() = 0;
        virtual unsigned GetId() = 0;
        virtual double GetChannelWeight(unsigned) = 0;  /*unsigned - ID of node, that requests*/
        virtual void Disconnect() = 0;   
};

#endif //NODE_HPP*/