//
// Created by artem on 29.09.23.
//

#ifndef LAB_07_01_01_CHECK_FUNC_H
#define LAB_07_01_01_CHECK_FUNC_H

#include <check.h>

#include "func.h"

Suite *comparator_tests(void);

Suite *swap_tests(void);

Suite *mysort_test_int(void);
Suite *mysort_test_double(void);
Suite *mysort_test_char(void);

Suite *key_tests(void);

Suite *find_max_min_test(void);

#endif  // LAB_07_01_01_CHECK_FUNC_H
