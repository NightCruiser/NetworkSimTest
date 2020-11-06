#include "../Headers/Creator.hpp"
#include "../Headers/RoutingCore.hpp"
#include "../Headers/Client.hpp"
std::shared_ptr<Node> Creator::CreateNode(nodes_ node, std::string name, uint32_t mac, std::pair<double,double> location, std::shared_ptr<AddressPool> pool) {
        std::shared_ptr<Node> newNode;
        switch (node) {
        case router:
                newNode = std::make_shared<Node>(RoutingCore(name, mac, location, pool));
                break;
        case client:
                newNode = std::make_shared<Node>(Client(name, mac, location, pool));
                break;
        default:
                return;
        }
        return newNode;
}