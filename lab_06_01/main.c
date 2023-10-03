#include <stdio.h>
#include <string.h>

#include "errors_code.h"
#include "obj_array.h"
#include "objects.h"

int main(int argc, char **argv)
{
    FILE *f;
    object_t objects[N_MAX];
    size_t count;
    int rc;
    if (argc > 3 || argc < 2)
        return ERR_ARGS;
    f = fopen(argv[1], "r");
    if (f == NULL)
        return ERR_FILE;
    rc = obj_arr_read(f, objects, N_MAX, &count);
    if (rc != OK || count == 0)
    {
        if (!count)
            rc = ERR_EMPTY_IO;
        return rc;
    }
    else
    {
        if (argc == 2)
        {
            obj_arr_sort(objects, count, obj_cmp_by_density);
            obj_arr_print(stdout, objects, count, "ALL");
        }
        else
            obj_arr_print(stdout, objects, count, argv[2]);
    }
    fclose(f);
    return rc;
}
