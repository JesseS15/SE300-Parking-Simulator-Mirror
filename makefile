all: compile link

compile:
	g++ -I src/include -I src/bin -c main.cpp
link:
	g++ Main.o -o main -L src/bin -L src/Lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio