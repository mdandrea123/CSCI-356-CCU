# Scheduler.c

## Description
`scheduler.c` is a program that simulates the First Come First Served (FCFS) and Round Robin (RR) scheduling algorithms. 
It uses a queue data structure to manage tasks, each with a unique ID.

## Compilation
This program comes with a Makefile to compile it. To use it, you can enter either 'make clean all' to for a completely fresh compilation,
or 'make all' to only compile things that have been changed.

## Usage
To run the program, use the command `./scheduler <algorithm> <quantum>`, where `<algorithm>` is either `FCFS` for First Come First Served or `RR` for Round Robin,
and `<quantum>` is the time quantum for the Round Robin algorithm. 

For example, to run the program with the FCFS algorithm, use `./scheduler FCFS`. To run it with the RR algorithm with a time quantum of 2, use `./scheduler RR 2`.

After starting the program, enter tasks in the format: `<id> <arrival_time> <burst_time>`. Enter `0` for all fields when you're done.

## Testing
This also comes with a shell script 'run.sh' which includes all off the tests I ran on this program. To use it, use the command 'bash run.sh'.
