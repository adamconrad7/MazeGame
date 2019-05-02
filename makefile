CC = g++ -std=c++11
CCXFLAGS = -Wall -g

all: maze_exe

#maze_exe: maze_application.o mazelevel.o OpenSpace.o ta.o player.o
#	$(CC) $(CCXFLAGS) maze_application.o OpenSpace.o mazelevel.o ta.o player.o  -o maze_exe


#maze_application.o: maze_application.cpp mazelevel.cpp
#	$(CC) $(CCXFLAGS) maze_application.cpp mazelevel.cpp  -c

maze_exe: maze_application.o mazelevel.o OpenSpace.o ta.o player.o game.o
	$(CC) $(CCXFLAGS) maze_application.o OpenSpace.o mazelevel.o ta.o player.o game.o -o maze_exe

game.o: mazelevel.cpp game.cpp
	$(CC) $(CCXFLAGS) game.cpp mazelevel.cpp -c

maze_application.o: maze_application.cpp mazelevel.cpp game.cpp
	$(CC) $(CCXFLAGS) maze_application.cpp mazelevel.cpp game.cpp -c


mazelevel.o: OpenSpace.cpp mazelevel.cpp ta.cpp player.o
	$(CC) $(CCXFLAGS) OpenSpace.cpp ta.cpp mazelevel.cpp player.o -c

OpenSpace.o: OpenSpace.cpp
	$(CC) $(CCXFLAGS) OpenSpace.cpp -c

ta.o: ta.cpp
	$(CC) $(CCXFLAGS) ta.cpp -c

player.o: player.cpp
	$(CC) $(CCXFLAGS) player.cpp -c

clean:
	rm -rf *.o *.out
