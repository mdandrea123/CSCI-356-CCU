//Author: Michael Dandrea
//Class: CSCI 356
//Professor Fuchs
//Description: This program is a rock paper scissors game between two child threads using sockets for communication.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Function Prototypes
void play_round(int round, char *child_name, int socket_fd);
void run_child(int child_num, char *child_name, int socket_fd);

int main(int argc, char *argv[]) {
    // Check for command line errors
    if(argc != 2) {
        printf("Usage: %s <number_of_rounds>\n", argv[0]);
        exit(1);
    }
    if(atoi(argv[1]) < 1) {
        printf("Error: Number of rounds must be greater than 0\n");
        exit(1);
    }

    // Get the number of rounds from the command line
    int numRounds = atoi(argv[1]);

    // Seed the random number generator
    srand(time(NULL));

    // initialize variables
    pid_t child1_pid, child2_pid;
    int round = 0;
    int sockets[2];
    char child1_name[] = "Child 1";
    char child2_name[] = "Child 2";

    // Create sockets
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    child1_pid = fork();

    if (child1_pid == 0) {
        // Child 1
        run_child(1, child1_name, sockets[0]);
    } else {
        // Child 2
        child2_pid = fork();
        if (child2_pid == 0) {
            // Child 2
            run_child(2, child2_name, sockets[1]);
        } else {
            // Parent
            printf("%s PID: %d\n", child1_name, child1_pid);
            printf("%s PID: %d\n", child2_name, child2_pid);
            printf("Beginning %d Round%s...\n", numRounds, numRounds == 1 ? "" : "s");
            printf("Fight!\n");
            printf("-------------------------------");

            // Initialize variables
            int child1_wins = 0;
            int child2_wins = 0;

            // Keep playing rounds until the number of rounds is reached
            while (round < numRounds) {
                // Increment the round
                round++;

                // Initialize variables
                int choice1, choice2;
                printf("\nRound %d:\n", round);

                // Keep playing until there is a winner
                do {
                    choice1 = rand() % 3;
                    choice2 = rand() % 3;

                    printf("%s throws %s!\n", child1_name, choice1 == 0 ? "Rock" : (choice1 == 1 ? "Paper" : "Scissors"));
                    printf("%s throws %s!\n", child2_name, choice2 == 0 ? "Rock" : (choice2 == 1 ? "Paper" : "Scissors"));

                    if (choice1 == choice2) {
                        printf("\nIt's a tie! Redoing the round:\n");
                    }
                } while (choice1 == choice2);

                // Print the winner
                if ((choice1 == 0 && choice2 == 2) || (choice1 == 1 && choice2 == 0) || (choice1 == 2 && choice2 == 1)) {
                    printf("%s Wins!\n", child1_name);
                    child1_wins++;
                } else {
                    printf("%s Wins!\n", child2_name);
                    child2_wins++;
                }
                printf("-------------------------------");
            }

            // Send termination signal
            int choice1 = -1;
            int choice2 = -1;
            write(sockets[0], &choice1, sizeof(int));
            write(sockets[1], &choice2, sizeof(int));

            // Close the sockets
            close(sockets[0]);
            close(sockets[1]);

            // Wait for the children to finish
            wait(NULL);
            wait(NULL);

            // Print the results
            printf("\nResults:\n");
            printf("%s: %d\n", child1_name, child1_wins);
            printf("%s: %d\n", child2_name, child2_wins);

            // Print the winner
            if (child1_wins > child2_wins) {
                printf("%s Wins!\n", child1_name);
            } else if (child2_wins > child1_wins) {
                printf("%s Wins!\n", child2_name);
            } else {
                printf("It's a Tie!\n");
            }
        }
    }

    return 0;
}

void play_round(int round, char *child_name, int socket_fd) {
    // Keep track of the child's choice
    int choice = 0;
    // Print child's choice
    while (1) {
        // Error check
        if (read(socket_fd, &choice, sizeof(int)) == -1 || choice == -1) {
            break;
        }
        printf("%s throws %s!\n", child_name, choice == 0 ? "Rock" : (choice == 1 ? "Paper" : "Scissors"));
    }
    close(socket_fd);
}

void run_child(int child_num, char *child_name, int socket_fd) {
    // Call play_round to play the round
    play_round(1, child_name, socket_fd);
    exit(0);
}
