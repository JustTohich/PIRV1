#include <stdio.h>
#include <assert.h>
#include "common.h"

static void check_output(void) {
    FILE *f = fopen("output.csv", "r");
    assert(f);
    fclose(f);
}

int main(int argc, char** argv) {
    remove("output.csv");

    run(500, 1);
    run(500, 5);
    run(500, 25);
    run(500, 50);
    run(500, 100);

    check_output();
}
