#! /usr/bin/bash

clear
cmake .
make
 xboard -fcp "./3_Check_Chess" -debug
 bash clear.sh