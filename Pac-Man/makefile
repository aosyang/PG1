all: Pac-man

Pac-man: main.o Player.o Ghost.o Console.o
	g++ main.o Player.o Ghost.o Console.o -o Pac-man
	
main.o: main.cpp
	g++ -c main.cpp
	
Player.o: Player.cpp
	g++ -c Player.cpp
	
Ghost.o: Ghost.cpp
	g++ -c Ghost.cpp
	
Console.o: Console.cpp
	g++ -c Console.cpp
	
clean:
	rm *o Pac-man

