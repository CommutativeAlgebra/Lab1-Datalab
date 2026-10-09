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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int eitherOne = ~(~x & ~y);     /* x | y: 德摩根律展开 */
  int bothOne = x & y;            /* x & y: 两位同时为 1 */
  return eitherOne & ~bothOne;    /* (x|y) & ~(x&y) */
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int signMask = x >> 31;         /* x<0 -> 全 1, x>=0 -> 0 */
  int negX = ~x + 1;              /* -x 的补码写法 */
  return signMask & negX;         /* 非负时被掩码清零 */
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;                           /* 源字节的位偏移 = src*8 */
  int dstShift = dst << 3;                           /* 目标字节的位偏移 = dst*8 */
  int byte = (x >> srcShift) & 0xFF;                 /* 取出源字节 (0xFF 剪掉算术右移的符号扩展) */
  int clearDst = ~(0xFF << dstShift);      /* 目标字节位置挖洞, 其余位保持 1 */
  int cleared = x & clearDst;                        /* 目标字节已清 0 */
  return cleared | (byte << dstShift);               /* 把源字节回填到目标位置 */
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int signBit = 1 << 31;              /* 只有一个 1 在最高位 */
  int smear = signBit >> n;           /* 最高 n+1 位为 1 */
  int keepLow = ~(smear << 1);        /* 高 n 位为 0 的掩码 */
  int shifted = x >> n;               /* 算术右移: 高位可能被符号位污染 */
  return shifted & keepLow;           /* 清除符号扩展位 */
}
// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int m = 0x0F | (0x0F << 8);             /* 0x00000F0F */
  int lowNibbles, highNibbles;
  m = m | (m << 16);                      /* 0x0F0F0F0F: 每字节的低 4 位 */
  lowNibbles = (x & m) << 4;              /* 低半字节搬到高半字节 */
  highNibbles = (x >> 4) & m;             /* 高半字节搬到低半字节 */
  return lowNibbles | highNibbles;        /* 两块拼起来 */
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y = ~x;                     /* x 的 0 -> y 的 1 */
  int low = y & (~y + 1);         /* 最低的那一个 0 位 */
  int rest = y ^ low;             /* 抠掉它 */
  return rest & (~rest + 1);      /* 剩下的最低 1 位 = 第二低的 0 位 (空则 0) */
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);              /* 32 位折成 16 位 */
  x = x ^ (x >> 8);               /* 16 -> 8 */
  x = x ^ (x >> 4);               /* 8 -> 4 */
  x = x ^ (x >> 2);               /* 4 -> 2 */
  x = x ^ (x >> 1);               /* 2 -> 1: bit0 = 全部位的异或 */
  return ~x & 1;                  /* 个数为偶数时返回 1 */
}
// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int k = n & 31;                           /* 规约移位量, 兼容 n >= 32 */
  int left = (32 + ~k + 1) & 31;            /* 32-k, 且 k=0 时为 0 (避免移 32 位) */
  int keepLow = ~(((1 << 31) >> k) << 1);   /* 清掉算术右移补进来的高 k 位 */
  int moved = x >> k;                       /* 普通右移: 高位可能是符号扩展 */
  int logical = moved & keepLow;            /* 变成逻辑右移: 掉出去的低位不在这里 */
  int wrap = x << left;                     /* 掉出去的低位绕回到最高位 */
  return logical | wrap;                    /* 两段拼成循环右移 */
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int q = x >> n;                                 /* 商 */
  int half = 1 << (n + ~0);                       /* 2^(n-1): 半个步长 */
  int oddQuotientBit = q & 1;                     /* 商的奇偶: 半整数时用来"取偶" */
  int bias = (half + ~0) + oddQuotientBit;        /* half-1 + 商的奇偶位 (余数已含在 x 里) */
  int rounded = (x + bias) >> n;                  /* 加偏置后取商 (就近舍入) */
  return rounded << n;                            /* 再乘回 2^n, 低位全 0 */
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int commonBits = x & y;                         /* x、y 公共的 1 */
  int differingHalf = (x ^ y) >> 1;               /* 不同部分的"一半" */
  int mid = commonBits + differingHalf;           /* floor((x+y)/2), 永不溢出 */

  int xMinusY = x + ~y + 1;                       /* x - y (同号时精确, 异号且相差足够大时失真) */
  int signsDiffer = (x ^ y) >> 31;                /* x、y 异号时全 1 */
  int signsClash = (xMinusY ^ x) >> 31;           /* d 的符号与 x 不符时全 1 -> 差值溢出了 */
  int signCorrect = signsDiffer & signsClash;     /* 两个条件同时成立时符号位是错的 */
  int geMask = ~((xMinusY >> 31) ^ signCorrect);  /* 全 1 <=> x >= y */

  int isHalf = (x ^ y) & 1;                       /* 1 <=> 真实中点是半整数 */
  int adjust = geMask & isHalf;                   /* 半整数且 x 较大时进位 1, 否则 0 */
  return mid + adjust;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* 第一部分: 无溢出地判断 x >= a */
  /* d = x - a; 若 x、a 异号且 d 的符号与 x 不符, 说明差值溢出, 符号位要翻转 */
  int xMinusA = x + ~a + 1;               /* x - a */
  int geA = ~((xMinusA >> 31) ^ (((x ^ a) >> 31) & ((xMinusA ^ x) >> 31)));
  /* geA 全 1 <=> x >= a, 0 <=> x < a */

  /* 第二部分: 无溢出地判断 x >= b (完全同理) */
  int xMinusB = x + ~b + 1;               /* x - b */
  int geB = ~((xMinusB >> 31) ^ (((x ^ b) >> 31) & ((xMinusB ^ x) >> 31)));
  /* geB 全 1 <=> x >= b */

  /* 第三部分: 拼出 0/1 的最终答案 */
  int inside = geA ^ geB;                 /* 全 1 <=> 恰好一个成立 */
  int onEndpoint = !(x ^ a) | !(x ^ b);   /* 1 <=> x 落在端点上 */
  return (inside | onEndpoint) & 1;       /* 归一化成 0/1 */
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int fourX = x << 2;                                               /* 4x 的低 32 位 */
  int lowSum = fourX + x;                                           /* 5x 的低 32 位 */
  int carry = (((fourX & x) | ((fourX | x) & ~lowSum)) >> 31) & 1;  /* 加法的进位 */
  int high = (x >> 30) + (x >> 31) + carry;                         /* 64 位和的高位字 (只可能是 -3..2) */
  int mismatch = high ^ (lowSum >> 31);                             /* 非 0 <=> 高位字不是符号扩展 = 溢出 */
  int satValue = (1 << 31) ^ ~(x >> 31);                            /* x>=0 -> INT_MAX, x<0 -> INT_MIN */
  int overflowMask = (mismatch | (~mismatch + 1)) >> 31;            /* 溢出时全 1, 否则 0 */
  return (lowSum & ~overflowMask) | (satValue & overflowMask);      /* 无分支选择 */
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 第一级: x + y */
  int low1 = x + y;                                                /* 低位和 */
  int carry1 = (((x & y) | ((x | y) & ~low1)) >> 31) & 1;          /* 往第 32 位的进位 */

  /* 第二级: (x+y) + z */
  int low = low1 + z;                                              /* 低位和 */
  int carry2 = (((low1 & z) | ((low1 | z) & ~low)) >> 31) & 1;

  /* 高位字与判定 */
  int high = (x >> 31) + (y >> 31) + (z >> 31) + carry1 + carry2;  /* 64 位和的高位字 */
  int d = high + ~(low >> 31) + 1;                                 /* H - sign(low), =0 表示恰好装得下 */
  int nonzeroMask = (d | (~d + 1)) >> 31;                          /* d != 0 时全 1 */
  int negativeMask = d >> 31;                                      /* d < 0 时全 1 */
  return (nonzeroMask & ~negativeMask & 1) | negativeMask;         /* 1 / 0 / -1 */
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {

  /* 拆位域 */
  unsigned sign = uf & 0x80000000;        /* 符号位 */
  unsigned exp = (uf >> 23) & 0xFF;       /* 阶码域 */
  unsigned frac = uf & 0x7FFFFF;          /* 尾数域 */

  unsigned mant;      /* 3 * (f 的整数尾数形式), 即要舍入的那个整数 n */
  unsigned shift;     /* 需要丢掉的低位数 = ulp 相对 2^-150 的倍数 */
  unsigned expOut;    /* 结果里的阶码域 */
  unsigned q;         /* 舍入后的尾数 */
  unsigned roundBit;  /* 公共舍入用的"半个 ulp 位" */

  if (exp == 0xFF) return uf;             /* Inf / NaN: 原样返回 */
  if ((exp | frac) == 0) return uf;       /* ±0: 原样返回, 保留 -0 */

  if (exp == 0) {                         /* ---- 非规格化: 真值 = frac * 2^-149 ---- */
    mant = (frac << 1) + frac;            /* n = 3*frac, 真值*1.5 = n * 2^-150 */
    if (mant < 0x1000000) {               /* n < 2^24: 结果仍是非规格化数 */
      q = mant >> 1;                      /* n/2: 步长从 2^-150 换到 2^-149 */
      if (mant & 1) {                     /* n 为奇数 -> 恰好半整数, 取偶 */
        q = q + (q & 1);                  /* 尾数为奇就进位到偶数 */
      }
      return sign | q;                    /* q 恰为 2^23 时自动变成 2^-126 */
    }
    shift  = 1;                           /* 结果是规格化数: 丢 1 位 */
    expOut = 1;                           /* 阶码域 = 1 (即 2^-126) */
  } else {                                /* ---- 规格化: 真值 = 1.frac * 2^(exp-127) ---- */
    mant = ((frac | 0x800000) << 1) + (frac | 0x800000);  /* n = 3M, M 含隐藏 1 */
    shift = (mant >> 25) + 1;             /* 最高位在第 24 或 25 位 -> shift = 1 或 2 */
    expOut = shift + exp - 1;             /* 结果阶码域 */
  }

  /* 公共舍入: 把 mant 的低 shift 位按"就近偶数"消掉 (偏置法, 同 P10) */
  roundBit = (mant >> shift) & 1;         /* 被丢掉部分的最高位 = 半个 ulp 位 */
  q = mant + (1u << (shift - 1)) - 1 + roundBit;   /* 加偏置: 余数 > half 进位, = half 看奇偶 */
  q = q >> shift;                         /* 丢掉低 shift 位 */
  if (q >> 24) {                          /* q 进到了 2^24: 尾数溢出 */
    q = q >> 1;                           /* 尾巴右移一位 */
    expOut = expOut + 1;                  /* 阶码加一 */
  }

  if (expOut >= 255) return sign | 0x7F800000;   /* 溢出到无穷 (含舍入凑到 2^128) */
  return sign | (expOut << 23) | (q & 0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;        /* 符号位 */
  unsigned exp = (uf >> 23) & 0xFF;       /* 阶码域 */
  unsigned frac = uf & 0x7FFFFF;          /* 尾数域 */

  unsigned mant;      /* 24 位尾数 (含隐藏 1): M */
  unsigned drop;      /* 要清掉的低位个数 1..23 */
  unsigned roundBit;  /* 被丢掉部分的最高位 = 半个 ulp 位 */
  unsigned rounded;   /* 就近偶数舍入后的尾数 */

  if (exp == 0xFF) return uf;             /* Inf / NaN 原样返回 */
  if (exp < 126) return sign;             /* |v| < 0.5 -> ±0 (保留符号) */
  if (exp == 126) {                       /* 0.5 <= |v| < 1 */
    if (frac) return sign | 0x3F800000;   /* 严格大于 0.5 -> ±1.0 */
    return sign;                          /* 恰好 0.5: 取偶 -> ±0 */
  }
  if (exp >= 150) return uf;              /* |v| >= 2^23: 已是整数, 原样返回 */

  drop = 150 - exp;                       /* 要清掉的低位个数 (1..23) */
  mant = frac | 0x800000;                 /* 24 位尾数 (含隐藏 1) */
  roundBit = (mant >> drop) & 1;          /* 半个 ulp 位: 决定"入"还是"舍" */

  /* 清掉低 drop 位, 就近偶数舍入 (偏置法) */
  rounded = mant + (1u << (drop - 1)) - 1 + roundBit;
  rounded = (rounded >> drop) << drop;

  exp = exp + (rounded >> 24);            /* 尾数进位到 2^24 时阶码 +1 */
  return sign | (exp << 23) | (rounded & 0x7FFFFF);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = x & 0x80000000;         /* 符号位 */
  unsigned magnitude = x;                 /* |x| (无符号形式) */
  unsigned exp = 31;                      /* 无偏阶码初值 */
  unsigned mant, roundBit, sticky;

  if (x == 0) return 0;                   /* 0 -> +0 的全零位型 */
  if (x < 0) magnitude = ~magnitude + 1;  /* magnitude = -x, 对 INT_MIN 也正确 */

  while (!(magnitude & 0x80000000)) {     /* 左移规格化: 把最高 1 顶到 bit31 */
    magnitude = magnitude << 1;
    exp = exp - 1;                        /* 每移一位, 无偏阶码减一 */
  }

  mant = magnitude >> 8;                  /* 24 位: 隐藏 1 + 23 位尾数 */
  roundBit = (magnitude >> 7) & 1;        /* 舍入位 (低 8 位的最高位) */
  sticky = (magnitude & 0x7F) != 0;       /* 粘滞位: 低 7 位是否还有 1 */
  mant = mant + (roundBit & (sticky | (mant & 1)));   /* 就近偶数舍入 (可能进位到 2^24) */

  return sign | ((exp + 127 + (mant >> 24)) << 23) | (mant & 0x7FFFFF);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m  = 0x0F | (0x0F << 8);        /* 0x00000F0F */
  int m3, m5, m8, m16;

  m = m | (m << 16);                  /* 0x0F0F0F0F: 每字节低半字节 */
  m3 = m ^ (m << 2);                  /* 0x33333333: 0x0F^0x3C = 0x33 */
  m5 = m3 ^ (m3 << 1);                /* 0x55555555: 0x33^0x66 = 0x55 */
  m8 = 0xFF | (0xFF << 16);           /* 0x00FF00FF: 两个低字节 */
  m16 = 0xFF | (0xFF << 8);           /* 0x0000FFFF: 低 16 位 */

  x = (x & m5) + ((x >> 1)  & m5);    /* 组宽 2: 相邻两位的 1 的个数 */
  x = (x & m3) + ((x >> 2)  & m3);    /* 组宽 4 */
  x = (x & m) + ((x >> 4)  & m);      /* 组宽 8 */
  x = (x & m8) + ((x >> 8)  & m8);    /* 组宽 16 */
  x = (x & m16) + ((x >> 16) & m16);  /* 组宽 32: 全部 1 的个数 */
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m = 0x0F | (0x0F << 8);             /* 0x00000F0F */
  int m3, m5, b8;                         /* m5 = 0x55555555, b8 = 0x0000FF00 */

  m = m | (m << 16);                      /* 0x0F0F0F0F: 每字节的低半字节 */
  m3 = m ^ (m << 2);                      /* 0x33333333: 每 2 位一组的低位 */
  m5 = m3 ^ (m3 << 1);                    /* 0x55555555: 每 1 位一组的低位 */
  b8 = 0xFF << 8;                         /* 0x0000FF00, 字节序倒置复用 */

  x = ((x & m5) << 1) | ((x >> 1) & m5);  /* 每个 2 位组内部翻转 */
  x = ((x & m3) << 2) | ((x >> 2) & m3);  /* 每个 4 位组 (半字节) 内部翻转 */
  x = ((x & m)  << 4) | ((x >> 4) & m);   /* 每个 8 位组 (字节) 内部翻转 */

  /* 字节序倒置: b3 b2 b1 b0 -> b0 b1 b2 b3 */
  x = ((x >> 24) & 0xFF) | ((x >> 8) & b8) | ((x & b8) << 8) | (x << 24);
  return x;
}
