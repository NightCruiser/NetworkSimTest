#ifndef CREATOR_HPP
#define CREATOR_HPP
#include "Node.hpp"
class Creator {
public:
        static std::shared_ptr<Node> CreateNode();
private:
};
#endif //CREATOR_HPP