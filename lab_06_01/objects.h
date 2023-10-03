#ifndef OBJECTS_H__
#define OBJECTS_H__

#include <stdio.h>

#include "errors_code.h"

#define NAME_LEN 25

typedef struct
{
    char name[NAME_LEN + 1];
    double weight;
    double volume;
} object_t;

/**
 * @brief Функция считывания одного объекта из файла
 * @param f [in] - файловая переменная
 * @param pb [out] - структура объекта
 * @return Код ошибки (0 - успех)
 */
int obj_read(FILE *f, object_t *pb);

/**
 * @brief Функция печати одного объекта в файл
 * @param f [in] - файловая переменная
 * @param po [in] - структура объекта
 * @return Код ошибки (0 - успех)
 */
int obj_print(FILE *f, const object_t *po);

/**
 * @brief Функция подсчета плотности
 * @param weight [in] - масса
 * @param volume [in] - объем
 * @return Плотность
 */
double calc_density(double weight, double volume);

/**
 * @brief Сравнение объектов по плотности
 * @param pl [in] - указатель на первый объект
 * @param pr [in] - указатель на второй объект
 * @return 1 - правый больше, 0 - одинаково, -1 - левый больше
 */
int obj_cmp_by_density(const object_t *pl, const object_t *pr);

#endif
