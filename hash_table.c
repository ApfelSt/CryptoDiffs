/*
 * hash_table.c
 * Description: This file contains the implementation of a hash table data structure with thread-safe insert operations. It includes functions to insert key-value pairs into the hash table while ensuring that concurrent access is properly synchronized using mutex locks.
 */

/* INCLUDES */
#include "hash_table.h"

/* DEFINES */

/* STRUCTS */

/* FUNCTIONS */

void insert(table_manager *manager, size_t index, hkey_t *key, bitstring *value) {
    // Get the hash table and lock for the given index
    hash_table *table = manager->tables[index];
    pthread_mutex_t *lock = &manager->locks[index];

    // Create a new entry
    entry *new_entry = malloc(sizeof(entry));
    new_entry->key = key;
    new_entry->value = malloc(sizeof(bitstring) * (sizeof(value) / sizeof(bitstring)));
    memcpy(new_entry->value, value, sizeof(bitstring) * (sizeof(value) / sizeof(bitstring)));
    new_entry->next = NULL;

    // Lock the hash table
    pthread_mutex_lock(lock);

    // Insert the new entry into the hash table
    size_t bucket_index = manager->hash(key) % table->size;
    if (table->table[bucket_index] == NULL) {
        table->table[bucket_index] = new_entry;
    } else {
        entry *current = table->table[bucket_index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_entry;
    }

    // Unlock the hash table
    pthread_mutex_unlock(lock);
}
