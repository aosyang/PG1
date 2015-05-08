all: Pac-man

Pac-man: main.o Player.o Ghost.o Console_linux.o
	g++ main.o Player.o Ghost.o Console_linux.o -o Pac-man
	
main.o: main.cpp
	g++ -c main.cpp
	
Player.o: Player.cpp
	g++ -c Player.cpp
	
Ghost.o: Ghost.cpp
	g++ -c Ghost.cpp
	
Console.o: Console_linux.cpp
	g++ -c Console_linux.cpp
	
clean:
	rm *o Pac-man

