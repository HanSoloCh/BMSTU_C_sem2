#include "input_output.h"

#include <stdio.h>
#include <stdlib.h>

#include "error_codes.h"

int count_elem(FILE *f, int *count)
{
    int rc = OK;
    *count = 0;
    while (rc == OK)
    {
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1)
            rc = ERR_IO;
        else
            (*count)++;
    }
    if (feof(f))
        rc = OK;
    return rc;
}

int fill_array(FILE *f, int *pbeg, int *pend)
{
    int rc = OK;
    fseek(f, SEEK_SET, 0);
    for (int *pcur = pbeg; pcur < pend; pcur++)
    {
        if (fscanf(f, "%d", pcur) != 1)
            rc = ERR_IO;
    }
    return rc;
}

int read_array_from_file(FILE *f, int **pbeg, int **pend)
{
    int count, rc;
    rc = count_elem(f, &count);
    if (rc != OK)
        return rc;
    else if (count == 0)
        return ERR_EMPTY_ARR;

    *pbeg = malloc(count * sizeof(int));
    if (*pbeg == NULL)
        return ERR_DYNAMIC_MEM;
    *pend = *pbeg + count;
    rc = fill_array(f, *pbeg, *pend);
    return rc;
}

void print_array_in_file(FILE *f, const int *pbeg, const int *pend)
{
    const int *pcur = pbeg;
    while (pcur < pend)
    {
        fprintf(f, "%d ", *pcur);
        pcur++;
    }
    fprintf(f, "\n");
}
