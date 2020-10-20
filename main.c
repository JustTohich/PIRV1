#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <memory.h>

#include "common.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    int n = 0, block_size = 0, t = 8;

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-n") == 0) {
            n = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-r") == 0) {
            block_size = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            t = atoi(argv[i + 1]);
        } else {
            return 1;
        }
    }

    if (n == 0 || block_size == 0) {
        return 1;
    }

    omp_set_dynamic(0);
    omp_set_num_threads(t);

    run(n, block_size);

    return 0;
}
