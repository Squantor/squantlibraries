#include <minunit.h>
#include <test_parse_ansi.h>
#include <parse_ansi.h>


void testParseAnsiSetup(void) 
{
}

void testParseAnsiTeardown(void) 
{

}

MU_TEST(testParseAnsiEmpty) 
{
    ;
}

MU_TEST_SUITE(testParseAnsi) 
{
    MU_SUITE_CONFIGURE(&testParseAnsiSetup, &testParseAnsiTeardown);
    MU_RUN_TEST(testParseAnsiEmpty);
}

int testParseAnsiSuite()
{
    MU_RUN_SUITE(testParseAnsi);
    MU_REPORT();
    return minunit_fail;
}