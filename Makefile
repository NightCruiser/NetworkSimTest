simulator.out : main.o sim_controller.o creator.o pool.o wired.o packet.o client.o router.o
	g++ BuildFiles/main.o BuildFiles/sim_controller.o BuildFiles/creator.o BuildFiles/pool.o BuildFiles/tpair.o BuildFiles/packet.o BuildFiles/client.o BuildFiles/router.o -o simulator.out -std=c++11 -pthread -Wall -pedantic
main.o : main.cpp Headers/SimulationController.hpp 
	g++ -c main.cpp -o BuildFiles/main.o -std=c++11 -pthread -Wall -pedantic
router.o : Node/RoutingCore.cpp Headers/RoutingCore.hpp
	g++ -c Node/RoutingCore.cpp -o BuildFiles/router.o -std=c++11 -pthread -Wall -pedantic
client.o : Node/Client.cpp Headers/Client.hpp
	g++ -c Node/Client.cpp -o BuildFiles/client.o -std=c++11 -pthread -Wall -pedantic
packet.o : Node/Packet/TcpPacket.cpp Headers/TcpPacket.hpp
	g++ -c Node/Packet/TcpPacket.cpp -o BuildFiles/packet.o -std=c++11 -pthread -Wall -pedantic
wired.o : Channel/Wired.cpp Headers/Wired.hpp
	g++ -c Channel/Wired.cpp -o BuildFiles/tpair.o -std=c++11 -pthread -Wall -pedantic
pool.o : BuilderAndAddressing/AddressPool.cpp Headers/AddressPool.hpp
	g++ -c BuilderAndAddressing/AddressPool.cpp -o BuildFiles/pool.o -std=c++11 -pthread -Wall -pedantic
creator.o: BuilderAndAddressing/Creator.cpp Headers/Creator.hpp
	g++ -c BuilderAndAddressing/Creator.cpp -o BuildFiles/creator.o -std=c++11 -pthread -Wall -pedantic
sim_controller.o: BuilderAndAddressing/SimulationController.cpp Headers/SimulationController.hpp
	g++ -c BuilderAndAddressing/SimulationController.cpp -o BuildFiles/sim_controller.o -std=c++11 -pthread -Wall -pedantic
