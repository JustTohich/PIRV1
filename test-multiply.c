#include "common.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int a[] = {42, 0, 0, 0,
               0, 42, 0, 0,
               0, 0, 42, 0,
               0, 0, 0, 42};
    int *b = generate_matrix(4);
    int c[16] = {0};

    block_multiple(a, b, c, 4, 1, 0);
    for (int i = 0; i < 16; ++i) {
        assert(c[i] == 42 * b[i]);
    }

    memset(c, 0, sizeof(c));
    block_multiple(a, b, c, 4, 2, 0);
    for (int i = 0; i < 16; ++i) {
        assert(c[i] == 42 * b[i]);
    }

    memset(c, 0, sizeof(c));
    block_multiple(a, b, c, 4, 4, 0);
    for (int i = 0; i < 16; ++i) {
        assert(c[i] == 42 * b[i]);
    }

    free(b);

    return 0;
}
