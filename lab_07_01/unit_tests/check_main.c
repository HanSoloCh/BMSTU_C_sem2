#include <check.h>

#include "check_func.h"

int main(void)
{
    SRunner *sr;

    sr = srunner_create(comparator_tests());
    srunner_add_suite(sr, swap_tests());
    srunner_add_suite(sr, mysort_test_int());
    srunner_add_suite(sr, mysort_test_double());
    srunner_add_suite(sr, mysort_test_char());
    srunner_add_suite(sr, key_tests());
    srunner_add_suite(sr, find_max_min_test());

    srunner_run_all(sr, CK_NORMAL);
    int failed_tests = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed_tests;
}
