
output : main.o transport_network.o graph.o
	@echo "Generating executable"
	g++ -o output  main.o transport_network.o graph.o

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

transport_network.o: transport_network.cpp transport_network.h
	g++ -c transport_network.cpp


run :
	@./output

clean: 
	@echo "Cleaning object and binary files"
	rm  *.o output a.out
