#ifndef ADDRESSPOOL_HPP
#define ADDRESSPOOL_HPP
#include "Node.hpp"

class AddressPool {
public:
        std::shared_ptr<Node> GetNodeByAddress(uint32_t);
        void AddNode(std::pair<std::shared_ptr<Node>, uint32_t>);
private:
        std::list<std::pair<std::shared_ptr<Node>, uint32_t>> nodes_;
        std::mutex pool_mtx_; /*mybe no need? too tired to investigate now*/
};
#endif //ADDRESSPOOL_HPP