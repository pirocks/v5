#!/bin/bash
cmd="gcc-4.8 -g -O2 `sdl-config --cflags` `sdl-config --libs` -o chess main.c -lSDL_image -lSDL -lX11 -std=c99 -Wall -pthread -DDMALLOC -DDMALLOC_FUNC_CHECK -pedantic -Wextra -save-temps=obj" #-fsanitize=address -fno-omit-frame-pointer 

echo $cmd
time  $cmd >& output.txt
cat output.txt
cat output.txt | grep -c warning | tr -d "\n"
printf " warnings, "

cat output.txt | grep -c error | tr -d "\n"
printf " errors\n"
