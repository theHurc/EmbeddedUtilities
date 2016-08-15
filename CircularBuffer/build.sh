#!/bin/bash

gcc -o CircularBuffer.o -c -Wall -Werror -fpic ./src/CircularBuffer.c -I ./include

gcc -shared -o libCircularBuffer.so CircularBuffer.o
mv libCircularBuffer.so ./lib
rm CircularBuffer.o

gcc -L/home/jake/EmbeddedUtilities/CircularBuffer/lib -Wl,-rpath=/home/jake/EmbeddedUtilities/CircularBuffer/lib -Wall -o test.out ./test/test.c -lCircularBuffer -I ./include
mv test.out ./bin


