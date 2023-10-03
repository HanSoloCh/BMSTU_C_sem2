#include "check_func.h"

#include <check.h>
#include <stdlib.h>

#include "error_codes.h"
#include "func.h"

#define EPS 1e-20

int comparator_for_double(const void *l, const void *r)
{
    const double *dl = l, *dr = r;
    if (fabs(*dl - *dr) < EPS)
        return 0;
    else if (*dl < *dr)
        return -1;
    return 1;
}

int comparator_for_char(const void *l, const void *r) { return *(char *)l - *(char *)r; }

// Правое больше левого
START_TEST(first_comparator_test)
{
    int a = 2, b = 3;

    // Результат меньше нуля
    ck_assert_int_lt(comparator_for_int_num(&a, &b), 0);
}
END_TEST

// Левое больше правого
START_TEST(second_comparator_test)
{
    int a = 3, b = 2;

    // Результат больше нуля
    ck_assert_int_gt(comparator_for_int_num(&a, &b), 0);
}
END_TEST

// Правое равно левому
START_TEST(third_comparator_test)
{
    int a = 3, b = 3;

    // Результат равен нулю
    ck_assert_int_eq(comparator_for_int_num(&a, &b), 0);
}
END_TEST

Suite *comparator_tests(void)
{
    Suite *s;
    TCase *first_test, *second_test, *third_test;

    s = suite_create("\nComparator tests");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_comparator_test);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_comparator_test);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_comparator_test);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    return s;
}

START_TEST(first_swap_test)
{
    int a = 2, b = 3;
    swap(&a, &b, sizeof(a));
    ck_assert_int_eq(a, 3);
    ck_assert_int_eq(b, 2);
}
END_TEST

Suite *swap_tests(void)
{
    Suite *s;
    TCase *first_test;

    s = suite_create("\nSwap tests");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_swap_test);

    suite_add_tcase(s, first_test);

    return s;
}

// Элементы по возрастанию
START_TEST(first_mysort_test_int)
{
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 3, 4};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Элементы по убыванию
START_TEST(second_mysort_test_int)
{
    int a[] = {4, 3, 2, 1};
    int b[] = {1, 2, 3, 4};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Элементы в случайном порядке
START_TEST(third_mysort_test_int)
{
    int a[] = {1, 3, 2, 4};
    int b[] = {1, 2, 3, 4};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Два по возрастанию
START_TEST(fourth_mysort_test_int)
{
    int a[] = {1, 2};
    int b[] = {1, 2};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Два по убыванию
START_TEST(fifth_mysort_test_int)
{
    int a[] = {2, 1};
    int b[] = {1, 2};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Один элемент
START_TEST(sixth_mysort_test_int)
{
    int a[] = {1};
    int b[] = {1};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Случайный массив с повторяющимися
START_TEST(seventh_mysort_test_int)
{
    int a[] = {1, 3, 4, 3};
    int b[] = {1, 3, 3, 4};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_int_num);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

Suite *mysort_test_int(void)
{
    Suite *s;
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_tests, *sixth_test, *seventh_test;
    s = suite_create("\nMysort tests for int");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_mysort_test_int);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_mysort_test_int);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_mysort_test_int);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_mysort_test_int);

    fifth_tests = tcase_create("Fifth test");
    tcase_add_test(fifth_tests, fifth_mysort_test_int);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_mysort_test_int);

    seventh_test = tcase_create("Seventh test");
    tcase_add_test(seventh_test, seventh_mysort_test_int);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_tests);
    suite_add_tcase(s, sixth_test);
    suite_add_tcase(s, seventh_test);

    return s;
}

// Элементы, упорядоченные по возрастанию
START_TEST(first_mysort_test_double)
{
    double a[] = {1.0, 2.0, 3.0, 4.0};
    double b[] = {1.0, 2.0, 3.0, 4.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Элементы, упорядоченные по убыванию
START_TEST(second_mysort_test_double)
{
    double a[] = {4.0, 3.0, 2.0, 1.0};
    double b[] = {1.0, 2.0, 3.0, 4.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Случайный порядок
START_TEST(third_mysort_test_double)
{
    double a[] = {1.0, 2.0, 4.0, 3.0};
    double b[] = {1.0, 2.0, 3.0, 4.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Два элемента по возрастанию
START_TEST(fourth_mysort_test_double)
{
    double a[] = {1.0, 2.0};
    double b[] = {1.0, 2.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Два элемента по убыванию
START_TEST(fifth_mysort_test_double)
{
    double a[] = {2.0, 1.0};
    double b[] = {1.0, 2.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Один элемент
START_TEST(sixth_mysort_test_double)
{
    double a[] = {1.0};
    double b[] = {1.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Случайный порядок, но есть одинаковые элементы
START_TEST(seventh_mysort_test_double)
{
    double a[] = {1.0, 3.0, 4.0, 3.0};
    double b[] = {1.0, 3.0, 3.0, 4.0};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

START_TEST(eight_mysort_test_double)
{
    double a[] = {6.000000004, 6.000000002};
    double b[] = {6.000000002, 6.000000004};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_double);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

Suite *mysort_test_double(void)
{
    Suite *s;
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_tests, *sixth_test, *seventh_test,
        *eight_test;
    s = suite_create("\nMysort tests for double");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_mysort_test_double);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_mysort_test_double);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_mysort_test_double);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_mysort_test_double);

    fifth_tests = tcase_create("Fifth test");
    tcase_add_test(fifth_tests, fifth_mysort_test_double);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_mysort_test_double);

    seventh_test = tcase_create("Seventh test");
    tcase_add_test(seventh_test, seventh_mysort_test_double);

    eight_test = tcase_create("Eight test");
    tcase_add_test(eight_test, eight_mysort_test_double);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_tests);
    suite_add_tcase(s, sixth_test);
    suite_add_tcase(s, seventh_test);
    suite_add_tcase(s, eight_test);

    return s;
}

// Элементы, упорядоченные по возрастанию
START_TEST(first_mysort_test_char)
{
    char a[] = {'a', 'b', 'c', 'd'};
    char b[] = {'a', 'b', 'c', 'd'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Элементы, упорядоченные по убыванию
START_TEST(second_mysort_test_char)
{
    char a[] = {'d', 'c', 'b', 'a'};
    char b[] = {'a', 'b', 'c', 'd'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Случайный порядок
START_TEST(third_mysort_test_char)
{
    char a[] = {'a', 'b', 'd', 'c'};
    char b[] = {'a', 'b', 'c', 'd'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Два элемента по возрастанию
START_TEST(fourth_mysort_test_char)
{
    char a[] = {'a', 'b'};
    char b[] = {'a', 'b'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Два элемента по убыванию
START_TEST(fifth_mysort_test_char)
{
    char a[] = {'b', 'a'};
    char b[] = {'a', 'b'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Один элемент
START_TEST(sixth_mysort_test_char)
{
    char a[] = {'a'};
    char b[] = {'a'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

// Случайный порядок, но есть одинаковые элементы
START_TEST(seventh_mysort_test_char)
{
    char a[] = {'a', 'c', 'd', 'c'};
    char b[] = {'a', 'c', 'c', 'd'};
    mysort(a, sizeof(a) / sizeof(a[0]), sizeof(*a), comparator_for_char);
    ck_assert_mem_eq(a, b, sizeof(a));
}
END_TEST

Suite *mysort_test_char(void)
{
    Suite *s;
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_tests, *sixth_test, *seventh_test;
    s = suite_create("\nMysort tests for char");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_mysort_test_char);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_mysort_test_char);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_mysort_test_char);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_mysort_test_char);

    fifth_tests = tcase_create("Fifth test");
    tcase_add_test(fifth_tests, fifth_mysort_test_char);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_mysort_test_char);

    seventh_test = tcase_create("Seventh test");
    tcase_add_test(seventh_test, seventh_mysort_test_char);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_tests);
    suite_add_tcase(s, sixth_test);
    suite_add_tcase(s, seventh_test);

    return s;
}

// Минимальный элемент идет раньше максимального
START_TEST(first_key_test)
{
    int a[] = {1, -100, 3, 4, 100, 5};
    int res[] = {3, 4};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Максимальный элемент идет раньше минимального
START_TEST(second_key_test)
{
    int a[] = {1, 100, 3, 4, -100, 5};
    int res[] = {3, 4};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Два минимальных элемента (минимальный раньше максимального)
START_TEST(third_key_test)
{
    int a[] = {1, -100, 3, -100, 4, 100, 5};
    int res[] = {3, -100, 4};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Два минимальных элемента (максимальный раньше минимального)
START_TEST(fourth_key_test)
{
    int a[] = {1, 100, 3, -100, 5, -100, 6};
    int res[] = {3};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Два максимальных элемента (минимальный раньше максимального)
START_TEST(fifth_key_test)
{
    int a[] = {1, -100, 3, 100, 4, 100, 5};
    int res[] = {3};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Два максимальных элемента (максимальный раньше минимального)
START_TEST(sixth_key_test)
{
    int a[] = {1, 100, 3, 100, 4, -100, 5};
    int res[] = {3, 100, 4};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Два минимальных и два максимальных элемента (минимальный раньше максимального)
START_TEST(seventh_key_test)
{
    int a[] = {1, -100, 3, -100, 4, 100, 5, 100, 6};
    int res[] = {3, -100, 4};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Два максимальных и два минимальных (максимальный раньше минимального)
START_TEST(eighth_key_test)
{
    int a[] = {1, 100, 3, 100, 4, -100, 5, -100, 6};
    int res[] = {3, 100, 4};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_mem_eq(pbeg, res, sizeof(res) / sizeof(*res));
    ck_assert_int_eq(code_return, OK);
    free(pbeg);
}
END_TEST

// Пустой результат
START_TEST(ninth_key_test)
{
    int a[] = {1, -100, 100, 2};
    int *pbeg = NULL, *pend;
    int code_return;
    code_return = key(a, a + sizeof(a) / sizeof(a[0]), &pbeg, &pend);
    ck_assert_int_eq(code_return, ERR_EMPTY_ARR);
    free(pbeg);
}
END_TEST

// Неправильные аргументы
START_TEST(tenth_key_test)
{
    int *pbeg, *pend;
    int code_return;
    code_return = key(NULL, NULL, &pbeg, &pend);
    ck_assert_int_eq(code_return, ERR_RANGE);
}
END_TEST

Suite *key_tests(void)
{
    Suite *s;
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_test, *sixth_test, *seventh_test,
        *eighth_test, *ninth_test, *tenth_test;
    s = suite_create("\nKey tests");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_key_test);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_key_test);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_key_test);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_key_test);

    fifth_test = tcase_create("Fifth test");
    tcase_add_test(fifth_test, fifth_key_test);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_key_test);

    seventh_test = tcase_create("Seventh test");
    tcase_add_test(seventh_test, seventh_key_test);

    eighth_test = tcase_create("Eighth test");
    tcase_add_test(eighth_test, eighth_key_test);

    ninth_test = tcase_create("Ninth test");
    tcase_add_test(ninth_test, ninth_key_test);

    tenth_test = tcase_create("Tenth test");
    tcase_add_test(tenth_test, tenth_key_test);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_test);
    suite_add_tcase(s, sixth_test);
    suite_add_tcase(s, seventh_test);
    suite_add_tcase(s, eighth_test);
    suite_add_tcase(s, ninth_test);
    suite_add_tcase(s, tenth_test);

    return s;
}

// Один максимальны, один минимальный
START_TEST(first_find_max_min_test)
{
    int a[] = {-100, 1, 2, 3, 100};
    int *max_res = &a[4], *min_res = &a[0];
    int *max, *min;
    find_max_min(a, a + sizeof(a) / sizeof(*a), &max, &min);
    ck_assert_ptr_eq(max_res, max);
    ck_assert_ptr_eq(min_res, min);
}
END_TEST

// Два минимальных, один максимальный
START_TEST(second_find_max_min_test)
{
    int a[] = {-100, -100, 2, 3, 100};
    int *min_res = &a[0], *max_res = &a[4];
    int *max, *min;
    find_max_min(a, a + sizeof(a) / sizeof(*a), &max, &min);
    ck_assert_ptr_eq(max_res, max);
    ck_assert_ptr_eq(min_res, min);
}
END_TEST

// Один минимальный, два максимальных
START_TEST(third_find_max_min_test)
{
    int a[] = {-100, 1, 2, 100, 100};
    int *min_res = &a[0], *max_res = &a[3];
    int *max, *min;
    find_max_min(a, a + sizeof(a) / sizeof(*a), &max, &min);
    ck_assert_ptr_eq(max_res, max);
    ck_assert_ptr_eq(min_res, min);
}
END_TEST

// Два минимальных, два максимальных
START_TEST(fourth_find_max_min_test)
{
    int a[] = {-100, -100, 2, 100, 100};
    int *min_res = &a[0], *max_res = &a[3];
    int *max, *min;
    find_max_min(a, a + sizeof(a) / sizeof(*a), &max, &min);
    ck_assert_ptr_eq(max_res, max);
    ck_assert_ptr_eq(min_res, min);
}
END_TEST

// Максимальный и минимальный совпадают. В массиве больше, чем один элемент
START_TEST(fifth_find_max_min_test)
{
    int a[] = {1, 1, 1};
    int *min_res = &a[0], *max_res = &a[0];
    int *max, *min;
    find_max_min(a, a + sizeof(a) / sizeof(*a), &max, &min);
    ck_assert_ptr_eq(max_res, max);
    ck_assert_ptr_eq(min_res, min);
}
END_TEST

// Максимальный и минимальный совпадают. В массиве один элемент
START_TEST(sixth_find_max_min_test)
{
    int a[] = {1};
    int *min_res = &a[0], *max_res = &a[0];
    int *max, *min;
    find_max_min(a, a + sizeof(a) / sizeof(*a), &max, &min);
    ck_assert_ptr_eq(max_res, max);
    ck_assert_ptr_eq(min_res, min);
}
END_TEST

Suite *find_max_min_test(void)
{
    Suite *s;
    TCase *first_test, *second_test, *third_test, *fourth_test, *fifth_test, *sixth_test;
    s = suite_create("\nFind_max_min tests");

    first_test = tcase_create("First test");
    tcase_add_test(first_test, first_find_max_min_test);

    second_test = tcase_create("Second test");
    tcase_add_test(second_test, second_find_max_min_test);

    third_test = tcase_create("Third test");
    tcase_add_test(third_test, third_find_max_min_test);

    fourth_test = tcase_create("Fourth test");
    tcase_add_test(fourth_test, fourth_find_max_min_test);

    fifth_test = tcase_create("Fifth test");
    tcase_add_test(fifth_test, fifth_find_max_min_test);

    sixth_test = tcase_create("Sixth test");
    tcase_add_test(sixth_test, sixth_find_max_min_test);

    suite_add_tcase(s, first_test);
    suite_add_tcase(s, second_test);
    suite_add_tcase(s, third_test);
    suite_add_tcase(s, fourth_test);
    suite_add_tcase(s, fifth_test);
    suite_add_tcase(s, sixth_test);

    return s;
}