#include "objects.h"

#include <math.h>
#include <string.h>

#define EPS 1E-6

int obj_read(FILE *f, object_t *pb)
{
    char tmp_name[NAME_LEN + 10];
    if (!fgets(tmp_name, sizeof(tmp_name), f))
        return ERR_IO;
    int len = strlen(tmp_name);
    if (len && tmp_name[len - 1] == '\n')
    {
        len--;
        tmp_name[len] = '\0';
    }
    else
        return ERR_IO;
    if (len > NAME_LEN)
        return ERR_OVERFLOW;
    else if (len <= 0)
        return ERR_IO;
    else
        strcpy(pb->name, tmp_name);

    if (fscanf(f, "%lf", &(pb->weight)) != 1)
        return ERR_IO;
    else if (pb->weight <= 0)
        return ERR_RANGE;
    if (fscanf(f, "%lf", &(pb->volume)) != 1)
        return ERR_IO;
    else if (pb->volume <= 0)
        return ERR_RANGE;

    if (!feof(f))
    {
        char tmp[2];
        if (!fgets(tmp, sizeof(tmp), f))
            return ERR_IO;
    }
    return OK;
}

int obj_print(FILE *f, const object_t *po)
{
    fprintf(f, "%s\n%lf\n%lf\n", po->name, po->weight, po->volume);
    return OK;
}

double calc_density(double weight, double volume)
{
    return (weight / volume);
}

int obj_cmp_by_density(const object_t *pl, const object_t *pr)
{
    double pr_density = calc_density(pr->weight, pr->volume);
    double pl_density = calc_density(pl->weight, pl->volume);
    if (pr_density > pl_density)
        return -1;
    else if (fabs(pr_density - pl_density) < EPS)
        return 0;
    else
        return 1;
}
