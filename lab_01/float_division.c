#include "float_division.h"

/// @brief определяет минимальное число из пары двух целых чисел
/// @param a первое число
/// @param b второе число
/// @return значение минимального числа
static int min(int a, int b) {
    return (a < b) ? a : b;
}

/// @brief сравнивает два числа в выбранном представлении
/// @param first первое число
/// @param second второе число
/// @param first_len длина первого числа
/// @param second_len длина второго числа
/// @return код возврата 1 если первое число больше,0-если они равны,-1 если меньше
static int cmp_float(short first[], short second[],size_t first_len, size_t second_len)
{   
    // проверка длин чисел
    if (first_len > second_len)
        return 1;
    if (first_len < second_len)
        return -1;
    // проход по каждой из соттветствующих цифр чисел и их сравнение
    for (size_t i = 0; i < first_len; i++)
    {
        if (first[i] > second[i])
            return 1;
        else if (first[i] < second[i])
            return -1;
    }
    return 0;
}

/// @brief вычитает два числа в выбранном представлении
/// @param first первое число
/// @param second второе число
/// @param result результирующее число
/// @param first_len длина первого числа
/// @param second_len длина второго числа
/// @return длина результирующего числа
static int subtraction(short first[], short second[],short result[],size_t first_len,size_t second_len)
{
    int remainder = 0; // остаток,переносящийся в следующий разряд
    // если длина числа на 1 больше второго,добавляем ко второму ведущий ноль
    if (first_len > second_len)
    {
        for (size_t i = first_len; i > 0; i--)
        {
            short temp = second[i];
            second[i] = second[i - 1];
            second[i - 1] = temp;
        }
        second[0] = 0;
    }
    // отладочный вывод вычитаемых чисел
    // for (size_t i = 0; i < first_len; i++)
    // {
    //     printf("%hd",first[i]);
    // }
    // printf("! - first\n");
    // for (size_t i = 0; i < first_len; i++)
    // {
    //     printf("%hd",second[i]);
    // }
    // printf("! - second\n");
    for (size_t i = first_len; i > 0; i--)
    {
        // если разница цифры первого и остатка больше или равна цифре второго - просто вычитаем
        if ((first[i - 1] - remainder) >= second[i - 1])
        {
            result[i - 1] = first[i - 1] - remainder - second[i - 1];
            remainder = 0;
        }
        // если цифра первого меньше - добавляем 10,которую мы "взяли" из следующего разряда
        else
        {
            result[i - 1] = ((first[i - 1] - remainder) + 10 - second[i - 1]);
            remainder = 1;
        }
    }
    int res_len = first_len; // длина результата
    // удаление ведущих нулей
    int zero_cnt = 0; //количество ведущих нулей
    for (int i = 0; (i < res_len) && (result[i] == 0); i++)
        zero_cnt++;
    if (zero_cnt != 0)
    {
        // если в результате только нули - просто сокращаем длину до единицы
        if (zero_cnt == res_len)
            return 1;
        // убираем ведущие нули
        for (int i = 0; i < res_len - zero_cnt; i++)
            result[i] = result[i + zero_cnt];
        res_len -= zero_cnt;
    }
    // убираем ведущий ноль из вычитаемого
    if (second[0] == 0)
        for (size_t i = 0; i < second_len; i++)
            second[i] = second[i + 1];
    return res_len;
}

/// @brief целочисленное деление двух чисел в выбранном представлении
/// @param first первое число, гарантировано больше второго,но не более чем в 10 раз
/// @param second второе число
/// @param result результирующее число
/// @param first_len длина первого числа
/// @param second_len длина второго числа
/// @param res_len длина результирующего числа
/// @return частное от деления
static int divide(short first[], short second[],short res[],size_t first_len,size_t second_len,size_t *res_len)
{
    int mult = 0; // частное от деления
    short temp[MAX_MANTIS_LEN + 2]; // массив остатка от деления
    // вычитаем первый раз
    size_t cur_len = subtraction(first,second,res,first_len,second_len);
    mult++;
    while (cmp_float(res,second,cur_len, second_len) >= 0)
    {
        // если количество операций превысило 10 - выходим из цикла
        if (mult > 10)
            break;
        //отладочный вывод печати текущей операции вычитания
        // printf("cur subtraction: %zu %zu %d %d\n",cur_len,second_len,cmp_float(res,second,cur_len, second_len), mult);
        cur_len = subtraction(res,second,temp,cur_len,second_len);
        // перенос остатка в уменьшаемое
        for (size_t i = 0; i < cur_len; i++)
            res[i] = temp[i];
        mult++;
    }
    *res_len = cur_len;
    //отладочный вывод результата операции
    // printf("total subtraction:%d ",mult);
    return mult;
}

/// @brief  деление двух чисел в выбранном представлении
/// @param first делимое
/// @param second делитель
/// @param total результирующее число
/// @return код возврата 0,если все прошло успешно или код ошибки
int my_float_division(my_float_t first, my_float_t second,my_float_t *total)
{
    if (second.sign == 0)
        return ERROR_ZERO_DIVISION;
    // если делимое ноль-возвращаем нулевой результат
    if (first.sign == 0)
    {
        total->sign = 0;
        total->mantiss[0] = 0;
        total->mantiss_len = 0;
        total->order = 0;
        return 0;
    }
     // если делитель ноль-возвращаем нулевой результат
    short divisible[MAX_MANTIS_LEN + 2]; // масссив цифр числителя
    short divider[MAX_MANTIS_LEN + 2]; // масссив цифр знаменателя
    for (size_t i = 0; i < second.mantiss_len; i++)
        divider[i] = second.mantiss[i];
    my_float_t result; // результат
    size_t divider_len = second.mantiss_len; // длина знаменателя
    size_t fractional = 0; // дробная часть результата
    size_t cur_index = 0; // текущий индекс 
    size_t cur_len = 0; // текущая длина накопленного числа
    size_t mant_res = 0; // длина мантиссы результата
    short tmp[MAX_MANTIS_LEN + 2]; // массив для хранения остатка
    for (int i = 0; i < min(second.mantiss_len,first.mantiss_len); i++)
    {
        divisible[cur_len] = first.mantiss[i];
        cur_len++;
        cur_index++;
    }
    // printf("begin:");
    // for (size_t i = 0; i < cur_len; i++)
    //         printf("%hd",divisible[i]);
    // printf("\n");
    if (cmp_float(divisible,divider,cur_len,second.mantiss_len) < 0)
    {
        if (cur_index >= first.mantiss_len)
            {
                divisible[cur_len] = 0;
                fractional++;
            }
        else
            divisible[cur_len] = first.mantiss[cur_index];
        cur_len++;
        cur_index++;
    }
    printf("post_process:");
    for (size_t i = 0; i < cur_len; i++)
            printf("%hd",divisible[i]);
    printf("\n");
    while ((mant_res < MAX_MANTIS_LEN + 1) && ((cur_index < first.mantiss_len) || (cur_len > 0)))
    {
        printf("Current iteration: %zu ",cur_index);
        for (size_t i = 0; i < cur_len; i++)
            printf("%hd",divisible[i]);
        printf(" %zu %zu %zu\n",cur_len,cur_index,fractional);
        int found = cmp_float(divisible,divider,cur_len,divider_len);
        if (found == -1)
        {
            if (cur_index >= first.mantiss_len)
            {
                divisible[cur_len] = 0;
                fractional++;
            }
            else
                divisible[cur_len] = first.mantiss[cur_index];
            cur_index++;
            result.mantiss[mant_res] = 0;
            mant_res++;
            cur_len++;
            continue;
        }
        else if (found == 0)
        {
                memset(divisible,0,sizeof(short) * MAX_MANTIS_LEN);
                cur_len = 0;
                result.mantiss[mant_res] = 1;
                mant_res++;
                if (cur_index >= first.mantiss_len)
                {
                    divisible[cur_len] = 0;
                    continue;
                }
                else
                    divisible[cur_len] = first.mantiss[cur_index];
                cur_len++;
                cur_index++;
        }
        else
        {
            size_t new_len = cur_len;
            result.mantiss[mant_res] = divide(divisible,divider,tmp,cur_len,divider_len,&new_len);
            mant_res++;
            printf("relt: ");
            for (size_t i = 0; i < mant_res; i++)
            {
                printf("%hd ",result.mantiss[i]);
            }
            printf("\n");
            printf("tmp: ");
            if ((tmp[0] == 0) && (cur_index >= first.mantiss_len))
            {
                divisible[0] = 0;
                cur_len = 0;
                continue;
            }
            if (tmp[0] != 0)
                for (size_t i = 0; i < new_len; i++)
                {
                    printf("%hd ",tmp[i]);
                    divisible[i] = tmp[i];
                }
            else
                new_len = 0;
            printf("\n");
            cur_len = new_len;
            for (size_t i = 0; i < cur_len; i++)
            {
                printf("%hd",divisible[i]);
            }
            printf(" ");
            if (cur_index >= first.mantiss_len)
            {
                divisible[cur_len] = 0;
                fractional++;
            }
            else
                divisible[cur_len] = first.mantiss[cur_index];
            cur_len++;
            cur_index++;
            for (size_t i = 0; i < cur_len; i++)
            {
               printf("%hd",divisible[i]);
            }
            printf("\n");
        }
            
    }
    printf("\n");
        for (size_t i = 0; i < mant_res; i++)
            total->mantiss[i] = result.mantiss[i];
    printf("fractional: %zu \n",fractional);
    printf("mant_res: %zu \n",mant_res);
    total->mantiss_len = mant_res;
    total->sign = first.sign * second.sign;
    if (fractional == 0)
        total->order =  first.order - second.order + mant_res;
    else
        total->order =  first.order - second.order - fractional + mant_res + 1;
    return 0;
}

/// @brief  производит округление числа,если его длина превышает допустимое
/// @param cur требуемое для округления числщ
void round_up(my_float_t *cur)
{
    print_float(*cur);
    size_t cur_len = cur->mantiss_len;
    if (cur_len < MAX_MANTIS_LEN)
        return ;
    int last_num = cur->mantiss[cur_len - 1];
    cur->mantiss[cur_len - 1] = 0;
    if (last_num >= 5)
        cur->mantiss[cur_len - 2]++;
    cur_len--;
    while ((cur_len > 0) && (cur->mantiss[cur_len - 1] % 10 == 0))
    {
       int last_num = cur->mantiss[cur_len - 1];
        cur->mantiss[cur_len - 1] = 0;
        if (last_num >= 5)
            cur->mantiss[cur_len - 2]++;
        cur_len--;
        // 999999999999999999999999999999999999999
        // 111111111111111111111111111111111111111
    }
    size_t zero_cnt = 0; 
    for (size_t i = 0; (i < cur_len) && (cur->mantiss[i] == 0); i++)
        zero_cnt++;
    if (zero_cnt != 0)
    {
        for (size_t i = 0; i < cur_len - zero_cnt; i++)
            cur->mantiss[i] = cur->mantiss[i + zero_cnt];
        cur_len -= zero_cnt;
        cur->order -= zero_cnt;
    }
    cur->mantiss_len = cur_len;
}
