#include "../Headers/SimulationController.hpp"
#include <iostream>
#include <sstream>

SimulationController::SimulationController() : uploaded_(false), ready_(false), active_(false), 
        pool_(new AddressPool()) { /*allocating new pool*/ /*make_shared uses a copy constructor so "new"*/
}
void SimulationController::StartSimulation() {
       
}
                                /*Enum nodes and name*/ /*without connections for testing*/


        /*TEST PARSER VERY BAD!!! Implement normal with value checking and other stuff*/
        /*In normal implementation parses the nodes into a list of structures
        the connections into a list of connections
        Checks that data is valid
        No need for events 
        */
bool SimulationController::LoadCheckConfiguration(std::fstream& config) {
        std::string tmpstr;
        unsigned i = 0;

        /*Clearing and deleting created objects (they a shared pointers) when new config is loaded*/
        parsed_nodes_.clear();
        parsed_connections_.clear();
        events_map_.clear();
        network_graph_.clear();
        created_nodes_.clear();
        pool_->ClearPool();


        /*Parsing Nodes*/
        while(std::getline(config, tmpstr)) {
                if (tmpstr == "END_OF_NODES") {break;}
                std::istringstream tmpstream(tmpstr);
                std::shared_ptr<NodeConfig> newnode(new NodeConfig);
                tmpstream >> newnode->name_ >> newnode->address_ >> newnode->mac_
                        >> newnode->location_.first >> newnode->location_.second
                        >> tmpstr;
                /*assume that config is correct and only 2 types*/
                tmpstr == "client" ? newnode->type_ = client : newnode->type_ = router;
                newnode->id_ = i;
                parsed_nodes_.push_back(newnode);
                ++i;
        }
       
        std::cout << "Nodes loaded" << std::endl; /*DELETE*/
        /*Parsing Connections*/
        while (std::getline(config, tmpstr)) {
                if (tmpstr == "END_OF_CONNECTIONS") {break;}
                std::istringstream tmpstream(tmpstr);
                std::shared_ptr<Connections> newconnection(new Connections);
                tmpstream >> newconnection->initiator_mac_ >> newconnection->target_mac_
                        >> tmpstr >> newconnection->bandwidth_
                        >> newconnection->length_;
                
                tmpstr == "cat5" ? newconnection->velocity_ = 0.64 : tmpstr == "cat6" ? newconnection->velocity_ = 0.65
                        : tmpstr == "optical" ? newconnection->velocity_ = 0.67 : tmpstr == "cat7" ? newconnection->velocity_ = 0.75
                        : tmpstr == "cat3" ? newconnection->velocity_ = 0.585 : newconnection->velocity_ = 0.65; /*default*/
                parsed_connections_.push_back(newconnection);
        }
        std::cout << "Connections loaded" << std::endl;/*DELETE*/

        /*Parsing Events*/ /*DELETE IT NO NEED*/
        while (std::getline(config, tmpstr)) {
                if (tmpstr == "END_OF_EVENTS") {break;}
                std::istringstream tmpstream(tmpstr);
                std::shared_ptr<Event> newevent(new Event);

                tmpstream >> i >> newevent->sender_address_ >> newevent->target_address_
                                >> newevent->size_;
                
                /*Check if there is already event with this timing*/
                std::map<unsigned, std::set<std::shared_ptr<Event>>>::iterator it;
                it = events_map_.find(i);
                /*If there is no yet such timing, creating new map entry*/
                if (it == events_map_.end()) {
                        std::set<std::shared_ptr<Event>> newset;
                        newset.insert(newevent);
                        events_map_.insert(std::make_pair(i, newset));
                /*If it is, adding new event to set*/
                } else {
                        it->second.insert(newevent);
                }
        }
        std::cout << "Events loaded" << std::endl;/*DELETE*/

        /*Clearing failbits and EOF*/
        config.clear();
        /*Setting position to beginning*/
        config.seekg(0, std::ios::beg);
        uploaded_ = true;
        return true;
}

bool SimulationController::BuildNetwork() {
        /*std::pair<unsigned, std::set<std::pair<unsigned, double>>> tmppair;*/ /*pair for graph*/
        std::shared_ptr<Node> new_node; /*temp for new nodes*/

        std::cout << "Building Network" << std::endl;
        std::cout << "Creating Nodes" << std::endl;
        created_nodes_.clear();
        network_graph_.clear();
        /*creating nodes and graph without edges*/
        for (auto i : parsed_nodes_) {
                new_node = Creator::CreateNode(i->type_, i->id_, i->name_, i->address_, i->mac_, i->location_, pool_);
                created_nodes_.push_back(new_node);
                /*adding new node to graph, clearing set of edges*/
                /*tmppair.second.clear();*/
                /*tmppair.first = i->id_;*/
                /*network_graph_.insert(tmppair);*/
                graph_.AddVertexWithoutWeight(i->id_);
                /*registering new node in address pool*/
                pool_->AddNode(std::make_pair(new_node, new_node->GetMac()));
        }

        std::cout << "Connecting nodes" << std::endl;

        for (auto i : parsed_connections_) {
                std::shared_ptr<Node> tmpnode1 = pool_->GetNodeByMac(i->initiator_mac_);
                std::shared_ptr<Node> tmpnode2 = pool_->GetNodeByMac(i->target_mac_);
               /* std::shared_ptr<Node> tmpnode2 = pool_->GetNodeByMac(i->target_mac_);*/
                if (tmpnode1->RequestConnection(tmpnode2, i)) {
                        std::cout << tmpnode1->GetName() << " connected to " << tmpnode2->GetName() << std::endl; /*DELETE*/

                        /*iterator of network's graph*/
                        /*std::map<unsigned, std::set<std::pair<unsigned, double>>>::iterator it;*/
                        /*Filling the network graph*/
                        /*find the location of initiator in graph*/
                        /*it = network_graph_.find(tmpnode1->GetId());*/
                        /*Adding new connection with channel's weight for initiator node*/
                        /*inserting a new pair ID - Weight to initiator's connections list*/
                        /*tmpnode1->GetChannelWeight(tmpnode2->GetId()) - if the node is router we need an ID */
                        /*to find the correct channel*/
                        /*it->second.insert(std::make_pair(tmpnode2->GetId(), tmpnode1->GetChannelWeight(tmpnode2->GetId())));*/
                        graph_.AddEdgeWithWeight(tmpnode1->GetId(), tmpnode2->GetId(), tmpnode2->GetChannelWeight(tmpnode1->GetId()));
                        /*Doing the same for the target node*/
                        /*it = network_graph_.find(tmpnode2->GetId());*/
                        /*it->second.insert(std::make_pair(tmpnode1->GetId(), tmpnode2->GetChannelWeight(tmpnode1->GetId())));*/
                        /*GetChannelWeight for routers doesnt work yet*/
                }
                
        }
        std::cout << "Calculating routes for 1000+ nodes\n";
        auto start = std::chrono::system_clock::now();

        for (auto i : created_nodes_) {
                graph_.FindPathesForGivenNode_Djikstra(i->GetId());
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Djikstra's calculation time is " << elapsed_seconds.count() << std::endl;

        /*std::cout << "Our Network : \n";
        for (auto i : network_graph_) {
                std::cout << "Node " << i.first << " Connected to ";
                for (auto j : i.second) {
                        std::cout << j.first << " with channel's weight (transmission time for 1500bytes packet) " << j.second << "ms ";
                }
                std::cout << std::endl;
        }

        std::cout << "Our Pool : \n";
        pool_->PrintPool();*/
        return true;
}


bool SimulationController::GetStatus() {
        return active_;
}