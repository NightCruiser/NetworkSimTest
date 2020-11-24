#include "../Headers/AddressPool.hpp"
#include <algorithm>
#include <iostream> /*DELETE*/

AddressPool::AddressPool() {
        std::cout << "pool created" << std::endl; /*DELETE*/
}

std::shared_ptr<Node> AddressPool::GetNodeByMac(const uint32_t address) {
        std::list<std::pair<std::shared_ptr<Node>, uint32_t>>::iterator it;
        std::cout << "GetNodeByAddress Called" << std::endl; /*DELETE*/
        it = std::find_if(nodes_.begin(), nodes_.end(), [&address](const std::pair<std::shared_ptr<Node>, uint32_t>& i) {
                return i.second == address ? true : false;
        });
        /*Implement some check later, also in Nodes and others*/
        return it->first;
}
void AddressPool::AddNode(std::pair<std::shared_ptr<Node>, uint32_t> node) {
        /*What if recieved new from DHCP?*/
        /*Implement some check later*/
        nodes_.push_back(node);
}

void AddressPool::ClearPool() {
        nodes_.clear();
        
}

void AddressPool::PrintPool() {

        for (auto i : nodes_) {
                std::cout << "Node " << i.first->GetId() << " with a mac " << i.second << std::endl;
        }
        
}