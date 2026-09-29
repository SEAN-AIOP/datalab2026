/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */
 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}
/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (x && y) {
        return !((x >> 31) ^ (y >> 31));
    }
    return !(x ^ y);
}
/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int t1 = (v >> 16) > 0;
    r = r | (t1 << 4);
    int t2 = (v >> (r | 8)) > 0;
    r = r | (t2 << 3);
    int t3 = (v >> (r | 4)) > 0;
    r = r | (t3 << 2);
    int t4 = (v >> (r | 2)) > 0;
    r = r | (t4 << 1);
    int t5 = (v >> (r | 1)) > 0;
    r = r | t5;
    return r;
}
/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nb = n << 3;
    int mb = m << 3;
    int a = (x >> nb) & 0xFF;
    int b = (x >> mb) & 0xFF;
    return (x ^ (a << nb) ^ (b << mb)) | (a << mb) | (b << nb);
}
/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    int i;
    for (i = 32; i; i--) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
    }
    return r;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int z = !n;
    int keep = z + ~0;
    int s = (n + ~0) & keep;
    int fill = ~(0x7FFFFFFF >> s) & keep;
    return (x >> n) & ~fill;
}
/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y = ~x;
    int c = 0;
    int t1 = !(y >> 16);
    c = c + (t1 << 4);
    int t2 = !(y >> (25 + ~c));
    c = c + (t2 << 3);
    int t3 = !(y >> (29 + ~c));
    c = c + (t3 << 2);
    int t4 = !(y >> (31 + ~c));
    c = c + (t4 << 1);
    int t5 = !(y >> (32 + ~c));
    c = c + t5;
    int t6 = !y;
    c = c + t6;
    return c;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x;
    unsigned sign, ax, res;
    int e = 31, m;
    if (x == 0) return 0;
    sign = ux & 0x80000000;
    if (sign) ux = -ux;
    ax = ux;
    while (!(ax & 0x80000000)) {
        ax = ax << 1;
        e = e - 1;
    }
    m = ax & 0xFF;
    ax = ax >> 8;
    if (m > 0x80) ax = ax + 1;
    else if (m == 0x80) {
        if (ax & 1) ax = ax + 1;
    }
    if (ax & 0x1000000) {
        ax = ax >> 1;
        e = e + 1;
    }
    res = sign | ((e + 127) << 23) | (ax & 0x7FFFFF);
    return res;
}
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned sign = uf & 0x80000000;
    if (exp == 0xFF) return uf;
    if (exp == 0) return sign | (uf << 1);
    if (exp == 0xFE) return sign | 0x7F800000;
    return sign | ((exp + 1) << 23) | (uf & 0x7FFFFF);
}
/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sgn = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned m;
    if (exp < 1023) return 0;
    if (exp > 1054) return 0x80000000;
    m = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    m = m >> (1054 - exp);
    if (sgn) {
        if (m > 0x80000000) return 0x80000000;
        return -m;
    }
    if (m > 0x7FFFFFFF) return 0x80000000;
    return m;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) return 0x7F800000;
    if (x >= -126) return (x + 127) << 23;
    if (x >= -149) return 1 << (x + 149);
    return 0;
}
