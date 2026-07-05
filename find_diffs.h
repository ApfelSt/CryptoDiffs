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
#include "hash_table.h"
#include "utils.h"

/* DEFINES */

/* FUNCTIONS */

/*
 * Function: f
 * Description: This is the encryption function from n bits to n bits.
 * Parameters:
 *   - input: pointer to the input data (n bits)
 *   - output: pointer to the output data (n bits)
 * Returns: void
 */
void f(bitstring *input, bitstring *output);

/*
 * Function: g_gamma
 * Description: f(x) XOR f(x XOR gamma)
 * Parameters:
 *   - input: pointer to x (n bits)
 *   - gamma: pointer to gamma (n bits)
 *   - output: pointer to the output data (n bits)
 * Returns: void
 */
void g_gamma(bitstring *input, bitstring *gamma, bitstring *output);

