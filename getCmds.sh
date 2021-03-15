#! /usr/bin/bash

g++ makeCmdFromDebugFile.cpp

for i in $(ls err); do
    ./a.out err/$i
    echo -e "\n"
done

rm a.out