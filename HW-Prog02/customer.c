/*
 * customer.c - Main program using the queue and Customer struct
 *
 * Author: Michael Dandrea
 * Course: CSCI 356
 * Date: 10/13/2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_queue.h"
#include "customer.h"

int main()
{
    // Create a new queue to store customer data
    queue customer_queue = newqueue();

    char input[100];
    int min_value = 0;
    int total_credit = 0;
    int customer_count = 0;

    printf("Customers\n");

    // Begin an infinite loop to input customer data
    while (1)
    {
        printf("Enter customer data (Name Credit) or press Enter to stop: ");
        fgets(input, sizeof(input), stdin);

        // If the input is empty, exit the loop
        if (strlen(input) <= 1)
        {
            break;
        }

        // Create a customer structure to store the data
        struct Customer customer;

        // Parse the input for customer name and credit rating
        if (sscanf(input, "%s %d", customer.name, &customer.credit_rating) == 2)
        {
            // Create a copy of the customer and add it to the queue
            struct Customer *customer_copy = malloc(sizeof(struct Customer));
            strcpy(customer_copy->name, customer.name);
            customer_copy->credit_rating = customer.credit_rating;
            enqueue(customer_queue, customer_copy);

            // Update the minimum credit rating and total credit
            if (customer.credit_rating < min_value)
            {
                min_value = customer.credit_rating;
            }
            total_credit += customer.credit_rating;
            customer_count++;
        }
        else
        {
            // Invalid input format, prompt the user to enter data in the correct format
            printf("Invalid input. Please enter data in the format: name credit_rating\n");
        }
    }

    if (customer_count > 0)
    {
        // Calculate the average credit rating
        int average = total_credit / customer_count;
        printf("\nName\tData\tDistance\n");

        // Process each customer in the queue
        while (!isempty(customer_queue))
        {
            struct Customer *customer = dequeue(customer_queue);
            int distance = abs(customer->credit_rating - average);

            // Print customer data and credit rating distance from the average
            printf("%s\t%d\t%d\n", customer->name, customer->credit_rating, distance);

            // Free the memory allocated for the customer structure
            free(customer);
        }

        // Display the average credit rating
        printf("\nAverage: %d\n", average);
    }
    else
    {
        // No customers entered
        printf("No customers entered.\n");
    }

    // Free the memory allocated for the customer queue
    free(customer_queue);
    return 0;
}
