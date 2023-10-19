#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_rounds>\n", argv[0]);
        return 1;
    }

    int rounds = atoi(argv[1]);

    if(rounds < 1){
        printf("Number of rounds must be greater than 0.\n");
        return 1;
    }

    int child1_pid;
    int pipefd_child1[2];  // Pipe for child1's score
    int pipefd_child2[2];  // Pipe for child2's score
    int child1_score = 0, child2_score = 0;

    if (pipe(pipefd_child1) == -1 || pipe(pipefd_child2) == -1) {
        perror("pipe");
        return 1;
    }

    printf("Child 1 PID: %d\n", getpid());

    child1_pid = fork();

    if (child1_pid == 0) {
        // Child 1's code
        srand(getpid());

        for (int round = 1; round <= rounds; round++) {
            int choice1, choice2;

            
                choice1 = rand() % 3;
                choice2 = rand() % 3;

            while (1) {
                printf("Round %d:\nChild 1 throws ", round);

                if (choice1 == 0) {
                    printf("Rock!\n");
                } else if (choice1 == 1) {
                    printf("Paper!\n");
                } else {
                    printf("Scissors!\n");
                }

                printf("Child 2 throws ");

                if (choice2 == 0) {
                    printf("Rock!\n");
                } else if (choice2 == 1) {
                    printf("Paper!\n");
                } else {
                    printf("Scissors!\n");
                }

                if ((choice1 == 0 && choice2 == 2) ||
                    (choice1 == 1 && choice2 == 0) ||
                    (choice1 == 2 && choice2 == 1)) {
                    printf("Child 1 Wins!\n");
                    child1_score++;
                    break;  // Exit the loop, there's a winner
                } else if ((choice2 == 0 && choice1 == 2) ||
                           (choice2 == 1 && choice1 == 0) ||
                           (choice2 == 2 && choice1 == 1)) {
                    printf("Child 2 Wins!\n");
                    child2_score++;
                    break;  // Exit the loop, there's a winner
                } else {
                    printf("It's a draw! Redoing the round...\n");
                    printf("---------------------------\n");
                    choice1 = rand() % 3;
                    choice2 = rand() % 3;
                }
            }

            printf("---------------------------\n");
        }

        // Send child1_score back to the parent process
        close(pipefd_child1[0]); // Close the read end of the pipe
        write(pipefd_child1[1], &child1_score, sizeof(child1_score));
        write(pipefd_child2[1], &child2_score, sizeof(child2_score));
        close(pipefd_child1[1]);
        exit(0);
    } else {
        // Parent process
        close(pipefd_child1[1]); // Close the write end of the child1's pipe
        close(pipefd_child2[1]); // Close the write end of the child2's pipe

        printf("Child 2 PID: %d\n", child1_pid);

        // Read and display child1's score
        read(pipefd_child1[0], &child1_score, sizeof(child1_score));
        close(pipefd_child1[0]);
        // Read and display child2's score
        read(pipefd_child2[0], &child2_score, sizeof(child2_score));
        close(pipefd_child2[0]);

        printf("Results:\n");
        printf("Child 1: %d\nChild 2: %d\n", child1_score, child2_score);

        if (child1_score > child2_score) {
            printf("Child 1 Wins!\n");
        } else if (child1_score < child2_score) {
            printf("Child 2 Wins!\n");
        } else {
            printf("It's a draw!\n");
        }
    }

    return 0;
}
