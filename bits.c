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
	int val = (1 << 31);
	return val;
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
	return ~(~((~x) & y) & ~(x & (~y)));
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
    int mask = (x >> 31);
    int ans = (~x + 1) & mask;
    return ans;
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
   int mask_ori = 0xFF;
   int m_src = src<<3;
   int m_dst = dst<<3;
   int mask_dst = mask_ori << m_dst;
   
   int changed_byte = (mask_ori << m_src) & x;
   int changed_to_0 = changed_byte >> m_src;     //把要改变的byte移到最低位：第0位。
   int changed_to_dst = (~mask_dst) | (changed_to_0 << m_dst);						 
   int changed = (changed_to_dst) & (mask_dst | x);
   return changed; 
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
    int ari_s = x >> n; //arithmetic shift result 
    int mask = ~(((1 << 31) >> n) << 1) ; // 构造掩码。	
    int result = mask & ari_s;
    return result;    
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
    int leftmask = (0x0F << 24) | (0x0F << 16) | (0x0F << 8) | 0x0F; 	
    int rightmask = leftmask << 4;
    int x_right = rightmask & x;
    int x_right_shift = (~((1 << 31) >> 3)) & (x_right >> 4);
    int x_left_shift = (leftmask & x) << 4;
    int result = x_right_shift | x_left_shift;
    return result;
    		
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
    int firstmask = (x + 1) & (~x);
    int x_complemented = x + firstmask; //补上最低位的0  
    int secondmask = (x_complemented + 1) & (~x_complemented);
    return secondmask;    
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
    int signal = 3;
    
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;
    x = x >> 2;
    signal = signal ^ x;

    int ans = (~(((signal & 2)>>1) ^ (signal & 1))) & 1;
    return ans;
    
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
    int mask1 = ((1<<31)>>(31^n));
    int mask2 = ~mask1;
    int rightpart = mask1 & x;
    int lsmask = ~(((1<<31)>>n)<<1);
    int rightshifted = lsmask & (rightpart >> n);
    int leftpartshifted = (mask2 & x) << ((31 ^ n) + 1);
    return rightshifted | leftpartshifted;
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
    int mask1 = (1 << n) + ~0;
    int low_part = mask1 & x;
    int bias = (1 << (n + ~0)) + ~0; 
    int mask2 = 1 << n; 
    int added_low_part = low_part + ((mask2 & x) >> n) + bias;
    int increment = added_low_part & mask2; //增量
    int ans = (x & (~mask1)) + increment;
    return ans;    
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
     int y_end = (y >> 31) & 1;
     int x_end = (x >> 31) & 1;	 	 
     int gap = y + ~x + 1; 	
     int bias = ((((gap) >> 31) & 1) | (y_end & ~x_end)) & (~((~y_end) & x_end));   		     //确定是否x > y 的signal码,1表示数学上 x > y.
												 			     		    
     //int bias = (((y - x) & mask_end) >> 31) & ((x & 1) ^ (y & 1));
     int complement = ((x & 1) & (y & 1)); //x + y都是奇数时，x/2与y/2都会损失0.5，加起来就是1，要补。
     bias = bias & ((x & 1) ^ (y & 1)); //要注意即便x > y,只有当 x和y奇偶性不想同时，才要考虑增加bias使得(x + y)/2作为小数向高处进。					   
     int ans = ((x >> 1) + (y >> 1)) + bias + complement;
     return ans;     
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
    int x_sig = (x >> 31) & 1;
    int a_sig = (a >> 31) & 1;
    int b_sig = (b >> 31) & 1;
    int a_minus_x = a + ~x + 1;
    int b_minus_x = b + ~x + 1;
    
    int x_comp_a = (((a_minus_x >> 31) & 1) | ((a_sig) & (~x_sig))) & (~(x_sig & (~a_sig)));
    int x_comp_b = (((b_minus_x >> 31) & 1) | ((b_sig) & (~x_sig))) & (~(x_sig & (~b_sig)));
    int ans = (x_comp_a ^ x_comp_b) | (!(x ^ a)) | (!(x ^ b));
    return ans;

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
    int sum = (x << 2) + x; //但还不是最终答案。	
    int x_sig = x >> 31;	
    int sum_sig = sum >> 31;
    int posi_1 = !((x>>29) & 3); 
    posi_1 = posi_1 + ~0; 
    int nega_0 = !((~(x>>29)) & 3);
    nega_0 = nega_0 + ~0;   
    int posi_flow = (~x_sig) & (posi_1 | sum_sig); //表示正溢出，32位均为1为正溢出。
    int nega_flow = x_sig & (nega_0 | (~sum_sig)); //类似上一句。
    int intmin = (1 << 31);
    int intmax = ~intmin;
    int temp = sum ^ ((intmax ^ sum) & posi_flow);
    int ans = temp ^ ((intmin ^ temp) & nega_flow);
    return ans;  
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
    int x_sig = (x >> 31) & 1;
    int y_sig = (y >> 31) & 1;
    int z_sig = (z >> 31) & 1;    
    int half_sum = x + y;
    int half_sum_sig = (half_sum >> 31) & 1;   
    int p_flow = ((~x_sig) & (~y_sig)) & half_sum_sig;
    int n_flow = (x_sig & y_sig) & (~half_sum_sig);
    
    int sum = half_sum + z;
    int sum_sig = (sum >> 31) & 1;
    int p_flow_sum = (~half_sum_sig) & (~z_sig) & sum_sig;
    int n_flow_sum = (half_sum_sig) & (z_sig) & (~sum_sig);
    
    int half_flow = p_flow | n_flow; 
    int pos_part = ((~half_flow) & p_flow_sum) | ((p_flow) & (~n_flow_sum));
    int neg_part = ((~half_flow) & n_flow_sum) | ((n_flow) & (~p_flow_sum));
    int ans = pos_part + ~neg_part + 1;
    return ans;
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
    int m1 = 1 << 31;	 //mask 1
    unsigned sign = uf & m1;
    unsigned temp = (m1 >> 8);
    unsigned m2 = temp - m1;
    unsigned unit = (1 << 23); //exp位增加的单位大小。
    unsigned exp = uf & m2;
    unsigned m3 = ~temp;
    unsigned frac = m3 & uf;
    if ((exp >> 23) == 0xFF) {
        return uf;                                                                     
    }//NaN + Inf的返回

    unsigned sum = (frac << 1) + frac;
    unsigned ans;
	
    //要先处理非规格化值
    if (!exp) {
        unsigned sig = sum & (sum >> 1) & 1;
        unsigned new_frac = (sum >> 1) + sig;
        ans = new_frac | sign;
	return ans;
    }
    
    
    sum += (1 << 23);  //规格化值对于小数位加起来的和，要增加0.5（来自0.5 + 0.5 * frac，非规格化无常数项）。
    if ((sum >> 24) & 1) {
        sum -= (1 << 24);  //相当于 + 2 ^ 25 - 2 ^ 26.
	
	exp += unit;
        if ((exp >> 23) == 0xFF) {
	     return temp & (exp | sign);
	}
	
	unsigned flow_bit = 3;
        flow_bit = flow_bit & sum;
	unsigned last_bit = 4 & sum;
	sum = (sum >> 2);
	
	if (flow_bit > 2 || (flow_bit == 2 && last_bit)) {
            sum += 1;           	    
	}	
	ans = sum | exp | sign;
	return ans;
    }

    else {
	unsigned sig = sum & (sum >> 1) & 1;
        unsigned new_frac = (sum >> 1) + sig;
	ans = new_frac | exp | sign;
	return ans;
    }	   
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
    int m1 = 1 << 31;    //mask 1
    unsigned sign = uf & m1;
    unsigned temp = (m1 >> 8);
    unsigned m2 = temp - m1;
    unsigned unit = (1 << 23); //exp位增加的单位大小。
    unsigned exp = (uf & m2);
    unsigned m3 = ~temp;
    unsigned frac = m3 & uf;
    int e = (exp >> 23);
    e = e - 127;
    unsigned ans;
    if (e >= 23 || ((exp >> 23) == 0xFF)) {
        return uf;
    }
    
    if (e <= -2) {
        return sign;
    }
    
    if (e == -1) {
        if (!frac) {
	    return sign;
	}
	else {
	    exp += unit;
	    ans = exp | sign;
	    return ans;
	}
    }   
    frac = frac + (1 << 23);
    unsigned new_temp = ~(m1 >> (e + 8)); //注意这里要利用补码，所以用unsigned的temp >> e不好，应该使用int
    if (((frac & new_temp) == (unit >> (e + 1)) && (frac & (unit >> e))) || (frac & new_temp) > (unit >> (e + 1))) {
        frac += (unit >> e);
    }		     
    frac = frac & ~new_temp;
    //注意：例如frac = 11111....11111 全1的情况，化整数后需要对其四舍五入。
    //这体现在frac舍入后，回到1-23位时，如果最高位又出现了1，那么就说明表示(1 + frac)表示数>=2。
    //实际上只可能等于2.
    
    if (frac & (1 << 24)) {
        frac = 0;
        exp += unit;
	ans = sign | exp | frac;
        return ans;	
    } 
    
    frac -= (1 << 23);
    ans = sign | exp | frac;
    return ans; 
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
   int sign = (1 << 31) & x;
   int m1 = sign >> 31;
   unsigned un_sign = sign;
   unsigned abs_x;
   if (x < 0){
       abs_x = -x;
   }
   else {
       abs_x = x;
   }
   
   if (x == 0) {
       return 0; //0不可能是-0，int没有-0，所以就是+0，对应float位级表示最高也是0，直接返回0即可。
   }
   int expr;
   unsigned ans;
   if (x == (1 << 31)) {
       expr = (158 << 23);
       ans = un_sign | expr;
       return ans; 
   }

   int ct = 0; //count
   unsigned temp = abs_x;		    
   while (temp > 0) {
	ct++;
        temp = temp >> 1;	
   }   
   int m2 = ((1 << 31) >> 8);//高位是1.
   expr = ct;	 //|x| = (2^(ct - 1)) * 规格化后值。
		
      
   if (ct >= 25) {//这一部分要舍入
       unsigned m3 = (1 << (ct - 25));
       unsigned m4 = (1 << 31) >> (55 - ct);
       unsigned omitted = abs_x & (~m4);
       unsigned incr = ((m3 == omitted) && ((m3 << 1) & abs_x)) || (omitted > m3);    //increment
       abs_x = abs_x >> (ct - 24);
       abs_x += incr;

       if ((1 << 23) & abs_x) {
           expr++;
	   abs_x = 0;
       }		   
   } 
   else {
       abs_x = abs_x << (-ct + 24);
   }
   abs_x = abs_x & (~m2);
   expr = expr + 126;
   expr = expr << 23;
   ans = un_sign | expr | abs_x;  
   return ans; 
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
    int mask_4bit = 0x33 | (0x33 << 8) | (0x33 << 16) | (0x33 << 24);
    int mask_2bit = (((mask_4bit >> 1) & mask_4bit) << 1) + mask_4bit;
    int temp = (x & mask_2bit) + ((x >> 1) & mask_2bit);
    temp = (temp & mask_4bit) + ((temp >> 2) & mask_4bit);
    int mask_8bit = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
    temp = (temp & mask_8bit) + ((temp >> 4) & mask_8bit);
    int mask_16bit = 0xFF | (0xFF << 16);
    temp = (temp & mask_16bit) + ((temp >> 8) & mask_16bit);
    int mask_32bit = 0xFF | (0xFF << 8);
    int ans = (temp & mask_32bit) + (temp >> 16);
    return ans;
}

// P19:
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
    int m5 = 0xFF | (0xFF << 8);
    int m4 = m5 ^ (m5 << 8);
    int m3 = m4 ^ (m4 << 4);
    int m2 = m3 ^ (m3 << 2);
    int m1 = m2 ^ (m2 << 1);

    //以下为从小到大分块转换顺序过程。
    int temp = ((x & m1) << 1) + ((x >> 1) & m1);
    temp = ((temp & m2) << 2) + ((temp >> 2) & m2);
    temp = ((temp & m3) << 4) + ((temp >> 4) & m3);
    temp = ((temp & m4) << 8) + ((temp >> 8) & m4);
    temp = (temp << 16) + ((temp >> 16) & m5);
    int ans = temp;
    return ans;
        	    
}
