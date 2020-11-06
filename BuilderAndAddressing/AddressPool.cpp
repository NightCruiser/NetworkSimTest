#include "../Headers/AddressPool.hpp"
#include <algorithm>
/*MULTITHREADING!!!*/
std::shared_ptr<Node> AddressPool::GetNodeByAddress(uint32_t address) {
        pool_mtx_.lock();
        std::list<std::pair<std::shared_ptr<Node>, uint32_t>>::iterator it;
        it = std::find(nodes_.begin(), nodes_.end(), address);
        /*Implement some check later, also in Nodes and others*/
        pool_mtx_.unlock();
        return it->first;
}
void AddressPool::AddNode(std::pair<std::shared_ptr<Node>, uint32_t> node) {
        /*Implement some check later*/
        nodes_.push_back(node);
}