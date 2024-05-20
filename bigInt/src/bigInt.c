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

bigInt
BI_add ( bigInt a, bigInt b )
{
    if (a.sign != b.sign)
    {
        if (a.sign < 0)
            return (BI_subtract(b, a));
        return (BI_subtract(a, b));
    }

    //is final size sufficient?
    
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

bigInt
BI_subtract ( bigInt a, bigInt b ) // check sign, check size and handle when what is substracted bigger than what you substract from.
{
    bigInt result;
    BI_init(&result);
    
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

    result.sign = a.sign;
    return result;
}
