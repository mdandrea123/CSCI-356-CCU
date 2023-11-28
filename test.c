// Exam 2 Programming Question
#include <stdio.h>
#include <stdlib.h>
#include "HW-Prog02/customer.h"
#include "HW-Prog02/my_queue.h"
// Did not need to provide #include statements

void main(int argc, char **argv)
{
    int total = 0;
    int count = 0;
    int avg = 0;
    queue q = newqueue();
    if (q == NULL || q->front == NULL)
    {
        return avg;
    }
    q_element *iter = q->front;
    while (iter != NULL)
    {
        Customer *temp = iter->contents;
        total += temp->credit_rating;
        count++;
        iter = iter->next;
    }
    avg = (float) total / count;
    return avg;
}