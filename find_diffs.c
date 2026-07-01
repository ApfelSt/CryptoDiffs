/*
 * This program follows the first algorithm in the paper
 */

/* INCLUDES */
#include "find_diffs.h"

/* DEFINES */

/* STRUCTS */

/* FUNCTIONS */

void f(bitstring *input, bitstring *output, size_t n) {
    //TODO: implement real f. For now, just copy input to output
    for (size_t i = 0; i < n; i++) {
        output[i] = input[i];
    }
}

void g_gamma(bitstring *input, bitstring *gamma, bitstring *output, size_t n) {
    bitstring *f_input = malloc(n);
    bitstring *input_xor_gamma = malloc(n);
    bitstring *f_input_xor_gamma = malloc(n);
    f(input, f_input, n);

    for (size_t i = 0; i < n; i++) {
        input_xor_gamma[i] = input[i] ^ gamma[i];
    }

    f(input_xor_gamma, f_input_xor_gamma, n);
    
    for (size_t i = 0; i < n; i++) {
        output[i] = f_input[i] ^ f_input_xor_gamma[i];
    }

    free(f_input);
    free(input_xor_gamma);
    free(f_input_xor_gamma);
}

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
