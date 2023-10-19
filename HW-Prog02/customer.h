/*
 * customer.h - Header file for the Customer struct
 *
 * Author: Michael Dandrea
 * Course: CSCI 356
 * Date: 10/13/2023
 */
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

struct Customer {
    char name[50];
    int credit_rating;
};

typedef struct Customer Customer;

#endif /* CUSTOMER_H_ */
