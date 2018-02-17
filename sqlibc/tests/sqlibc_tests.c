#include "minunit.h"
#include "test_strlen.h"
#include "test_strto.h"
#include "test_strtok.h"
#include "test_putchar.h"

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_strlen);
    MU_REPORT();
    testStrtoSuite();
    MU_RUN_SUITE(test_strtok);
    MU_REPORT();
    MU_RUN_SUITE(test_putchar);
    MU_REPORT();
    return 0;
}
