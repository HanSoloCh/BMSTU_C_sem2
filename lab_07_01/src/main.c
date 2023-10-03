#include <stdio.h>
#include <stdlib.h>

#include "error_codes.h"
#include "func.h"
#include "input_output.h"

int main(int argc, char **argv)
{
    int rc, *pbeg = NULL, *pend, *pb_new_arr = NULL, *pe_new_arr;
    FILE *f;

    if (argc < 3 || argc > 4 || (argc == 4 && *argv[3] != 'f'))
        return ERR_ARGS;

    f = fopen(argv[1], "r");
    if (f == NULL)
        return ERR_FILE;

    rc = read_array_from_file(f, &pbeg, &pend);
    fclose(f);

    f = fopen(argv[2], "w");
    if (f == NULL)
        rc = ERR_FILE;

    if (rc == OK)
    {
        int *pb_for_print = pbeg, *pe_for_print = pend;
        if (argc == 4)
        {
            rc = key(pbeg, pend, &pb_new_arr, &pe_new_arr);
            pb_for_print = pb_new_arr, pe_for_print = pe_new_arr;
        }
        if (rc == OK)
        {
            mysort(pb_for_print, pe_for_print - pb_for_print, sizeof(int), comparator_for_int_num);
            print_array_in_file(f, pb_for_print, pe_for_print);
        }
        fclose(f);
    }
    free(pbeg);
    free(pb_new_arr);
    return rc;
}
