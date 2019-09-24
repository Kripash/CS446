all: sim04

sim04: Sim04.cpp ConfigMeta.o PCBTimer.o
	g++ -std=c++11 -g Sim04.cpp -o sim04 -pthread 

ConfigMeta.o: ConfigMeta.cpp
	g++ -std=c++11 -c ConfigMeta.cpp -o ConfigMeta

PCBTimer.o: PCBTimer.cpp
	g++ -std=c++11 -c PCBTimer.cpp -o PCBTimer -pthread 

clean:
	rm -rf *.0 sim04
	rm -rf *.0 ConfigMeta
	rm -rf *.0 PCBTimer



