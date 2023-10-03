#ifndef SEM_3_BOOK_ARRAY_H
#define SEM_3_BOOK_ARRAY_H

#include <stddef.h>
#include <stdio.h>

#include "errors_code.h"
#include "objects.h"

#define N_MAX 15

typedef int (*cmp_t)(const object_t *pl, const object_t *pr);

/**
 * @brief Считывание массива структур объектов из файла
 * @param f [in] - файловая переменная
 * @param objects [in] - массив структур
 * @param n_max [in] - максимальный размер массива
 * @param pn [out] - количество, считанных элементов
 * @return Код ошибки (0 - успех)
 */
int obj_arr_read(FILE *f, object_t *objects, size_t n_max, size_t *pn);

/**
 * @brief Функция печати массива структур объектов, согласно префиксу
 * @param f [in] - файловая переменная
 * @param objects [in] - массив структур объектов
 * @param count [in] - количество элементов
 * @param prefix [in] - префикс
 * @return КОд ошибки (0 - успех)
 */
int obj_arr_print(FILE *f, const object_t *objects, size_t count, char *prefix);

/**
 * @brief Производит проверку ключа (префикса)
 * @param name [in] - поле имя
 * @param prefix [in] - вводимый ключ
 * @return 0 - ключ == ALL, 1 - prefix является началом name, иначе -1
 */
int check_key(char *name, char *prefix);

/**
 * @brief Сортировка массива по плотности
 * @param objects [in] - массив структур объектов
 * @param n [in] - количество элементов
 * @param comparator [in] - компаратор
 */
void obj_arr_sort(object_t *objects, size_t n, cmp_t comparator);

#endif
