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
bool SimulationController::LoadCheckConfiguration(std::fstream config) {
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
                tmpstream >> newnode->name_ >> newnode->address_ 
                        >> newnode->location_.first >> newnode->location_.second
                        >> newnode->type_;
                newnode->id_ = i;
                parsed_nodes_.push_back(newnode);
                ++i;
        }
        /*Parsing Connections*/
        while (std::getline(config, tmpstr)) {
                if (tmpstr == "END_OF_CONNECTIONS") {break;}
                std::istringstream tmpstream(tmpstr);
                std::shared_ptr<Connections> newconnection(new Connections);
                tmpstream >> newconnection->initiator_ >> newconnection->target_
                        >> newconnection->channel_ >> newconnection->bandwidth_
                        >> newconnection->length_;
                parsed_connections_.push_back(newconnection);
        }
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
        
        return true;
}

bool SimulationController::BuildNetwork() {
        return false; /*disable using*/
}

bool SimulationController::LoadCheckConfiguration(std::string test) {
        uploaded_ = true;
        return true;
}

bool SimulationController::BuildNetwork(std::string test) { /*Just FOR TEST 15 clients connected to 1 router*/
        if (!uploaded_) {return false;}
        std::shared_ptr<Node> tempNode = Creator::CreateNode(router, "firstRouter", 455, std::make_pair(15,52), pool_);
        tempNode->SetAddress((uint32_t)321);
        pool_->AddNode(std::make_pair(tempNode, (uint32_t)321)); /*adding to pool*/
        /*CreateNode(nodes_ node, std::string name, uint32_t mac, std::pair<double,double> location, std::shared_ptr<AddressPool> pool)*/
        
        for (int i = 0; i < 50; i++) {
                std::cout << "Creating Node " << (i + 1) << std::endl; /*DELETE*/
                std::string name = "Client " + std::to_string(i); /*DELETE*/
                std::shared_ptr<Node> tmp = Creator::CreateNode(client, name, i, std::make_pair(15,52), pool_);
                if (tmp->RequestConnection((uint32_t)321, twisted_pair, (unsigned)2000, 0.65, 75.)) {
                        std::cout << tmp->GetName() << " connected to " << tempNode->GetName() << std::endl; /*DELETE*/
                };
                pool_->AddNode(std::make_pair(tmp, i));
                sim_nodes_.push_back(std::make_pair(tmp, client));
        }

        sim_nodes_.push_back(std::make_pair(tempNode, router));
        ready_ = true;
        return true;
}


bool SimulationController::GetStatus() {
        return active_;
}