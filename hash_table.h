/*
 * File: hash_table.h
 * Description: Header file for the hash table implementation.
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
#include "utils.h"

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

/*
 * Function: search
 * Description: Searches for a key in the table and returns the corresponding value.
 * Parameters:
 *  - table: pointer to the hash table manager
 *  - index: index of the mini hash table to search in
 *  - key: pointer to the key to be searched (n bits)
 * Returns: pointer to the value corresponding to the key (n bits), or NULL if not found
 */
bitstring *search(table_manager *table, size_t index, hkey_t *key);

/*
 * Function: create_table_manager
 * Description: Creates a new table manager with the specified number of mini hash tables.
 * Parameters:
 *  - size: the number of mini hash tables to create (NUM_THREADS)
 * Returns: pointer to the newly created table manager
 */
table_manager *create_table_manager(size_t size);

/*
 * Function: free_table_manager
 * Description: Frees the memory allocated for the table manager and its mini hash tables.
 * Parameters:
 *  - manager: pointer to the table manager to be freed
 * Returns: void
 */
void free_table_manager(table_manager *manager);

/*
 * Function: hash_function
 * Description: A simple hash function that hashes a key to an index in the hash table.
 * Parameters:
 *  - key: pointer to the key to be hashed (n bits)
 * Returns: the index in the hash table corresponding to the key
 */
size_t hash_function(hkey_t *key);
