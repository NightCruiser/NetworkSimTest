simulator.out : main.o sim_controller.o creator.o pool.o wired.o packet.o client.o router.o network_graph.o
	g++ BuildFiles/main.o BuildFiles/sim_controller.o BuildFiles/creator.o BuildFiles/pool.o BuildFiles/tpair.o BuildFiles/packet.o BuildFiles/client.o BuildFiles/router.o BuildFiles/network_graph.o -o simulator.out -std=c++11 -pthread -Wall -pedantic -g
main.o : main.cpp Headers/SimulationController.hpp 
	g++ -c main.cpp -o BuildFiles/main.o -std=c++11 -pthread -Wall -pedantic -g
router.o : Node/RoutingCore.cpp Headers/RoutingCore.hpp
	g++ -c Node/RoutingCore.cpp -o BuildFiles/router.o -std=c++11 -pthread -Wall -pedantic -g
client.o : Node/Client.cpp Headers/Client.hpp
	g++ -c Node/Client.cpp -o BuildFiles/client.o -std=c++11 -pthread -Wall -pedantic -g
packet.o : Node/Packet/TcpPacket.cpp Headers/TcpPacket.hpp
	g++ -c Node/Packet/TcpPacket.cpp -o BuildFiles/packet.o -std=c++11 -pthread -Wall -pedantic -g
wired.o : Channel/Wired.cpp Headers/Wired.hpp
	g++ -c Channel/Wired.cpp -o BuildFiles/tpair.o -std=c++11 -pthread -Wall -pedantic -g
pool.o : BuilderAndAddressing/AddressPool.cpp Headers/AddressPool.hpp
	g++ -c BuilderAndAddressing/AddressPool.cpp -o BuildFiles/pool.o -std=c++11 -pthread -Wall -pedantic -g
creator.o: BuilderAndAddressing/Creator.cpp Headers/Creator.hpp
	g++ -c BuilderAndAddressing/Creator.cpp -o BuildFiles/creator.o -std=c++11 -pthread -Wall -pedantic -g
sim_controller.o: BuilderAndAddressing/SimulationController.cpp Headers/SimulationController.hpp
	g++ -c BuilderAndAddressing/SimulationController.cpp -o BuildFiles/sim_controller.o -std=c++11 -pthread -Wall -pedantic -g
network_graph.o: BuilderAndAddressing/NetworkGraph.cpp Headers/NetworkGraph.hpp
	g++ -c BuilderAndAddressing/NetworkGraph.cpp -o BuildFiles/network_graph.o -std=c++11 -pthread -Wall -pedantic -g
