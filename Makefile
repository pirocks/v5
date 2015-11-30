cc=gcc-4.9
ccflags=-g -O0 -std=c99 -Dmaxdebug
sdlflags=`sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL -lX11
#asanflags=-fsanitize=address -fno-omit-frame-pointer -lasan
asanflags=
warnings= -Wall -pedantic -Wextra
#ldflags=-lasan
ldflags=-g
all: main.o position_evaluate text_only_utils debug.o
	$(cc) -g board_display.o command_line.o get_movev2.o position_evaluatev6.o valid.o move.o debug.o main.o -o chess $(sdlflags) $(ldflags)
position_evaluate: get_movev2.o position_evaluatev6.o valid.o move.o
text_only_utils: board_display.o command_line.o
#debug: debug.o dot_record.o

board_display.o: board_display.c
	$(cc) $(ccflags) -c board_display.c -o board_display.o $(warnings) $(asanflags)
command_line.o: command_line.c
	$(cc) $(ccflags) -c command_line.c -o command_line.o $(warnings) $(asanflags)
main.o: main.c
	$(cc) $(ccflags) -c main.c -o main.o $(warnings) $(warnings) $(asanflags) $(sdlflags)
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
dot_record.o: dot_record.c
	$(cc) $(ccflags) -c dot_record.c -o dot_record.o $(warnings) $(asanflags)
clean:
	rm chess *.o out.dot -f
check:
	#not implemented
