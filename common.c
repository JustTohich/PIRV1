#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <memory.h>

#include "common.h"

static inline void dot_multiple(int* a, int *b, int *c, int i_from, int i_to, int j_from, int j_to, int k_from, int k_to, int n, int par_type) {
#pragma omp parallel for if (par_type == 1)
    for (int i = i_from; i < i_to; i++) {
#pragma omp parallel for if (par_type == 2)
        for (int j = j_from; j < j_to; j++) {
            for (int k = k_from; k < k_to; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}

void block_multiple(int *a, int *b, int *c, int n, int r, int par_type) {
    if (r == 1 || n == r) {
        dot_multiple(a, b, c, 0, n, 0, n, 0, n, n, par_type);
        return;
    }
#pragma omp parallel for if (par_type == 1)
    for (int i = 0; i < n / r; i++) {
#pragma omp parallel for if (par_type == 2)
        for (int j = 0; j < n / r; j++) {
            for (int k = 0; k < n / r; k++) {
                dot_multiple(a, b, c, i * r, (i + 1) * r, j * r, (j + 1) * r, k * r, (k + 1) * r, n, 0);
            }
        }
    }
}

int *generate_matrix(int n) {
    int *a = (int *)malloc(n * n * sizeof(int));
    for (int i = 0; i < n * n; ++i) {
        a[i] = rand() % 201 - 100;
    }
    return a;
}

FILE *open_output(const char* filename) {
    int results_exist = 0;
    FILE *results = fopen(filename,"r");
    if (results) {
        results_exist = 1;
        fclose(results);
    }
    results = fopen(filename, "a");
    if (!results_exist) {
        fprintf(results, "%s,%s,%s,%s\n", "n", "r", "parallel_type", "time");
        fflush(results);
    }
    return results;
}

void run(int n, int block_size) {
    FILE *file = open_output("output.csv");
    double wtime;
    int par_type;
    int *a = generate_matrix(n);
    int *b = generate_matrix(n);
    int *c = (int *)malloc(n * n * sizeof(int));
    memset(c, 0, n * n * sizeof(int));

    for (par_type = 0; par_type < 3; par_type++) {
        wtime = omp_get_wtime();
        block_multiple(a, b, c, n, block_size, par_type);
        wtime = omp_get_wtime() - wtime;
        memset(c, 0, n * n * sizeof(int));
        fprintf(file, "%d,%d,%d,%f\n", n, block_size, par_type, wtime);
    }

    free(a);
    free(b);
    free(c);
}