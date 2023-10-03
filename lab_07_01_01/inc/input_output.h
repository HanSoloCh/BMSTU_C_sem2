#ifndef C_LAB_INPUT_OUTPUT_H
#define C_LAB_INPUT_OUTPUT_H

#include <stdio.h>

/**
 * @brief Функция подсчета количества элементов в файле
 * @param f [in, out] - файловый указатель
 * @param count [out] - количество элементов в файле
 * @return Код ошибки (0 - успех)
 */
int count_elem(FILE *f, int *count);

/**
 * @brief Функция заполнения массива элементами из файла
 * @param f [in, out] - файловый указатель
 * @param pbeg [in, out] - указатель на начало массива
 * @param pend [in, out] - указатель на конец массива
 * @return Код ошибки (0 - успех)
 */
int fill_array(FILE *f, int *pbeg, int *pend);

/**
 * @brief Считывание элементов из файла в массив
 * @param f [in, out] - файловый указатель
 * @param pbeg [out] - указатель на начало массива
 * @param pend [out] - указатель за конец массива
 * @return Код ошибки (0 - успех)
 */
int read_array_from_file(FILE *f, int **pbeg, int **pend);

/**
 * @brief Функция печати массива в файл
 * @param f [in, out] - файловый указатель
 * @param pbeg [in] - указатель на начало массива
 * @param pend [in] - указатель за конец массива
 */
void print_array_in_file(FILE *f, const int *pbeg, const int *pend);

#endif  // C_LAB_INPUT_OUTPUT_H
