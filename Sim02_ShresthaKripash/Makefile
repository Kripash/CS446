all: sim02

sim02: Sim02.cpp ConfigMeta.o PCBTimer.o
	g++ -std=c++11 -g Sim02.cpp -o sim02 -pthread 

ConfigMeta.o: ConfigMeta.cpp
	g++ -std=c++11 -c ConfigMeta.cpp -o ConfigMeta

PCBTimer.o: PCBTimer.cpp
	g++ -std=c++11 -c PCBTimer.cpp -o PCBTimer -pthread 

clean:
	rm -rf *.0 sim02
	rm -rf *.0 ConfigMeta
	rm -rf *.0 PCBTimer



