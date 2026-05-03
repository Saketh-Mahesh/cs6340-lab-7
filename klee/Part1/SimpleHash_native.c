/*
 * Simple Hash Reversal Lab
 *
 * From:
 *   sfold hash function sourced from https://research.cs.vt.edu/AVresearch/hashing/strings.php
 *
 *
 * Author: Justin Dunnaway
 * Modified by: Michael D. Brown
 * Purpose: This code is a graded portion of a KLEE Lab for academic use.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// #include <klee/klee.h>

long long int sfold(char * message, int length) {
        long int seed = 1000;
	long int modulo = 100000000;
	int sum = seed;
        int iter_length = length/4;

        for (int j = 0; j < iter_length; j++) {
                int start_index = j * 4;
                int end_index = (j * 4) + 4;
                long mult = 1;

                if (end_index >= length) {
                        end_index = length - 1;
                }

                int arr_length = end_index - start_index;
                char c[arr_length];
                strncpy(c, &message[start_index], arr_length);

                for (int k = 0; k < arr_length; k++) {
                        sum += ((c[k] << 1) + sum) * mult;
                        mult *= 256;
                }
        }

        long mult = 1;
        for (int k = 0; k < length; k++) {
                sum += ((message[k] << 1) + sum) * mult;
                mult *= 256;
        }

        int mod_value = sum % modulo;

        if (mod_value >= 0) {
                return mod_value;
        } else {
                return (-1)*mod_value;
        }
}

int main(int argc, char *argv[]) {
    long int length = strlen(argv[1]);

    for (int i = 0; i < 20; i++) {
        char c = argv[1][i];
        // klee_assume((c >= '0' & c <= '9') |
        //             (c >= 'A' & c <= 'Z') |
        //             (c >= 'a' & c <= 'z'));
    }

    long int hash = sfold(argv[1], length);
//     klee_assert(hash != 13365056);

    printf("The computed hash value is: %ld .\n", hash);
    return 0;
}

