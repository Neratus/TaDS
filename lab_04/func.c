#include "func.h"

int read_line(char *str, size_t str_max, FILE *f)
{
    if (!fgets(str, str_max, f))
    {
        return ERROR_STR_INPUT;
    }
    char *p = strchr(str, '\n');
    if (p)
    {
        *p = 0;
        return OK;
    }
    return ERROR_STR_SIZE;
}
