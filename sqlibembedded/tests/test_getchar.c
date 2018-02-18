#include <stdbool.h>
#include "minunit.h"
#include "test_getchar.h"
#include <sqstdio.h>
#include <results.h>

uint8_t inchar = 'b';
bool testEOF;

result testStreamRead(uint8_t * c)
{
    if(testEOF)
    {
        return streamEOF;
    }
    else
    {
        *c = inchar;    
        return noError;
    }
}

const rStream sqstdindef = {
    testStreamRead,
};

void test_getchar_setup(void) 
{
   
}

void test_getchar_teardown(void) 
{

}

MU_TEST(test_getchar_EOF) 
{
    testEOF = true;
    mu_assert_int_eq(EOF, sqgetchar());
}

MU_TEST(test_getchar_normal) 
{
    testEOF = false;
    inchar = 'a';
    mu_assert_int_eq('a', sqgetchar());
}

MU_TEST_SUITE(test_getchar) 
{
    MU_RUN_TEST(test_getchar_EOF);
    MU_RUN_TEST(test_getchar_normal);
    MU_SUITE_CONFIGURE(&test_getchar_setup, &test_getchar_teardown);
}

void testGetcharSuite()
{
    MU_RUN_SUITE(test_getchar);
    MU_REPORT();
}