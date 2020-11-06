#include "Node.hpp"

class AddressPool {
public:
        std::shared_ptr<Node> GetNodeByAddress(uint32_t);
        void AddNode(std::pair<std::shared_ptr<Node>, uint32_t>);
private:
        std::list<std::pair<std::shared_ptr<Node>, uint32_t>> nodes_;
};