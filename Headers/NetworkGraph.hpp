#include <map>
#include <set>

/**
 * Test class that doesn't affect the project!!!
 * NOT USED, NOT INCLUDED IN BUILD
 * */
const double Infinity = 9999.9999;

class NetworkGraph {
public:
        NetworkGraph();
        ~NetworkGraph();
        bool AddVertexWithoutWeight(unsigned);
        void AddVertexWithoutWeight(void);
        bool AddEdgeWithWeight(unsigned, unsigned, double); /*node - target node - weight*/
        void FindPathesForGivenNode_Djikstra(unsigned); /**/
        
private:
        unsigned vertexes_count_;
        /*unsigned == vertex, unsigned2 == adjacent vertex, double == weight of the edge*/
        std::map<unsigned, std::set<std::pair<unsigned, double>>> network_graph_;
};