/*
The MIT License (MIT)

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "minunit.h"
#include "test_assert.h"
#include <sqassert.h>
#include <mock_assert.h>

void test_assert_setup(void) 
{
    reset_assertion_count();
}

void test_assert_teardown(void) 
{
   
}

MU_TEST(test_assert_mock) 
{
    mu_check(get_assertion_failures() == 0);
}

MU_TEST(test_assert_call) 
{
    sqassert(1 == 0);
#ifdef NDEBUG
    mu_check(get_assertion_failures() == 0);
#elif DEBUG
    mu_check(get_assertion_failures() == 1);
#endif
}

MU_TEST_SUITE(test_assert) 
{
    MU_SUITE_CONFIGURE(&test_assert_setup, &test_assert_teardown);
    MU_RUN_TEST(test_assert_mock);
    MU_RUN_TEST(test_assert_call);
}

int testAssertSuite()
{
    MU_RUN_SUITE(test_assert);
    MU_REPORT();
    return minunit_fail;
}