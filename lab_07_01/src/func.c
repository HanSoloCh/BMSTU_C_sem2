#include "func.h"

#include <stdlib.h>
#include <string.h>

#include "error_codes.h"

int comparator_for_int_num(const void *l, const void *r)
{
    return *(int *)l - *(int *)r;
}

void mysort(void *pdata, size_t n_members, size_t elem_size, uni_cmp_t comparator)
{
    if (n_members == 0)
        return;
    char *pbeg = pdata, *pend = pbeg + n_members * elem_size;
    for (char *pcur_1 = pend - elem_size; pcur_1 > pbeg; pcur_1 -= elem_size)
    {
        char *max_elem = pcur_1;
        for (char *pcur_2 = pbeg; pcur_2 < pcur_1; pcur_2 += elem_size)
        {
            if (comparator(max_elem, pcur_2) < 0)
                max_elem = pcur_2;
        }
        swap(max_elem, pcur_1, elem_size);
    }
}

void swap(void *l, void *r, size_t elem_size)
{
    char *pl = l, *pr = r;
    for (size_t i = 0; i < elem_size; i++)
    {
        char tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pl++;
        pr++;
    }
}

void find_max_min(const int *pbeg, const int *pend, int **max, int **min)
{
    *max = (int *)pbeg, *min = (int *)pbeg;
    for (const int *pcur = pbeg + 1; pcur < pend; pcur++)
    {
        if (*pcur < **min)
            *min = (int *)pcur;

        if (*pcur > **max)
            *max = (int *)pcur;
    }
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int *max, *min;
    const int *start;
    if (pb_src == NULL || pe_src == NULL)
        return ERR_RANGE;
    find_max_min(pb_src, pe_src, &max, &min);
    int new_array_size = abs((int)(max - min)) - 1;
    if (new_array_size <= 0)
        return ERR_EMPTY_ARR;
    start = max - min < 0 ? max + 1 : min + 1;
    *pb_dst = malloc(new_array_size * sizeof(int));
    if (*pb_dst == NULL)
        return ERR_DYNAMIC_MEM;

    *pe_dst = *pb_dst + new_array_size;
    memmove(*pb_dst, start, new_array_size * sizeof(int));

    return OK;
}
