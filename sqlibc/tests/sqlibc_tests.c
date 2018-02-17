#include "minunit.h"
#include "test_strlen.h"
#include "test_strto.h"
#include "test_strtok.h"
#include "test_putchar.h"
#include "test_getchar.h"


int main(int argc, char *argv[]) {
    testStrlenSuite();
    testStrtoSuite();
    testStrtokSuite();
    testPutcharSuite();
    testGetcharSuite();
    return 0;
}
