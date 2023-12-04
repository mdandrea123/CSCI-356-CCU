#!/bin/bash

echo "-----------------COMPILE THE PROGRAM-----------------"
make clean all
echo "-----------------RUN THE PROGRAM-----------------"
echo "-----------------PRINT THE USAGE-----------------"
 ./scheduler
echo "-----------------Cretae input.txt-----------------"
echo "1 0 10
2 0 9
3 3 5
4 7 4
5 10 6
6 10 7
0 0 0" > input.txt
echo "-----------------TEST WITH FCFS-----------------"
./scheduler FCFS <<< "$(cat input.txt)"
echo "-----------------TEST WITH RR-----------------"
./scheduler RR 2 <<< "$(cat input.txt)"
 echo "-----------------ERROR: TEST WITH NEGATIVE-----------------"
 ./scheduler FCFS <<< "-1 2 3"
 ./scheduler FCFS <<< "1 -2 3"
 ./scheduler FCFS <<< "1 2 -3"