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

bitstring *search(table_manager *manager, size_t index, hkey_t *key) {
    // Get the hash table and lock for the given index
    hash_table *table = manager->tables[index];
    pthread_mutex_t *lock = &manager->locks[index];

    // Lock the hash table
    pthread_mutex_lock(lock);

    // Search for the key in the hash table
    size_t bucket_index = manager->hash(key) % table->size;
    entry *current = table->table[bucket_index];
    while (current != NULL) {
        if (memcmp(current->key, key, sizeof(hkey_t)) == 0) {
            // Unlock the hash table before returning
            pthread_mutex_unlock(lock);
            return current->value;
        }
        current = current->next;
    }

    // Unlock the hash table before returning
    pthread_mutex_unlock(lock);
    return NULL; // Key not found
}

table_manager *create_table_manager(size_t size) {
    table_manager *manager = malloc(sizeof(table_manager));
    manager->tables = malloc(sizeof(hash_table *) * size);
    manager->locks = malloc(sizeof(pthread_mutex_t) * size);
    manager->size = size;
    manager->hash = NULL; // Hash function to be implemented

    for (size_t i = 0; i < size; i++) {
        manager->tables[i] = malloc(sizeof(hash_table));
        manager->tables[i]->table = calloc(MINI_HASH_TABLE_SIZE, sizeof(entry *));
        manager->tables[i]->size = MINI_HASH_TABLE_SIZE;
        pthread_mutex_init(&manager->locks[i], NULL);
    }

    return manager;
}

void free_table_manager(table_manager *manager) {
    for (size_t i = 0; i < manager->size; i++) {
        hash_table *table = manager->tables[i];
        for (size_t j = 0; j < table->size; j++) {
            entry *current = table->table[j];
            while (current != NULL) {
                entry *temp = current;
                current = current->next;
                free(temp->value);
                free(temp);
            }
        }
        free(table->table);
        free(table);
        pthread_mutex_destroy(&manager->locks[i]);
    }
    free(manager->tables);
    free(manager->locks);
    free(manager);
}
