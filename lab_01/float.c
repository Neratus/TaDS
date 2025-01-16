#include "float.h"


int input_float(char *str,my_float_t *first)
{
    int sign = 1;
    int ord_sign = 1;
    char *cur = str;
    int order = 0;
    size_t mant_size = 0;
    size_t order_size = 0;
    size_t fractional = 0;
    short mantiss_nums[MAX_MANTIS_LEN];
    while (isspace(*cur))
        cur++;
    if (*cur == '-')
    {
        sign = -1;
        cur++;
    }
    if ((*cur == '+') && (sign == 1))
        cur++;
    while ((isspace(*cur)) || (*cur == '0'))
        cur++;
    while (isdigit(*cur))
    {
        mant_size++;
        if (mant_size > MAX_MANTIS_LEN)
            return ERROR_NUM_OVERFLOW;
        mantiss_nums[mant_size - 1] = *cur - '0';
        cur++;
    }
    if (cur == str)
        return ERROR_NOT_NUM;
    if (mant_size == 0)
        mantiss_nums[0] = 0;
    if (*cur == '.')
    {
        cur++;
        while (isdigit(*cur))
        {
            mant_size++;
            fractional++;
            if (mant_size > MAX_MANTIS_LEN)
                return 1;
            mantiss_nums[mant_size - 1] = *cur - '0';
            cur++;
        }
        size_t zero_cnt = 0;
        for (size_t i = 1; (i <= fractional) && (mantiss_nums[mant_size - i] == 0); i++)
            zero_cnt++;
        fractional -= zero_cnt;
        mant_size -= zero_cnt;
    }
    if (mant_size == 0)
    {
        first->sign = 0;
        return 0;
    }
    while (isspace(*cur))
        cur++;
    if (*cur == 'E')
    {
        cur++;
        while (isspace(*cur))
            cur++;
        if (*cur == '-')
        {
            ord_sign = -1;
            cur++;
        }
        if (*cur == '+')
            cur++;
        while (*cur == '0')
            cur++;
        while (isdigit(*cur))
        {
            order_size++;
            if (order_size - 1 >= MAX_ORD_LEN)
                return 1;
            order *= 10;
            order += (int)(*cur - '0');
            cur++;
        }
        if (order_size == 0)
            return 3;
        order *= ord_sign;
    }
    printf("fractional: %zu \n",fractional);
    order -= fractional;
    printf("mantiss: ");
    for (size_t i = 0; i < mant_size; i++)
        printf("%hd",mantiss_nums[i]);
    if (*cur != '\0')
        return 3;
    printf("\norder: %d \n",order);
    printf("mant_size : %zu \n",mant_size);
    first->sign = sign;
    first->order = order;
    size_t zero_cnt = 0;
    for (size_t i = mant_size - 1; (i > 0) && (mantiss_nums[mant_size - i] == 0); i--)
        zero_cnt++;
    mant_size -= zero_cnt;
    first->mantiss_len = mant_size;
    for (size_t i = 0; i < mant_size + 1; i++)
        first->mantiss[i] = mantiss_nums[i];
    return 0;
}

void print_float(my_float_t my_float)
{
    if (my_float.sign == -1)
        printf("-");
    else if (my_float.sign == 0)
    {
        printf("0.0E0 \n");
        return ;
    }
    printf("0.");
    for (size_t i = 0; i < my_float.mantiss_len; i++)
    {
        printf("%hd",my_float.mantiss[i]);
    } 
    printf("E%d \n",my_float.order);
}
