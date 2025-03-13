/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int result;
int getByte(int x, int n) {
    x = x >> (n << 3);         //x 右移 8n 位     *** 8n = n 左移 3位 ***
    result = x & 0xFF;      //取最低有效字节
    return result;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int tmp = ((1 << 31) >> n) << 1;     //得到前32 - n位为0，后 n 位为 1 的二进制数
    int result = ((x >> n) & ~tmp);      //x算数右移后将右移空出的位全置为0  tip:～tmp   为低32 - n位为1，高 n 位为 0 的二进制数
    return result;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int tmp1, tmp2, tmp3, tmp4, tmp5;
int bitCount(int x) {
    tmp1 = (0x55 << 8) | (0x55);      // tmp1 = 0x00 00 55 55
    tmp1 = (tmp1 << 16) | tmp1;          // tmp1 = 0x55 55 55 55
    
    tmp2 = (0x33 << 8) | (0x33);      // tmp2 = 0x00 00 33 33
    tmp2 = (tmp2 << 16) | tmp2;         // tmp2 = 0x33 33 33 33
    
    tmp3 = (0x0f << 8) | (0x0f);    // tmp3 = 0x00 00 0f 0f
    tmp3 = (tmp3 << 16) | tmp3;         // tmp3 = 0x0f 0f 0f 0f
    
    tmp4 = (0xff) | (0xff << 16);   // tmp4 = 0x00 ff 00 ff
    tmp5 = (0xff) | (0xff << 8);    // tmp5 = 0x00 00 ff ff
    
    x = (x & tmp1) + ((x >> 1) & tmp1);     //低一位的1的个数 + 高一位的1的个数 = 相邻两位1的个数
    x = (x & tmp2) + ((x >> 2) & tmp2);     //低相邻两位的1的个数 + 高相邻两位的1的个数 = 相邻四位的1的个数
    x = (x + (x >> 4)) & tmp3;
    x = (x + (x >> 8)) & tmp4;
    x = (x + (x >> 16)) & tmp5;
    return x;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    x = (~x + 1) | x;
    x = x >> 31;
  return ~x & 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;    //0x80 00 00 00
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1        0011
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    n = 32 + (~n + 1);              //用补码加法运算 代替 二进制减法运算 n = 32 - n
    result = (x << n) >> n;     //左移 32-n 位 再 右移 32 - n 位， 保留低n位
  return !(x ^ result);             //原来的数应与移位后的数相等
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int sign = x >> 31;               // 获取x的最高位，即符号位
    int bias = (1<< n) + (~1 + 1);
    x = x + (bias & sign);            // 负数加上偏移量
    return x >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;        //根据补码运算 取反加1
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return !(x >> 31) & (!!x);        //正数符号位为0 负数符号位位1 返回符号位取非即可 特殊处理0
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 
 3
 */
int isLessOrEqual(int x, int y) {
    int x_sign = (x >> 31) & 1;
    int y_sign = (y >> 31) & 1;
    
    //x与y异号 x_sign = 1 y_sign = 0; x与y同号 x < y 判断x - y 的符号位是否为1; x = y;
    int tmp = x + (~y + 1);
    int tmp_sign = (!(x_sign ^ y_sign)) & ( (tmp >> 31) & 1);
    
  return (x_sign & !y_sign) | tmp_sign | !(x ^ y);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int cnt = 0;
    cnt = (!!(x >> 16)) << 4;                    //判断高16位是否有1， 如果有1 x >> 16 后取两次非结果一定是1 有则结果+16
    cnt = cnt + ((!!(x >> (8 + cnt))) << 3);    //用二分法继续计算
    cnt = cnt + ((!!(x >> (4 + cnt))) << 2);
    cnt = cnt + ((!!(x >> (2 + cnt))) << 1);
    cnt = cnt + (!!(x >> (1 + cnt)));
  return cnt;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned result = uf ^ 0x80000000;
    unsigned tmp = uf & 0x7fffffff;
    if (tmp > 0x7f800000)
        result = uf;
 return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    unsigned shiftLeft = 0;
    unsigned afterShift, tmp, flag;
    unsigned absX = x;
    unsigned sign = 0;
    if (x == 0)
        return 0;
    if (x < 0) {
        sign = 0x80000000;
        absX = -x;
    }
    afterShift = absX;
    while (1) {
        tmp = afterShift;
        afterShift = afterShift << 1;
        shiftLeft ++ ;
        if (tmp & 0x80000000)
            break;
    }
    if ((afterShift & 0x01ff) > 0x0100)
        flag = 1;
    else if ((afterShift & 0x03ff) == 0x0300)
    flag = 1;
    else
        flag = 0;
    return (sign + (afterShift >> 9) + ((159 - shiftLeft) << 23) + flag);
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//阶码+1
unsigned float_twice(unsigned uf) {
    int sign = (uf >> 31) & 1;
    
    //非规格化数，尾数左移1位
    if ((uf & 0x7f800000) == 0)
    {
        uf = ((uf & 0x007fffff) << 1) | (uf & 0x7f800000) | (sign << 31);
    }
    //规格化数，阶码+1
    else if ((uf & 0x7f800000) != 0x7f800000)
    {
        uf = uf + 0x00800000;
    }
  return uf;
}
