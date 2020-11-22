#include "../Headers/SimulationController.hpp"
#include <iostream>
#include <sstream>
/*MULTITHREADING!!!*/
SimulationController::SimulationController() : uploaded_(false), ready_(false), active_(false), 
        pool_(new AddressPool()) { /*allocating new pool*/ /*make_shared uses a copy constructor so "new"*/
}
void SimulationController::StartSimulation() {
       
}
                                /*Enum nodes and name*/ /*without connections for testing*/
bool SimulationController::LoadCheckConfiguration(std::fstream& config) {
        std::string tmpstr;
        unsigned i = 0;

        parsed_nodes_.clear();
        parsed_connections_.clear();
        events_map_.clear();

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
                /*will refactor Channels, but for now only 1 twisted pait exists*/
                tmpstr == "cat5" ? newconnection->velocity_ = 0.64 : tmpstr == "cat6" ? newconnection->velocity_ = 0.65
                        : tmpstr == "optical" ? newconnection->velocity_ = 0.67 : tmpstr == "cat7" ? newconnection->velocity_ = 0.75
                        : tmpstr == "cat3" ? newconnection->velocity_ = 0.585 : newconnection->velocity_ = 0.65; /*default*/
                parsed_connections_.push_back(newconnection);
        }
        std::cout << "Connections loaded" << std::endl;/*DELETE*/
        /*Parsing Events*/
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
        
        uploaded_ = true;
        return true;
}

bool SimulationController::BuildNetwork() {
        std::pair<unsigned, std::set<std::pair<unsigned, double>>> tmppair; /*pair for graph*/
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
                tmppair.second.clear();
                tmppair.first = i->id_;
                network_graph_.insert(tmppair);
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
                        std::map<unsigned, std::set<std::pair<unsigned, double>>>::iterator it;
                        /*Filling the network graph*/
                        it = network_graph_.find(tmpnode1->GetId());
                        it->second.insert(std::make_pair(tmpnode2->GetId(), tmpnode1->GetChannelWeight()));
                        it = network_graph_.find(tmpnode2->GetId());
                        it->second.insert(std::make_pair(tmpnode1->GetId(), tmpnode1->GetChannelWeight()));
                }
                
        }

        std::cout << "Our Network : \nNode ID\tConnected To\tChannel's weight\n";
        for (auto i : network_graph_) {
                std::cout << i.first << "\t";
                for (auto j : i.second) {
                        std::cout << j.first << "\t" << j.second << "\n";
                }
        }
        return true;
}


bool SimulationController::GetStatus() {
        return active_;
}