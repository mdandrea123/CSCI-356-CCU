/*
 * scheduler.c - Simulation of First Come First Served and Round Robin scheduling algorithms using my_queue.c from HW-Prog02
 *
 * Author: Michael Dandrea
 * Course: CSCI 356
 * Date: 12/1/2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my_queue.h"

typedef struct
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int has_started;
} Task;

void simulateFCFS(queue q)
{
    int time = 0;
    queue arrived_q = newqueue(); // Create a queue for arrived processes
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_turnaround_time = 0;
    int total_cpu_usage = 0;
    int num_tasks = 0;

    // Process until the queue is empty
    while (!isempty(q) || !isempty(arrived_q)) // Continue until both queues are empty
    {
        // Check if any process is arriving at the current time
        while (!isempty(q) && ((Task *)peek(q))->arrival_time <= time)
        {
            Task *arriving_task = dequeue(q);
            enqueue(arrived_q, arriving_task); // Enqueue to the arrived queue
            printf("%d %d arriving\n", time, arriving_task->id);
        }

        if (!isempty(arrived_q)) // Only dequeue from arrived queue if it's not empty
        {
            Task *current_task = dequeue(arrived_q);

            if (current_task->start_time == -1)
            {
                current_task->start_time = time;
                int response_time = time - current_task->arrival_time;
                total_response_time += response_time; // Add response time only when the task starts for the first time
                current_task->has_started = 1;        // Set the flag
            }

            // Process the current task based on the Round Robin logic and quantum
            int run_time = current_task->remaining_time;
            for (int i = 0; i < run_time; i++)
            {
                printf("%d %d running\n", time, current_task->id);
                time++;

                // Check if any process is arriving at the current time
                while (!isempty(q) && ((Task *)peek(q))->arrival_time <= time)
                {
                    Task *arriving_task = dequeue(q);
                    enqueue(arrived_q, arriving_task); // Enqueue to the arrived queue
                    printf("%d %d arriving\n", time, arriving_task->id);
                }
            }
            current_task->remaining_time -= run_time;

            // If the task is not finished, enqueue it back to the arrived queue
            if (current_task->remaining_time > 0)
            {
                enqueue(arrived_q, current_task);
            }
            else
            {
                printf("%d %d finished\n", time, current_task->id); // Print when a task has finished

                int waiting_time = time - current_task->arrival_time - current_task->burst_time;
                int turnaround_time = time - current_task->arrival_time;
                int cpu_usage = current_task->burst_time;

                total_waiting_time += waiting_time;
                total_turnaround_time += turnaround_time;
                total_cpu_usage += cpu_usage;

                num_tasks++;
            }
        }
        else
        {
            printf("%d waiting\n", time); // Print "waiting" if no tasks have arrived yet
            time++;                       // Increment the time
        }
    }

    // Calculate averages
    double avg_waiting_time = (double)total_waiting_time / num_tasks;
    double avg_response_time = (double)total_response_time / num_tasks;
    double avg_turnaround_time = (double)total_turnaround_time / num_tasks;
    double avg_cpu_usage = (double)total_cpu_usage / time;

    // Print averages
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Response Time: %.2f\n", avg_response_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average CPU Usage: %.2f%%\n", avg_cpu_usage * 100);
}

void simulateRR(queue q, int quantum)
{
    int time = 0;
    queue arrived_q = newqueue(); // Create a queue for arrived processes

    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_turnaround_time = 0;
    int total_cpu_usage = 0;
    int num_tasks = 0;

    // Process until the queue is empty
    while (!isempty(q) || !isempty(arrived_q)) // Continue until both queues are empty
    {
        // Check if any process is arriving at the current time
        while (!isempty(q) && ((Task *)peek(q))->arrival_time <= time)
        {
            Task *arriving_task = dequeue(q);
            enqueue(arrived_q, arriving_task); // Enqueue to the arrived queue
            printf("%d %d arriving\n", time, arriving_task->id);
        }

        if (!isempty(arrived_q)) // Only dequeue from arrived queue if it's not empty
        {
            Task *current_task = dequeue(arrived_q);

            if (current_task->start_time == -1)
            {
                current_task->start_time = time;
                int response_time = time - current_task->arrival_time;
                total_response_time += response_time; // Add response time only when the task starts for the first time
                current_task->has_started = 1;        // Set the flag
            }

            // Process the current task based on the Round Robin logic and quantum
            int run_time = current_task->remaining_time > quantum ? quantum : current_task->remaining_time;
            for (int i = 0; i < run_time; i++)
            {
                printf("%d %d running\n", time, current_task->id);
                time++;

                // Check if any process is arriving at the current time
                while (!isempty(q) && ((Task *)peek(q))->arrival_time <= time)
                {
                    Task *arriving_task = dequeue(q);
                    enqueue(arrived_q, arriving_task); // Enqueue to the arrived queue
                    printf("%d %d arriving\n", time, arriving_task->id);
                }
            }
            current_task->remaining_time -= run_time;

            // If the task is not finished, enqueue it back to the arrived queue
            if (current_task->remaining_time > 0)
            {
                enqueue(arrived_q, current_task);
            }
            else
            {
                printf("%d %d finished\n", time, current_task->id); // Print when a task has finished

                int waiting_time = time - current_task->arrival_time - current_task->burst_time;
                int turnaround_time = time - current_task->arrival_time;
                int cpu_usage = current_task->burst_time;

                total_waiting_time += waiting_time;
                total_turnaround_time += turnaround_time;
                total_cpu_usage += cpu_usage;
                num_tasks++;
            }
        }
        else
        {
            printf("%d waiting\n", time); // Print "waiting" if no tasks have arrived yet
            time++;                       // Increment the time
        }
    }

    // Calculate the averages
    double avg_waiting_time = (double)total_waiting_time / num_tasks;
    double avg_response_time = (double)total_response_time / num_tasks;
    double avg_turnaround_time = (double)total_turnaround_time / num_tasks;
    double avg_cpu_usage = (double)total_cpu_usage / time;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Response Time: %.2f\n", avg_response_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average CPU Usage: %.2f%%\n", avg_cpu_usage * 100);
}

int main(int argc, char **argv)
{
    int quantum;
    queue q = newqueue();
    int *id_list = NULL; // Array to store entered IDs
    int id_count = 0;    // Counter for entered IDs

    if (argc < 2)
    {
        printf("Usage: ./scheduler <algorithm> <quantum>\n");
        printf("Example: ./scheduler FCFS\n");
        printf("Example: ./scheduler RR 2\n");
        exit(1);
    }
    if (argc != 3 && (strcmp(argv[1], "RR") == 0 || strcmp(argv[1], "rr") == 0))
    {
        printf("Usage: ./scheduler <algorithm> <quantum>\n");
        printf("Round Robin requires a quantum value.\n");
        exit(1);
    }
    if (argc != 2 && (strcmp(argv[1], "FCFS") == 0 || strcmp(argv[1], "fcfs") == 0))
    {
        printf("Usage: ./scheduler <algorithm>\n");
        printf("First Come First Served does not require a quantum value.\n");
        exit(1);
    }
    if (strcmp(argv[1], "FCFS") != 0 && strcmp(argv[1], "fcfs") != 0 && strcmp(argv[1], "RR") != 0 && strcmp(argv[1], "rr") != 0)
    {
        printf("Usage: ./scheduler <algorithm> <quantum>\n");
        printf("Algorithm must be either FCFS or RR.\n");
        exit(1);
    }
    if (strcmp(argv[1], "RR") == 0 || strcmp(argv[1], "rr") == 0)
    {
        quantum = atoi(argv[2]);
        if (quantum <= 0)
        {
            printf("Usage: ./scheduler <algorithm> <quantum>\n");
            printf("Quantum must be a positive integer.\n");
            exit(1);
        }
    }

    printf("Enter tasks in the format: <id> <arrival_time> <burst_time>\n");
    printf("Enter 0 for everything when you're done.\n");

    int id, arrival_time, burst_time;
    while (1)
    {
        scanf("%d", &id);
        if (id == 0)
        {
            break;
        }
        scanf("%d %d", &arrival_time, &burst_time);
        if (id < 0 || arrival_time < 0 || burst_time < 0)
        {
            printf("Id, arrival time and burst time must be positive integers.\n");
            exit(1);
        }

        // Check if the entered ID is already in the list
        for (int i = 0; i < id_count; i++)
        {
            if (id == id_list[i])
            {
                printf("ID %d is not unique. Please enter a unique ID.\n", id);
                exit(1);
            }
        }

        // Check if the entered ID is in ascending order
        if (id_count > 0 && id <= id_list[id_count - 1])
        {
            printf("IDs must be entered in ascending order. Please enter a higher ID.\n");
            exit(1);
        }

        // Add the ID to the list
        id_list = realloc(id_list, (id_count + 1) * sizeof(int));
        id_list[id_count] = id;
        id_count++;

        Task *task = malloc(sizeof(Task));
        task->id = id;
        task->arrival_time = arrival_time;
        task->burst_time = burst_time;
        task->remaining_time = burst_time;
        task->start_time = -1;
        enqueue(q, task);
    }

    if (strcmp(argv[1], "FCFS") == 0 || strcmp(argv[1], "fcfs") == 0)
    {
        simulateFCFS(q);
    }
    else if (strcmp(argv[1], "RR") == 0 || strcmp(argv[1], "rr") == 0)
    {
        quantum = atoi(argv[2]);
        simulateRR(q, quantum);
    }

    free(q);
    free(id_list);

    return 0;
}