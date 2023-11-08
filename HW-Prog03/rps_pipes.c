// Author: Michael Dandrea
// Class: CSCI 356
// Purpose: This program simulates a game of rock, paper, scissors between two children programs using PThreads
//Professor: Prof. Fuchs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>

#define NUM_ROUNDS 10

struct Score {
    int child1_score;
    int child2_score;
};

void *child1(void *arg) {
    struct Score *score = (struct Score *) arg;
    srand(time(NULL));

    for (int round = 1; round <= NUM_ROUNDS; round++) {
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
                score->child1_score++;
                break;  // Exit the loop, there's a winner
            } else if ((choice2 == 0 && choice1 == 2) ||
                       (choice2 == 1 && choice1 == 0) ||
                       (choice2 == 2 && choice1 == 1)) {
                printf("Child 2 Wins!\n");
                score->child2_score++;
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

    pthread_exit(NULL);
}

void *child2(void *arg) {
    struct Score *score = (struct Score *) arg;
    srand(time(NULL));

    for (int round = 1; round <= NUM_ROUNDS; round++) {
        int choice1, choice2;

        choice1 = rand() % 3;
        choice2 = rand() % 3;

        while (1) {
            printf("Round %d:\nChild 2 throws ", round);

            if (choice2 == 0) {
                printf("Rock!\n");
            } else if (choice2 == 1) {
                printf("Paper!\n");
            } else {
                printf("Scissors!\n");
            }

            printf("Child 1 throws ");

            if (choice1 == 0) {
                printf("Rock!\n");
            } else if (choice1 == 1) {
                printf("Paper!\n");
            } else {
                printf("Scissors!\n");
            }

            if ((choice2 == 0 && choice1 == 2) ||
                (choice2 == 1 && choice1 == 0) ||
                (choice2 == 2 && choice1 == 1)) {
                printf("Child 2 Wins!\n");
                score->child2_score++;
                break;  // Exit the loop, there's a winner
            } else if ((choice1 == 0 && choice2 == 2) ||
                       (choice1 == 1 && choice2 == 0) ||
                       (choice1 == 2 && choice2 == 1)) {
                printf("Child 1 Wins!\n");
                score->child1_score++;
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

    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;
    struct Score score = {0, 0};

    pthread_create(&tid1, NULL, child1, &score);
    pthread_create(&tid2, NULL, child2, &score);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Results:\n");
    printf("Child 1: %d\nChild 2: %d\n", score.child1_score, score.child2_score);

    if (score.child1_score > score.child2_score) {
        printf("Child 1 Wins!\n");
    } else if (score.child1_score < score.child2_score) {
        printf("Child 2 Wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}
