#include "../Headers/NetworkGraph.hpp"
#include <vector>
#include <cmath>
#include <iostream>
/*Constructor*/
NetworkGraph::NetworkGraph() : vertexes_count_(0) {
        network_graph_.clear();
}

/*Destructor*/
NetworkGraph::~NetworkGraph() {}

bool NetworkGraph::AddVertexWithoutWeight(unsigned id) {
        std::map<unsigned, std::set<std::pair<unsigned, double>>>::iterator it;
        std::pair<unsigned, std::set<std::pair<unsigned, double>>> tmp_pair;
        /*check the existance of the given vertex id*/
        it = network_graph_.find(id);
        if (it != network_graph_.end()) {
                return false;
        }
        /*adding new pair with clean set to network graph's map*/
        tmp_pair.second.clear();
        tmp_pair.first = id;
        network_graph_.insert(tmp_pair);
        return true;
}

void NetworkGraph::AddVertexWithoutWeight() {
        std::pair<unsigned, std::set<std::pair<unsigned, double>>> tmp_pair;

        /*adding new pair with clean set to network graph's map*/
        tmp_pair.second.clear();
        tmp_pair.first = vertexes_count_;
        network_graph_.insert(tmp_pair);
        ++vertexes_count_;
}

bool NetworkGraph::AddEdgeWithWeight(unsigned id, unsigned target_id, double weight) {
        std::map<unsigned, std::set<std::pair<unsigned, double>>>::iterator it1, it2;
        /*check the existance of the given vertexes ids*/
        it1 = network_graph_.find(id);
        it2 = network_graph_.find(target_id);
        if (it1 == network_graph_.end() || it2 == network_graph_.end()) {
                return false;
        }
        /*adding new values to the set for given id*/
        it1->second.insert(std::make_pair(target_id, weight));
        
        /*doing the same with target id*/
        it2->second.insert(std::make_pair(id, weight));
        return true;
}

bool compare_doubles_equality (double x, double y, double epsilon = 0.00001) {
        if (fabs(x - y) < epsilon) {
                return true;
        }
        return false;
}

void NetworkGraph::FindPathesForGivenNode_Djikstra(unsigned vertex) {
        /*an associative container that will contain and maintain the cheapest route's weight to/from vertex
          to/from other vertexes in graph
          index(key) - vertex (id of node (assume that node's ids increment from 0 while creating))
          [key].first - cost(weight) of cheapest route
          [key].second - visited or not*/
        std::map<unsigned, std::pair<double, bool>> cheapest_routes;
        //std::vector<std::pair<double, bool>> cheapest_routes;
        cheapest_routes.clear();

        /*creating cheapest_routes helper map depending on graph's size
          Setting costs to Infinity (const value == 9999.9999) and visited to false */
        for (auto i : network_graph_) {
                cheapest_routes.insert(std::make_pair(i.first, std::make_pair(Infinity, false)));
        }

        /*Setting cost for given vertex (start vertex) to 0.0*/
        cheapest_routes[vertex].first = 0.;

        for (unsigned long i = 0; i < cheapest_routes.size(); ++i) {
                /*Finding vertex with minimal route weight*/
                double min = 9999.9999;
                unsigned min_vertex = 0;
                for (auto k : cheapest_routes) {
                        /*check that not visited yet and update new minimum*/
                        if (!k.second.second) {
                                if (k.second.first < min) {
                                        min = k.second.first;
                                        min_vertex = k.first;
                                }
                        }
                }
                /*running through adjacencies of minimal weight vertex*/
                for (auto k : network_graph_[min_vertex]) {
                        /*cheapest_routes[k.first].first - [k.first] - ID of Neighbour's vertex from graph
                        [k.first].first - current weight in cheapest_routes map*/
                        if (cheapest_routes[k.first].first > min + k.second) {
                                cheapest_routes[k.first].first = min + k.second;
                        }
                }
                /*Marking as visited*/
                cheapest_routes[min_vertex].second = true;
                
        }
        std::cout << "Cheapest Routes (Start Vertex has 0.0) " << vertex << std::endl;

        for (auto i : cheapest_routes) {
                std::cout << "Vertex " << i.first << " :: " << i.second.first << std::endl;
        }

}