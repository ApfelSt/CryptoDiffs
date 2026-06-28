#pragma once

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include "find_diffs.h"

/* DEFINES */

// placeholders
#define p 0.2
#define n 64
#define M sqrt(n) * pow(2, n / 2) * (1 / p)

/* STRUCTS */

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
void f(uint8_t *input, uint8_t *output, size_t n);

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
void g_gamma(uint8_t *input, uint8_t *gamma, uint8_t *output, size_t n);


