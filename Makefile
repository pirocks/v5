cc=gcc-4.9
ccflags=-g -O2 -std=c99 -pthread
sdlflags=`sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL -lX11
asanflags=-fsanitize=address -fno-omit-frame-pointer
warnings= -Wall -Wextra
all: main.o position_evaluate.o text_only_utils.o 
	$(cc) board_display.o command_line.o get_movev2.o position_evaluatev6.o valid.o move.o debug.o main.o -o chess -lasan $(sdlflags)
text_only_utils.o: board_display.o command_line.o
board_display.o: board_display.c valid.o
	$(cc) $(ccflags) -c board_display.c -o board_display.o $(asanflags)
command_line.o: command_line.c valid.o
	$(cc) $(ccflags) -c command_line.c -o command_line.o $(warnings) $(asanflags)
main.o: main.c
	$(cc) $(ccflags) -c main.c -o main.o $(warnings) $(asanflags) $(sdlflags)
position_evaluate.o: position_evaluatev6.o get_movev2.o valid.o move.o debug.o board_display.o
get_movev2.o: get_movev2.c 
	$(cc) $(ccflags) -c get_movev2.c -o get_movev2.o $(warnings) $(asanflags)
position_evaluatev6.o: position_evaluatev6.c
	$(cc) $(ccflags) -c position_evaluatev6.c -o position_evaluatev6.o $(warnings) $(asanflags)
valid.o: valid.c
	$(cc) $(ccflags) -c valid.c -o valid.o $(warnings) $(asanflags)
move.o: valid.o move.c
	$(cc) $(ccflags) -c move.c -o move.o $(warnings) $(asanflags)
debug.o: debug.c
	$(cc) $(ccflags) -c debug.c -o debug.o $(warnings) $(asanflags)
clean:
	rm chess *.o -f
