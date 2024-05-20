#include "bigInt.h"

void 
test_BI_add()
{
    // Test cases for BI_add

    // Test adding positive numbers
    bigInt a, b, result;
    BI_setValue(&a, "123456");
    BI_setValue(&b, "789012");
    result = BI_add(a, b);
    wwrite("123456 + 789012 = ");
    BI_print(result);

    // Test adding negative numbers
    BI_setValue(&a, "-123456");
    BI_setValue(&b, "-789012");
    result = BI_add(a, b);
    wwrite("-123456 + (-789012) = ");
    BI_print(result);

    // Test adding positive and negative numbers
    BI_setValue(&a, "9123456");
    BI_setValue(&b, "-789012");
    result = BI_add(a, b);
    wwrite("9123456 + -789012 = ");
    BI_print(result);

    BI_setValue(&a, "9123456");
    BI_setValue(&b, "-789012");
    result = BI_add(b, a);
    wwrite("-789012 + 9123456 = ");
    BI_print(result);

    // Test addition resulting in overflow
    BI_setValue(&a, "999999");
    BI_setValue(&b, "1");
    result = BI_add(a, b);
    wwrite("999999 + 1 = ");
    BI_print(result);

    // Test addition with different digit lengths
    BI_setValue(&a, "1234567890");
    BI_setValue(&b, "987654321");
    result = BI_add(a, b);
    wwrite("1234567890 + 987654321 = ");
    BI_print(result);
}

int
main( void )
{
    unsigned int errors = 0;

    test_BI_add();

    return (errors);
}