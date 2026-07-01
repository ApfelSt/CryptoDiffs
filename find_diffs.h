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

/* Union: key
 * Description: A key for the hash table
 */
typedef union {
    bitstring *bits;
    uint64_t *int_rep;
    size_t *size_rep;
} hkey_t;

/* Struct: entry
 * Description: An entry in the hash table, containing a key and a value.
 * Members:
 *   - key: pointer to the key (n bits)
 *   - value: pointer to the value (n bits)
 *   - next: pointer to the next entry in the hash table (for collision resolution)
 *   - len: number of values stored in the entry (for collision resolution)
 */
typedef struct entry {
    hkey_t *key;
    bitstring *value;
    struct entry *next;
    uint32_t len;
} entry;

/* Struct: hash_table
 * Description: A hash table that stores entries. It uses separate chaining for collision resolution.
 * Members: 
 *  - table: pointer to an array of entry pointers (the hash table)
 *  - size: the size of the hash table (M)
 */
typedef struct hash_table {
    entry **table;
    size_t size;
} hash_table;

/* Struct: table_manager
 * Description: holds all the hash tables, and a lock for each hash table.
 * Members:
 *  - tables: pointer to an array of hash_table pointers (the hash tables)
 *  - locks: pointer to an array of pthread_mutex_t (the locks for each mini hash table)
 *  - size: the number of mini hash tables (NUM_THREADS)
 *  - hash: pointer to the hash function used to hash the keys (not implemented yet).
 */
typedef struct table_manager {
    hash_table **tables;
    pthread_mutex_t *locks;
    size_t size;
    size_t (*hash)(hkey_t *key);
} table_manager;

/* FUNCTIONS */

/*
 * Function: f
 * Description: This is the encryption function from n bits to n bits.
 * Parameters:
 *   - input: pointer to the input data (n bits)
 *   - output: pointer to the output data (n bits)
 *   - n: number of bits in the input and output data
 * Returns: void
 */
void f(bitstring *input, bitstring *output, size_t n);

/*
 * Function: g_gamma
 * Description: f(x) XOR f(x XOR gamma)
 * Parameters:
 *   - input: pointer to x (n bits)
 *   - gamma: pointer to gamma (n bits)
 *   - output: pointer to the output data (n bits)
 *   - n: number of bits in the input and output data
 * Returns: void
 */
void g_gamma(bitstring *input, bitstring *gamma, bitstring *output, size_t n);

/*
 * Function: insert
 * Description: Inserts a key-value pair into the table.
 * Parameters:
 *  - table: pointer to the hash table manager
 *  - index: index of the mini hash table to insert into
 *  - key: pointer to the key to be inserted (n bits)
 *  - value: pointer to the value to be inserted (n bits)
 * Returns: void
 */
void insert(table_manager *table, size_t index, hkey_t *key, bitstring *value);
