all: sim01

sim01: Sim01.cpp ConfigMeta.o
	g++ -std=c++11 Sim01.cpp -o sim01

ConfigMeta.o: ConfigMeta.cpp
	g++ -std=c++11 -c ConfigMeta.cpp -o ConfigMeta

clean:
	rm -rf *.0 sim01 
	rm -rf *.0 ConfigMeta



