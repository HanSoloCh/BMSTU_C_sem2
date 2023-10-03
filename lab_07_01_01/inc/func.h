#ifndef LAB_07_1_01_FUNC_H
#define LAB_07_1_01_FUNC_H

#include <stddef.h>

typedef int (*uni_cmp_t)(const void *, const void *);

/**
 * @brief Компаратор для целых чисел
 * @return значение <0 - правое число больше, 0 - равны, >0 - левое число больше
 */
int comparator_for_int_num(const void *, const void *);

/**
 * @brief Функция сортировки массива выбором
 * @param pdata [in, out] - указатель на массив
 * @param n_members [in] - количество элементов
 * @param elem_size [in] - размер одного элемента
 * @param comparator [in] - компаратор
 */
void mysort(void *pdata, size_t n_members, size_t elem_size, uni_cmp_t comparator);

/**
 * @brief Функция обмена двух элементов
 * @param l [in, out] - указатель на элемент 1
 * @param r [in, out] - указатель на элемент 2
 * @param elem_size [in] - размер одного элемента
 */
void swap(void *l, void *r, size_t elem_size);

/**
 * @brief Функция фильтрации массива
 * @param pb_src [in] - указатель на первый элемент входного массива
 * @param pe_src [in] - указатель за последний элемент входного массива
 * @param pb_dst [out] - указатель на первый элемент результирующего массива
 * @param pe_dst [out] - указатель за последний элемент результирующего массива
 * @return Код ошибки (0 - успех)
 */
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

void find_max_min(const int *pbeg, const int *pend, int **max, int **min);

#endif
