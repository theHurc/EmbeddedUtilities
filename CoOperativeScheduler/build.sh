#!/bin/bash

isCleanOption=false #indicates if build artifacts should be removed
isSharedOption=false #indicates if ONLY shared object should be built
isHelpOption=false #indicates if only shared object should be built

LIBRARY_NAME=CoOperativeScheduler
EXECUTABLE_DIRECTORY=bin
LIBRARY_DIRECTORY=lib

SUCCESS_COLOR=`tput setaf 2`
NEUTRAL_COLOR=`tput setaf 3`
NO_COLOR=`tput sgr0` #No color; reset

#check user input
#for i in $*; do
if [[ $1 = "clean" ]]; then
  isCleanOption=true

elif [[ $1 = "shared" ]]; then
  isSharedOption=true

elif [[ $1 = "help" ]]; then
  isHelpOption=true

elif [[ $1 = "" ]]; then
  :

else
  echo "${NEUTRAL_COLOR}"
  echo "Invalid Option"
  isHelpOption=true

fi 
#done

if [ "$isHelpOption" = true ]; then
  echo "${NEUTRAL_COLOR}"
  echo "Usage : $0 [Option]"
  echo ""
  echo "Options:"
  echo "help    Print this menu"
  echo "clean   Remove all build artifacts"
  echo "shared  Build only the shared library"
  echo "${NO_COLOR}"
  exit 0
fi

#make directories if not already made
mkdir ${LIBRARY_DIRECTORY} > /dev/null 2>&1
mkdir ${EXECUTABLE_DIRECTORY} > /dev/null 2>&1

#execute if clean option enabled
if [ "$isCleanOption" = true ]; then
  rm ./${LIBRARY_DIRECTORY}/* > /dev/null 2>&1
  rm ./${EXECUTABLE_DIRECTORY}/* > /dev/null 2>&1
  echo "${SUCCESS_COLOR}"
  echo "Completely cleaned build artifacts from directories:${NEUTRAL_COLOR}"
  echo "${LIBRARY_DIRECTORY}/"
  echo "${EXECUTABLE_DIRECTORY}/"
  echo "${NO_COLOR}"
  exit 0
fi


#Create shared library object
gcc -o ${LIBRARY_NAME}.o -c -Wall -Werror -fpic ./src/CoOperativeScheduler.c -I ./include -I../Common/include
gcc -shared -o lib${LIBRARY_NAME}.so ${LIBRARY_NAME}.o
mv lib${LIBRARY_NAME}.so ./${LIBRARY_DIRECTORY}
rm ${LIBRARY_NAME}.o

echo "${SUCCESS_COLOR}"
echo "Built shared object"
echo "Libraries placed in ${LIBRARY_DIRECTORY}/"
echo "${NO_COLOR}"

#Exit early if only building shared object
if [[ "${isSharedOption}" = true ]]; then
  exit 0
fi

#Create test executable and link to above shared object
gcc -L${PWD}/${LIBRARY_DIRECTORY} -Wl,-rpath=${PWD}/${LIBRARY_DIRECTORY} -Wall -o test.out ./test/test.c -lCoOperativeScheduler -I ./include -I../Common/include
mv test.out ./${EXECUTABLE_DIRECTORY}

echo "${SUCCESS_COLOR}Built executables!"
echo "Executables placed in ${EXECUTABLE_DIRECTORY}/"
echo "${NO_COLOR}"

exit 0
