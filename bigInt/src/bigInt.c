#include "bigInt.h"

#define DEBUG

// static int
// _abs(int nbr)
// {
//     if (nbr < 0)
//         return (-nbr);
//     return (nbr);
// }

void
BI_init( bigInt * num )
{
    memset(num->numbers, '0', MAX_SIZE);
    num->sign       = 1;
    num->size       = 0;
    num->overflow   = 0;
}

void
BI_print( bigInt num )
{
    if (num.overflow)
    {
        ewrite("Overflow\n");
        return;
    }
    write(1, (num.sign >= 0) ? "+" : "-", 1);

    int start = MAX_SIZE - num.size;
    write(1, num.numbers + start, num.size);
    write(1, "\n", 1);
}

int
BI_setValue( bigInt * num, char * str )
{
    int size = strlen(str);
    if (size > MAX_SIZE)
    {
        #ifdef DEBUG
            ewrite("MAX_SIZE exceeded\n");
        #endif
        return (1);
    }

    BI_init(num);

    int offset = MAX_SIZE - size;
    num->size = size;

    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (str[i] == '-')
            num->sign = -1, offset++;
        else if (str[i] == '+')
            num->sign = 1, offset++;
        else
        {
            num->numbers[j + offset] = str[i];
            j++;
        }
    }
    num->size = j;
    
    return (0);
}

int
BI_getSize( bigInt a )
{
    // could be obtaine by MAX_SIZE - first occurence of char in a.numbers[] but uncessary memory access when it's already stocked in memory
    return (a.size);
}

int
BI_compare ( bigInt a, bigInt b )
{
    if (a.size > b.size)
        return 1;
    if (a.size < b.size)
        return -1;
    
    for (int i = 0; i < a.size; i++)
    {
        if (a.numbers[MAX_SIZE - a.size + i] > b.numbers[MAX_SIZE - b.size + i])
            return 1;
        if (a.numbers[MAX_SIZE - a.size + i] < b.numbers[MAX_SIZE - b.size + i])
            return -1;
    }
    return 0;
}

bigInt
BI_add ( bigInt a, bigInt b )
{
    if (a.sign != b.sign)
    {
        if (a.sign < 0)
        {
            a.sign = 1;
            return (BI_subtract(b, a));
        }
        b.sign = 1;
        return (BI_subtract(a, b));
    }

    bigInt result;
    BI_init(&result);

    int carry = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        int sum = (a.numbers[MAX_SIZE - 1 - i] - '0') + (b.numbers[MAX_SIZE - 1 - i] - '0') + carry;
        result.numbers[MAX_SIZE - 1 - i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    result.size = MAX_SIZE;
    while (result.size > 0 && result.numbers[MAX_SIZE - result.size] == '0')
        result.size--;

    if (result.size == 0)
        result.size = 1;

    result.sign = a.sign;
    result.overflow = carry;
    return result;
}

bigInt BI_subtract ( bigInt a, bigInt b )
{
    bigInt result;
    BI_init(&result);
    
    if (a.sign != b.sign)
    {
        if (a.sign < 0)
        {
            b.sign = -1;
            return (BI_add(b, a));
        }
        b.sign = 1;
        return (BI_add(a, b));
    }

    int comparison = BI_compare(a, b);
    if (comparison < 0)
    {
        bigInt temp = a;
        a = b;
        b = temp;
        result.sign = -1;
    }
    else
    {
        result.sign = a.sign;
    }

    int borrow = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        int diff = (a.numbers[MAX_SIZE - 1 - i] - '0') - (b.numbers[MAX_SIZE - 1 - i] - '0') - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        result.numbers[MAX_SIZE - 1 - i] = diff + '0';
    }

    result.size = MAX_SIZE;
    while (result.size > 0 && result.numbers[MAX_SIZE - result.size] == '0')
        result.size--;

    if (result.size == 0)
        result.size = 1;

    return result;
}

bigInt
BI_shiftLeft( bigInt num, int shift )
{
    bigInt result;
    BI_init(&result);

    if (shift >= MAX_SIZE)
    {
        result.overflow = 1;
        return result;
    }

    for (int i = 0; i < MAX_SIZE - shift; i++)
    {
        result.numbers[i] = num.numbers[i + shift];
    }

    result.size = num.size + shift;
    if (result.size > MAX_SIZE)
    {
        result.overflow = 1;
        result.size = MAX_SIZE;
    }

    result.sign = num.sign;
    return result;
}

bigInt
BI_multiply( bigInt a, bigInt b )
{
    bigInt result;
    BI_init(&result);

    for (int i = 0; i < b.size; i++)
    {
        bigInt temp;
        BI_init(&temp);
        int digit = b.numbers[MAX_SIZE - 1 - i] - '0';

        int carry = 0;
        for (int j = 0; j < a.size; j++)
        {
            int prod = digit * (a.numbers[MAX_SIZE - 1 - j] - '0') + carry;
            temp.numbers[MAX_SIZE - 1 - j] = (prod % 10) + '0';
            carry = prod / 10;
        }
        
        if (carry > 0)
        {
            temp.numbers[MAX_SIZE - a.size - 1] = carry + '0';
            temp.size = a.size + 1;
        }
        else
        {
            temp.size = a.size;
        }

        temp = BI_shiftLeft(temp, i);
        result = BI_add(result, temp);
    }

    result.sign = (a.sign == b.sign) ? 1 : -1;
    return result;
}