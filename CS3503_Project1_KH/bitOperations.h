#ifndef BITOPERATIONS_H   // uppercase header guard
#define BITOPERATIONS_H

#include <stdint.h>

// Basic bit operations (lowercase function names)
uint64_t setBit(uint64_t value, int position);
uint64_t clearBit(uint64_t value, int position);
uint64_t flipBit(uint64_t value, int position);
int getBit(uint64_t value, int position);

// Counting and shifting
int countBits(uint64_t value);
uint64_t shiftLeft(uint64_t value, int positions);
uint64_t shiftRight(uint64_t value, int positions);

// Display helpers
void printBinary(uint64_t value);
void printHex(uint64_t value);

#endif