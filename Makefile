cc=gcc-4.9
ccflags=-g -O2 -std=c99 -pthread
sdlflags=`sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL -lX11
asanflags=-fsanitize=address -fno-omit-frame-pointer -lasan
warnings= -Wall -pedantic -Wextra
all: main.o  position_evaluate.o text_only_utils.o
	$(cc) main.o position_evaluate.o text_only_utils.o -o chess
text_only_utils.o: board_display.o command_line.o
	$(cc) board_display.o command_line.o -o text_only_utils.o -lasan
board_display.o: board_display.c valid.o
	$(cc) $(ccflags) -c board_display.c -o board_display.o $(asanflags)
command_line.o: command_line.c valid.o
	$(cc) $(ccflags) -c command_line.c -o command_line.o $(warnings) $(asanflags)
main.o: main.c
	$(cc) $(ccflags) -c main.c -o main.o $(warnings) $(asanflags) $(sdlflags)
position_evaluate.o: position_evaluatev6.o get_movev2.o valid.o move.o
	$(cc) -c get_movev2.o position_evaluatev6.o -o position_evaluate.o -lasan
get_movev2.o:
	$(cc) $(ccflags) -c get_movev2.c -o get_movev2.o $(warnings) $(asanflags)
position_evaluatev6.o:
	$(cc) $(ccflags) -c position_evaluatev6.c -o position_evaluatev6.o $(warnings) $(asanflags)
valid.o:
	$(cc) $(ccflags) -c valid.c -o valid.o $(warnings) $(asanflags)
move.o: valid.o
	$(cc) $(ccflags) -c move.c -o move.o $(warnings) $(asanflags)
clean:
	rm chess text_only_utils.o position_evaluate.o -f
