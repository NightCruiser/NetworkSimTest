#include <map>
#include <set>
class NetworkGraph {
public:

private:
        /*unsigned == vertex, unsigned2 == adjacent vertex, double == weight of the edge*/
        std::map<unsigned, std::set<std::pair<unsigned, double>>> network_graph_;
};