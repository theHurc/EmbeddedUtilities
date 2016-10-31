#!/bin/bash

#Make bin directory if necessary
mkdir bin > /dev/null 2>&1

#Remove the executables already there
rm ./bin/*

echo "Building thread safe circular buffer test"

gcc -o thread_safe_circular_buffer_test.out -Wall -Werror ./test/thread_safe_circular_buffer_test.c ./src/ThreadSafeCircularBuffer.c ./src/CriticalSection.c ./src/Logger.c -I ./include

mv thread_safe_circular_buffer_test.out ./bin

echo "Building table driven state machine example"

gcc -o table_driven_state_machine_example.out -Wall -Werror ./example/table_driven_state_machine_example.c ./src/TableDrivenStateMachine.c -I ./include

mv table_driven_state_machine_example.out ./bin

echo "Building X Macro example"

gcc -o x_macro_example.out -Wall -Werror ./example/x_macro_example.c ./src/XMacroTable.c ./src/XMacroTableExtended.c -I ./include

mv x_macro_example.out ./bin

exit 0
