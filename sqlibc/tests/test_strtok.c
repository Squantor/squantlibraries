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

MU_TEST(test_sqstrstok_r_emptys)
{
    char *strtok_state;
    char *token;
    mu_assert(sqstrtok_r(strtok_test_empty, strtok_whitespaces, &strtok_state) == NULL, "sqstrtok(strtok_test_empty, strtok_whitespaces) != NULL");
    mu_assert(sqstrtok_r(strtok_test_no_tok, strtok_whitespaces, &strtok_state) == NULL, "sqstrtok(strtok_test_empty, strtok_whitespaces) != NULL");
}

MU_TEST(test_sqstrstok_r_singletok)
{
    char *strtok_state;
    char *token;
    
    token = sqstrtok_r(strtok_test_tokonly, strtok_whitespaces, &strtok_state);
    mu_assert(token != NULL, "sqstrtok(strtok_test_tokonly, strtok_whitespaces) == NULL");
    mu_assert_string_eq("foo", token);
    
    token = sqstrtok_r(strtok_test_tokspaced, strtok_whitespaces, &strtok_state);
    mu_assert(token != NULL, "sqstrtok(strtok_test_tokspaced, strtok_whitespaces) == NULL");
    mu_assert_string_eq("baz", token); 
}

MU_TEST(test_sqstrstok_r_multitoken) 
{
    char *strtok_state;
    char *token;  
    token = sqstrtok_r(strtok_test_multitokspaced, strtok_whitespaces, &strtok_state);
    mu_assert(token != NULL, "sqstrtok(strtok_test_multitokspaced, strtok_whitespaces) == NULL");
    mu_assert_string_eq("neodymium", token);
    token = sqstrtok_r(NULL, strtok_whitespaces, &strtok_state);
    mu_assert(token != NULL, "sqstrtok(NULL, strtok_whitespaces) == NULL");
    mu_assert_string_eq("foo", token);
    token = sqstrtok_r(NULL, strtok_whitespaces, &strtok_state);
    mu_assert(token != NULL, "sqstrtok(NULL, strtok_whitespaces) == NULL");
    mu_assert_string_eq("zapfff", token);
    token = sqstrtok_r(NULL, strtok_whitespaces, &strtok_state);
    mu_assert(token != NULL, "sqstrtok(NULL, strtok_whitespaces) == NULL");
    mu_assert_string_eq("moo", token);
}


MU_TEST_SUITE_GLOBAL(test_strtok) 
{
    MU_SUITE_CONFIGURE(&test_strtok_setup, &test_strtok_teardown);
    MU_RUN_TEST(test_sqstrstok_r_emptys);
    MU_RUN_TEST(test_sqstrstok_r_singletok);
    MU_RUN_TEST(test_sqstrstok_r_multitoken);
}

void testStrtokSuite()
{
    MU_RUN_SUITE(test_strtok);
    MU_REPORT();
}