#include "minunit.h"
#include "test_strlen.h"
#include "test_strto.h"

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_strlen);
    MU_RUN_SUITE(test_strto);
    MU_RUN_SUITE(test_strtok);
    MU_REPORT();
    return 0;
}
