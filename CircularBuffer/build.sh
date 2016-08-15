#!/bin/bash

LIBRARY_NAME=CircularBuffer

#Create shared library object
gcc -o ${LIBRARY_NAME}.o -c -Wall -Werror -fpic ./src/CircularBuffer.c -I ./include
gcc -shared -o lib${LIBRARY_NAME}.so ${LIBRARY_NAME}.o
mv lib${LIBRARY_NAME}.so ./lib
rm ${LIBRARY_NAME}.o

#Create test executable and link to above shared object
gcc -L${PWD}/lib -Wl,-rpath=${PWD}/lib -Wall -o test.out ./test/test.c -lCircularBuffer -I ./include
mv test.out ./bin


