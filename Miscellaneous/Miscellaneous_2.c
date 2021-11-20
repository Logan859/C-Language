#include <stdio.h>
#include <stdbool.h>

/*
 * => Setting a bit
 * Use the bitwise OR operator (|) to set a bit.
 * number |= 1UL << n;
 *
 * => Clearing a bit
 * Use the bitwise AND operator (&) to clear a bit.
 * number &= ~(1UL << n);
 * That will clear the nth bit of number. You must invert the bit string with the bitwise NOT operator (~), then AND it.
 * 
 * => Toggling a bit
 * The XOR operator (^) can be used to toggle a bit.
 * number ^= 1UL << n;
 * 
 * => Checking a bit
 * To check a bit, shift the number n to the right, then bitwise AND it:
 * bit = (number >> n) & 1U;
 * 
 * => Changing the nth bit to x
 * number = (number & ~(1UL << n)) | (x << n); 
 */
 
/* number=target variable, n=bit number to act upon 0-n */
#define BIT_SET(number,n)      ((number)   |= (1ULL<<(n)))
#define BIT_CLEAR(number,n)    ((number)   &= ~(1ULL<<(n)))
#define BIT_FLIP(number,n)     ((number)   ^= (1ULL<<(n)))
#define BIT_CHECK(number,n)    (!!((number) & (1ULL<<(n))))           // '!!' to make sure this returns 0 or 1

#define BITMASK_SET(x, mask)          ((x) |= (mask))
#define BITMASK_CLEAR(x, mask)        ((x) &= (~(mask)))
#define BITMASK_FLIP(x, mask)         ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x, mask)    (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x, mask)    ((x) & (mask))


typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

#define BOOL(x) (!(!(x)))

#define BitSet(arg,posn) ((arg) | (1L << (posn)))
#define BitClr(arg,posn) ((arg) & ~(1L << (posn)))
#define BitTst(arg,posn) BOOL((arg) & (1L << (posn)))
#define BitFlp(arg,posn) ((arg) ^ (1L << (posn)))

// Map range value to given range
//MAP_RANGE(VALUE, FROMLOW, FROMHIGH, TOLOW, TOHIGH)
#DEFINE MAP_RANGE(VALUE, IN_MIN, IN_MAX, OUT_MIN, OUT_MAX)  \
(((VALUE - IN_MIN) * (OUT_MAX - OUT_MIN)) / ((IN_MAX - IN_MIN) + OUT_MIN))


int main()
{
    // a = 5(00000101), b = 9(00001001)
    unsigned char a = 5, b = 9;
  
    // The result is 00000001
    printf("a = %d, b = %d\n", a, b);
    printf("a&b = %d\n", a & b);
  
    // The result is 00001101
    printf("a|b = %d\n", a | b);
  
    // The result is 00001100
    printf("a^b = %d\n", a ^ b);
  
    // The result is 11111010
    printf("~a = %d\n", a = ~a);
  
    // The result is 00010010
    printf("b<<1 = %d\n", b << 1);
  
    // The result is 00000100
    printf("b>>1 = %d\n", b >> 1);
  
    return 0;
    
}