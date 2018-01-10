#include "minunit.h"
#include "test_strtok.h"
#include <sqstring.h>

static const char strtok_whitespaces[] = " \n\r\t";
static char strtok_test_empty[] = "";
static char strtok_test_no_tok[] = "    \t   \r";
static char strtok_test_tokonly[] = "foo";
static char strtok_test_tokspaced[] = "   baz    ";
static char strtok_test_multitokspaced[] = " neodymium    foo\t zapfff\tmoo \n\r";

void test_strtok_setup(void) 
{
    
}

void test_strtok_teardown(void) 
{

}

MU_TEST(test_sqstrstok) 
{
    char *token;
    mu_assert(sqstrtok(strtok_test_empty, strtok_whitespaces) == NULL, "sqstrtok(strtok_test_empty, strtok_whitespaces) != NULL");
    mu_assert(sqstrtok(strtok_test_no_tok, strtok_whitespaces) == NULL, "sqstrtok(strtok_test_empty, strtok_whitespaces) != NULL");
    
    token = sqstrtok(strtok_test_tokonly, strtok_whitespaces);
    mu_assert(token != NULL, "sqstrtok(strtok_test_tokonly, strtok_whitespaces) == NULL");
    mu_assert_string_eq("foo", token);
    
    token = sqstrtok(strtok_test_tokspaced, strtok_whitespaces);
    mu_assert(token != NULL, "sqstrtok(strtok_test_tokspaced, strtok_whitespaces) == NULL");
    mu_assert_string_eq("baz", token);
    
    token = sqstrtok(strtok_test_multitokspaced, strtok_whitespaces);
    mu_assert(token != NULL, "sqstrtok(strtok_test_multitokspaced, strtok_whitespaces) == NULL");
    mu_assert_string_eq("neodymium", token);
    token = sqstrtok(NULL, strtok_whitespaces);
    mu_assert(token != NULL, "sqstrtok(NULL, strtok_whitespaces) == NULL");
    mu_assert_string_eq("foo", token);
    token = sqstrtok(NULL, strtok_whitespaces);
    mu_assert(token != NULL, "sqstrtok(NULL, strtok_whitespaces) == NULL");
    mu_assert_string_eq("zapfff", token);
    token = sqstrtok(NULL, strtok_whitespaces);
    mu_assert(token != NULL, "sqstrtok(NULL, strtok_whitespaces) == NULL");
    mu_assert_string_eq("moo", token);
}

MU_TEST(test_sqstrstoks) 
{

}


MU_TEST_SUITE_GLOBAL(test_strtok) 
{
    MU_SUITE_CONFIGURE(&test_strtok_setup, &test_strtok_teardown);
    MU_RUN_TEST(test_sqstrstok);
    MU_RUN_TEST(test_sqstrstoks);
}
