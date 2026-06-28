/*
 * This program follows the first algorithm in the paper
 */

/* INCLUDES */
#include "find_diffs.h"

/* DEFINES */

/* STRUCTS */

/* FUNCTIONS */
void f(uint8_t *input, uint8_t *output, size_t n) {
    // Example encryption function: simple XOR with a constant key
    uint8_t key = 0xAA; // Example key
    for (size_t i = 0; i < n; i++) {
        output[i] = input[i] ^ key;
    }
}
