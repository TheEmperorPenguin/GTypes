#ifndef BIGINT_H
# define BIGINT_H

#   define MAX_SIZE 1024
#   define wwrite(x) write(1, x, strlen(x));
#   define ewrite(x) write(1, x, strlen(x));

#   include <stdio.h>
#   include <unistd.h>
#   include <string.h>

//char based until i think of a better way to memorize data
// int to get size ? update to long ? to bigInt itself ? int should be far suffficient for most use but who knows

//create a table to link int error to actual error messages (already kind of doing it with the #ifdef DEBUG but the code looks messy)

//No input verification on user input when setValue used for now, will add something but maybe in another function? or set with a define so it's removable if user is sure of input

typedef struct s_bigInt
{
    char    numbers[MAX_SIZE];
    int     sign;
    int     size;
    int     overflow;
}   bigInt;




void    BI_print( bigInt num );

void    BI_init( bigInt * num );

int     BI_setValue( bigInt * num, char * str );

int     BI_getSize( bigInt a );

bigInt  BI_add ( bigInt a, bigInt b );
bigInt  BI_subtract ( bigInt a, bigInt b );

#endif