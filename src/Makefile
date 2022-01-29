
output : main.o transport_network.o graph.o distance_calculator.o
	@echo "Generating executable"
	g++ -o output  main.o transport_network.o graph.o Menu.o distance_calculator.o
main.o: main.cpp
	g++ -c main.cpp

distance_calculator.o:  distance_calculator.cpp distance_calculator.h 
	g++ -c distance_calculator.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

transport_network.o: transport_network.cpp transport_network.h
	g++ -c transport_network.cpp

Menu.o: Menu.cpp Menu.h 
	g++ -c Menu.cpp


greetings:
	@echo "Hi user this is our graph project for the class AED 2021/2022"
run :
	@./output

clean: 
	@echo "Cleaning object and binary files"
	rm  *.o output a.out

