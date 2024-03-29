cc=gcc
ccflags=-g -O0 -m32 -std=c99 #-Ddotout #-Dmaxdebug
#sdlflags=`sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL -lX11
sdl=
#asanflags=-fsanitize=address -fno-omit-frame-pointer -lasan
asanflags=
warnings= -Wall -pedantic -Wextra
#ldflags=-lasan
#ldflags=-pg
ldflags=-m32
all: main.o position_evaluate text_only_utils debug.o dot_record.o
	$(cc) board_display.o command_line.o get_movev2.o position_evaluatev6.o valid.o move.o debug.o main.o dot_record.o -o chess $(sdlflags) $(ldflags)
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
check: check_curses_utils
	#not implemented
check_curses_utils: curses_board_utils.o valid.o
	$(cc) curses_board_utils.o valid.o -o test $(sdlflags) $(ldflags)
curses_board_utils.o:
	$(cc) $(ccflags) -c curses_board_utils.c -o curses_board_utils.o $(warnings) $(asanflags) #-Dtesting_files
