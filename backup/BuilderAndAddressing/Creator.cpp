#include "../Headers/Creator.hpp"
#include "../Headers/RoutingCore.hpp"
#include "../Headers/Client.hpp"
std::shared_ptr<Node> Creator::CreateNode(nodes_ node, std::string name, uint32_t mac, std::pair<double,double> location, std::shared_ptr<AddressPool> pool) {

        Node *tmpPtr; /*avoiding make_shared*/
        switch (node) {
        case router:
                tmpPtr = new RoutingCore(name, mac, location, pool);
                /*newNode = std::make_shared<Node>(RoutingCore(name, mac, location, pool));*/
                break;
        case client:
                tmpPtr = new Client(name, mac, location, pool);
                /*newNode = std::make_shared<Node>(Client(name, mac, location, pool));*/
                break;
        }
        std::shared_ptr<Node> newNode(tmpPtr);
        return newNode;
}