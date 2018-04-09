#include <stdbool.h>
#include "minunit.h"
#include "test_putchar.h"
#include <sqstdio.h>

uint8_t outchar;
bool testEOF;

result testStreamWrite(uint8_t c)
{
    if(testEOF)
    {
        return streamEOF;
    }
    else
    {
        outchar = c;
        return noError;
    }
}

const wStream sqstdoutdef = {
    testStreamWrite,
};

void test_putchar_setup(void) 
{
   
}

void test_putchar_teardown(void) 
{

}

MU_TEST(test_putchar_EOF) 
{
    testEOF = true;
    mu_assert_int_eq(EOF, sqputchar('a'));
}

MU_TEST(test_putchar_normal) 
{
    testEOF = false;
    mu_assert_int_eq('a', sqputchar('a'));
    mu_assert_int_eq('a', outchar);
}

MU_TEST_SUITE(test_putchar) 
{
    MU_RUN_TEST(test_putchar_EOF);
    MU_RUN_TEST(test_putchar_normal);
    MU_SUITE_CONFIGURE(&test_putchar_setup, &test_putchar_teardown);
}

int testPutcharSuite()
{
    MU_RUN_SUITE(test_putchar);
    MU_REPORT();
    return minunit_fail;
}