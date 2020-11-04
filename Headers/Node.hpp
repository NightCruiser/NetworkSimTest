#ifndef NODE_HPP
#define NODE_HPP
#include <utility>
#include <list>
#include <string>
#include "Packet.hpp"
class Node {
public:
        virtual ~Node() {}
        virtual bool RecievePacket() = 0;
        virtual bool Start() = 0;
        virtual bool TransmitPacket() = 0;
        virtual bool Connect(Node&) = 0;
        virtual bool GeneratePacket() = 0;
private:
        std::pair<double, double> location_;
        std::string name_;
        std::list<Packet> packets_;
};

#endif //NODE_HPP