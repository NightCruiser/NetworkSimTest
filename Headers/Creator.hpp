#ifndef CREATOR_HPP
#define CREATOR_HPP
#include "RoutingCore.hpp"
#include "Client.hpp"

class Creator {
public:
        static std::shared_ptr<Node> CreateNode(nodes_ node, unsigned, std::string name, uint32_t address, uint32_t mac, std::pair<double,double> location, std::shared_ptr<AddressPool> pool);
private:
};
#endif //CREATOR_HPP