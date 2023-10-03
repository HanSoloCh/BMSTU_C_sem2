#include "obj_array.h"

#include <string.h>

int obj_arr_read(FILE *f, object_t *objects, size_t n_max, size_t *pn)
{
    object_t object;
    size_t i = 0;
    int rc = OK;
    while (rc == OK)
    {
        rc = obj_read(f, &object);
        if (rc == OK)
        {
            if (i < n_max)
                objects[i++] = object;
            else
                rc = ERR_OVERFLOW;
        }
    }
    *pn = i;
    if (feof(f))
        rc = OK;
    return rc;
}

int obj_arr_print(FILE *f, const object_t *objects, size_t count, char *prefix)
{
    int rc = OK;

    for (size_t i = 0; i < count && rc == OK; i++)
    {
        int key = check_key((char *)objects[i].name, prefix);
        if (key == 0)
            rc = obj_print(f, &objects[i]);
        else if (key == 1)
            rc = obj_print(f, &objects[i]);
    }
    return rc;
}

int check_key(char *name, char *prefix)
{
    if (strcmp(prefix, "ALL") == 0)
        return 0;
    else
    {
        char *find_str = strstr(name, prefix);
        if (find_str != NULL && find_str == name)
            return 1;
        else
            return -1;
    }
}

void obj_arr_sort(object_t *objects, size_t n, cmp_t comparator)
{
    int flag = 0;
    while (!flag)
    {
        flag = 1;
        for (size_t i = 0; i < n - 1; i++)
        {
            if (comparator(&objects[i], &objects[i + 1]) == 1)
            {
                flag = 0;
                object_t tmp = objects[i];
                objects[i] = objects[i + 1];
                objects[i + 1] = tmp;
            }
        }
    }
}
