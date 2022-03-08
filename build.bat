@echo off

gcc -g -std=c99 main.c  -ISDL2/include/ -L../chip8 -lSDL2 -o emu
