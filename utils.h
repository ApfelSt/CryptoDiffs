/*
 * utils.h
 * Description: This file contains utility functions and definitions for the whole project.
 */

#pragma once

/* INCLUDES */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>

/* DEFINES */

// placeholders
#define p 0.2
#define n 64
#define M sqrt(n) * pow(2, n / 2) * (1 / p)
#define NUM_THREADS 4
#define MINI_HASH_TABLE_SIZE 1000

/* STRUCTS */

/* Typedef: bitstring
 * Description: A bitstring of length n.
 */
typedef uint64_t bitstring;

/* Struct: Tuple
 * Description: A tuple containing two bitstrings.
 * Members:
 *  - first: the first bitstring
 *  - second: the second bitstring
 */
typedef struct {
    bitstring first;
    bitstring second;
} Tuple;

/* Union: key
 * Description: A key for the hash table
 */
typedef union {
    bitstring *bits;
    uint64_t *int_rep;
    size_t *size_rep;
    Tuple *tuple_rep;
} hkey_t;

