#include "minunit.h"
#include "test_strlen.h"

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_strlen);
    MU_REPORT();
    return 0;
}
