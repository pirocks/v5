#!/bin/bash
cmd="gcc-4.8 -pg `sdl-config --cflags` `sdl-config --libs` -o chess main.c -lSDL -lSDL_image -lX11 -std=c99 -Wall -pthread -pedantic -Wextra -Wunused-parameter -fsanitize=address -fno-omit-frame-pointer"

echo $cmd
$cmd &> output.txt
cat output.txt
cat output.txt | grep -c warning | tr -d "\n"

printf " warnings, "
cat output.txt | grep -c error | tr -d "\n"
printf " errors\n"
