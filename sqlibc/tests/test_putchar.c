#include <stdbool.h>
#include "minunit.h"
#include "test_putchar.h"
#include <sqstdio.h>

uint8_t outchar;
bool testEOF;

int testStreamWrite(uint8_t c)
{
    if(testEOF)
    {
        return EOF;
    }
    else
    {
        outchar = c;
        return 0;
    }
}

const sqFILE sqstdoutdef = {
    testStreamWrite,
    NULL,
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
    mu_assert_int_eq(0, sqputchar('a'));
    mu_assert_int_eq('a', outchar);
}

MU_TEST_SUITE_GLOBAL(test_putchar) 
{
    MU_RUN_TEST(test_putchar_EOF);
    MU_RUN_TEST(test_putchar_normal);
    MU_SUITE_CONFIGURE(&test_putchar_setup, &test_putchar_teardown);
}

void testPutcharSuite()
{
    MU_RUN_SUITE(test_putchar);
    MU_REPORT();
}