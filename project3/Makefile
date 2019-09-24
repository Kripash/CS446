all: sim03

sim03: Sim03.cpp ConfigMeta.o PCBTimer.o
	g++ -std=c++11 -g Sim03.cpp -o sim03 -pthread 

ConfigMeta.o: ConfigMeta.cpp
	g++ -std=c++11 -c ConfigMeta.cpp -o ConfigMeta

PCBTimer.o: PCBTimer.cpp
	g++ -std=c++11 -c PCBTimer.cpp -o PCBTimer -pthread 

clean:
	rm -rf *.0 sim03
	rm -rf *.0 ConfigMeta
	rm -rf *.0 PCBTimer



