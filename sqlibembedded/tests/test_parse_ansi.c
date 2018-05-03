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
    mu_check(ansiParse('a') == ansiError);
}

MU_TEST(testParseAnsiUnknownEscapes)
{
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('_') == ansiError);
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('_') == ansiError);    
}

MU_TEST(testParseAnsiCursorUp)
{
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('A') == ansiCursorUp);
}

MU_TEST(testParseAnsiCursorForward)
{
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('C') == ansiCursorForward);
}

MU_TEST(testParseAnsiInvalidValidInvalid)
{
    mu_check(ansiParse('a') == ansiError);
    mu_check(ansiParse('\e') == ansiEntered);
    mu_check(ansiParse('[') == ansiBrackOpen);
    mu_check(ansiParse('C') == ansiCursorForward);
    mu_check(ansiParse('a') == ansiError);
}

MU_TEST_SUITE(testParseAnsi) 
{
    MU_SUITE_CONFIGURE(&testParseAnsiSetup, &testParseAnsiTeardown);
    MU_RUN_TEST(testParseAnsiEmpty);
    MU_RUN_TEST(testParseAnsiUnknownEscapes);
    MU_RUN_TEST(testParseAnsiCursorUp);
    MU_RUN_TEST(testParseAnsiCursorForward);
    MU_RUN_TEST(testParseAnsiInvalidValidInvalid);
}

int testParseAnsiSuite()
{
    MU_RUN_SUITE(testParseAnsi);
    MU_REPORT();
    return minunit_fail;
}