#!/bin/bash

gcc -o CircularBuffer.o -c -Wall -fpic ./src/CircularBuffer.c -I ./include 
gcc -shared -o CircularBuffer.so CircularBuffer.o
gcc -L ./ -Wall -o test.out ./test/test.c -lCircularBuffer -I ./include
