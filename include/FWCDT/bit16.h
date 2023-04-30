#ifndef BIT16_H
#define BIT16_H 1

#include "fwcdt.h"


/* Try to implement a type with exact 16 bits. */
#if (UINT_MAX == 0xffff)
   typedef unsigned int bit16_t;
   #define BIT16_C(hex) 0x ## hex ## U
   #define FWCDT_BIT16_ARRAY_SIZE 1
#elif (USHRT_MAX == 0xffff)
   typedef unsigned short int bit16_t;
   #define BIT16_C(hex) ((unsigned short int)(0x ## hex))
   #define FWCDT_BIT16_ARRAY_SIZE 1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
# include <stdint.h> /* Defines exact-width integer types. */
# if defined(UINT16_C)
   typedef uint16_t bit16_t;
   #define BIT16_C(hex) UINT16_C(0x ## hex)
   #define FWCDT_BIT16_ARRAY_SIZE 1
# elif __STDC_VERSION__ >= 202311L
   typedef unsigned _BitInt(16) bit16_t;
   #define BIT16_C(hex) ((unsigned _BitInt(16))(0x ## hex))
   #define FWCDT_BIT16_ARRAY_SIZE 1
# endif
#else
# include "bit8.h"
# if defined(FWCDT_BIT8_ARRAY_SIZE) && (FWCDT_BIT8_ARRAY_SIZE == 1)
   typedef struct { bit8_t m_BitField[2]; } bit16_t;
   #define BIT16_C(hex) ((bit16_t){ .m_BitField = {\
      (bit8_t)(0x ## hex),\
      (bit8_t)(0x ## hex >> 8U)\
   }})
   #define FWCDT_BIT16_ARRAY_SIZE 2
# endif /* FWCDT_BIT8_ARRAY_SIZE */
#endif /* UINT_MAX */


#if defined(FWCDT_BIT16_ARRAY_SIZE)
# define BIT16_ZERO BIT16_C(0000)
#if (FWCDT_BIT16_ARRAY_SIZE == 1)
# define bit16_and(bits, mask)    __bitN_and_ONE(bits, mask, 16)
# define bit16_or(bits, mask)     __bitN_or_ONE(bits, mask, 16)
# define bit16_xor(bits, mask)    __bitN_xor_ONE(bits, mask, 16)
# define bit16_not(bits)          __bitN_not_ONE(bits, 16)
# define bit16_Lshift(bits, mask) __bitN_Lshift_ONE(bits, mask, 16)
# define bit16_Rshift(bits, mask) __bitN_Rshift_ONE(bits, mask, 16)
# define bit16_isequal(a, b)      __bitN_isequal_ONE(a, b)
#elif (FWCDT_BIT16_ARRAY_SIZE == 2)
# define bit16_and(bits, mask)    __bitN_and_TWO(bits, mask, 16, 8)
# define bit16_or(bits, mask)     __bitN_or_TWO(bits, mask, 16, 8)
# define bit16_xor(bits, mask)    __bitN_xor_TWO(bits, mask, 16, 8)
# define bit16_not(bits)          __bitN_not_TWO(bits, 16, 8)
# define bit16_Lshift(bits, mask) __bitN_Lshift_TWO(bits, mask, 16, 8)
# define bit16_Rshift(bits, mask) __bitN_Rshift_TWO(bits, mask, 16, 8)
# define bit16_isequal(a, b)      __bitN_isequal_TWO(a, b, 8)
#endif /* FWCDT_BIT16_ARRAY_SIZE */

FWCDT_INLINE_FUNCTION(16)

#endif /* FWCDT_BIT16_ARRAY_SIZE */


#endif /* BIT16_H */
