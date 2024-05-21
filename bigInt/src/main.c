#include "bigInt.h"

int compare_bigInt(bigInt a, bigInt b) {
    if (a.sign != b.sign) return 0;
    if (a.size != b.size) return 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (a.numbers[i] != b.numbers[i]) return 0;
    }
    return 1;
}

void test_BI_multiply()
{
    int error_count = 0;

    bigInt a, b, result, expected;

    // Test multiplying positive numbers
    BI_setValue(&a, "123");
    BI_setValue(&b, "456");
    result = BI_multiply(a, b);
    BI_setValue(&expected, "56088");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 123 * 456\n");
    }

    // Test multiplying negative numbers
    BI_setValue(&a, "-123");
    BI_setValue(&b, "-456");
    result = BI_multiply(a, b);
    BI_setValue(&expected, "56088");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in -123 * -456\n");
    }

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Total errors: %d\n", error_count);
    wwrite(buffer);
}

void
test_BI_subtract()
{
    int error_count = 0;

    bigInt a, b, result, expected;

    // Test subtracting positive numbers
    BI_setValue(&a, "789012");
    BI_setValue(&b, "123456");
    result = BI_subtract(a, b);
    BI_setValue(&expected, "665556");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 789012 - 123456\n");
    }

    // Test subtracting negative numbers
    BI_setValue(&a, "-789012");
    BI_setValue(&b, "-123456");
    result = BI_subtract(a, b);
    BI_setValue(&expected, "-665556");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in -789012 - (-123456)\n");
    }

    // Test subtracting positive from negative
    BI_setValue(&a, "-789012");
    BI_setValue(&b, "123456");
    result = BI_subtract(a, b);
    BI_setValue(&expected, "-912468");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in -789012 - 123456\n");
    }

    // Test subtracting negative from positive
    BI_setValue(&a, "789012");
    BI_setValue(&b, "-123456");
    result = BI_subtract(a, b);
    BI_setValue(&expected, "912468");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 789012 - (-123456)\n");
    }

    // Test subtraction resulting in negative result
    BI_setValue(&a, "123456");
    BI_setValue(&b, "789012");
    result = BI_subtract(a, b);
    BI_setValue(&expected, "-665556");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 123456 - 789012\n");
    }

    // Test subtraction with different digit lengths
    BI_setValue(&a, "1234567890");
    BI_setValue(&b, "987654321");
    result = BI_subtract(a, b);
    BI_setValue(&expected, "246913569");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 1234567890 - 987654321\n");
    }

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Total errors: %d\n", error_count);
    wwrite(buffer);
}

void test_BI_add()
{
    int error_count = 0;

    bigInt a, b, result, expected;

    // Test adding positive numbers
    BI_setValue(&a, "123456");
    BI_setValue(&b, "789012");
    result = BI_add(a, b);
    BI_setValue(&expected, "912468");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 123456 + 789012\n");
    }

    // Test adding negative numbers
    BI_setValue(&a, "-123456");
    BI_setValue(&b, "-789012");
    result = BI_add(a, b);
    BI_setValue(&expected, "-912468");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in -123456 + (-789012)\n");
    }

    // Test adding positive and negative numbers
    BI_setValue(&a, "9123456");
    BI_setValue(&b, "-789012");
    result = BI_add(a, b);
    BI_setValue(&expected, "8334444");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 9123456 + -789012\n");
    }

    BI_setValue(&a, "9123456");
    BI_setValue(&b, "-789012");
    result = BI_add(b, a);
    BI_setValue(&expected, "8334444");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in -789012 + 9123456\n");
    }

    // Test addition resulting in overflow
    BI_setValue(&a, "999999");
    BI_setValue(&b, "1");
    result = BI_add(a, b);
    BI_setValue(&expected, "1000000");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 999999 + 1\n");
    }

    // Test addition with different digit lengths
    BI_setValue(&a, "1234567890");
    BI_setValue(&b, "987654321");
    result = BI_add(a, b);
    BI_setValue(&expected, "2222222211");
    if (!compare_bigInt(result, expected)) {
        error_count++;
        wwrite("Error in 1234567890 + 987654321\n");
    }

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Total errors: %d\n", error_count);
    wwrite(buffer);
}


int
main( void )
{
    unsigned int errors = 0;

    test_BI_add();
    test_BI_subtract();
    test_BI_multiply();
    bigInt a, b, result;
    BI_setValue(&a, "10011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011001");
    BI_setValue(&b, "510011001100110011001100110011001100110011001");
    result = BI_add(a, b);
    BI_print(result);

    return (errors);
}