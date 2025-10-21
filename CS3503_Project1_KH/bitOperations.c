#include "bitOperations.h"
#include <stdio.h>

uint64_t setBit(uint64_t value, int position) {
    if (position < 0 || position >= 64) return value;
    return value | (1ULL << position);
}

uint64_t clearBit(uint64_t value, int position) {
    if (position < 0 || position >= 64) return value;
    return value & ~(1ULL << position);
}

uint64_t flipBit(uint64_t value, int position) {
    if (position < 0 || position >= 64) return value;
    return value ^ (1ULL << position);
}

int getBit(uint64_t value, int position) {
    if (position < 0 || position >= 64) return 0;
    return (value >> position) & 1ULL;
}

int countBits(uint64_t value) {
    int count = 0;
    while (value) {
        count += value & 1ULL;
        value >>= 1;
    }
    return count;
}

uint64_t shiftLeft(uint64_t value, int positions) {
    return value << positions;
}

uint64_t shiftRight(uint64_t value, int positions) {
    return value >> positions;
}

void printBinary(uint64_t value) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", getBit(value, i));
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

void printHex(uint64_t value) {
    printf("0x%016llX\n", value);
}