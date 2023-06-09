/* *****************************************************************************
   This file try to implement a type that storages 32 bit of memory and their
   bitwise operators.

   Last modified: April 30, 2023
   *****************************************************************************
   E-mail: ismaellxd@gmail.com
   Site: https://ismaeldamiao.github.io/
   *****************************************************************************
   Copyright (c) 2023 I.F.F. dos SANTOS

   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the “Software”), to 
   deal in the Software without restriction, including without limitation the 
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
   sell copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
   IN THE SOFTWARE.
***************************************************************************** */
#ifndef BIT32_H
#define BIT32_H 1

#include "fwcdt.h"

/* Try to implement a type with exact 32 bits. */
#if (UINT_MAX == 0xffffffff)
   typedef unsigned int bit32_t;
   #define BIT32_C(hex) 0x ## hex ## U
   #define FWCDT_BIT32_ARRAY_SIZE 1
#elif (ULONG_MAX == 0xffffffff)
   typedef unsigned long int bit32_t;
   #define BIT32_C(hex) 0x ## hex ## UL
   #define FWCDT_BIT32_ARRAY_SIZE 1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
# include <stdint.h> /* Defines exact-width integer types. */
# if defined(UINT32_C)
   typedef uint32_t bit32_t;
   #define BIT32_C(hex) UINT32_C(0x ## hex)
   #define FWCDT_BIT32_ARRAY_SIZE 1
# elif (__STDC_VERSION__ >= 202311L)
   typedef unsigned _BitInt(32) bit32_t;
   #define BIT32_C(hex) ((unsigned _BitInt(32))(0x ## hex))
   #define FWCDT_BIT32_ARRAY_SIZE 1
# endif
#else
# include "bit16.h"
# if defined(FWCDT_BIT16_ARRAY_SIZE)
#  if (FWCDT_BIT16_ARRAY_SIZE == 1)
   typedef struct { bit16_t m_BitField[2]; } bit32_t;
   #define BIT32_C(hex) ((bit32_t){ .m_BitField = {\
      (bit16_t)(0x ## hex),\
      (bit16_t)(0x ## hex >> 16U)\
   }})
   #define FWCDT_BIT32_ARRAY_SIZE 2
#  elif (FWCDT_BIT16_ARRAY_SIZE == 2)
   typedef struct { bit8_t m_BitField[4]; } bit32_t;
   #define BIT32_C(hex) ((bit32_t){ .m_BitField = {\
      (bit8_t)(0x ## hex),\
      (bit8_t)(0x ## hex >> 8U),\
      (bit8_t)(0x ## hex >> 16U),\
      (bit8_t)(0x ## hex >> 24U)\
   }})
   #define FWCDT_BIT32_ARRAY_SIZE 4
#  endif /* FWCDT_BIT16_ARRAY_SIZE */
# endif /* FWCDT_BIT16_ARRAY_SIZE */
#endif /* UINT_MAX */


#if defined(FWCDT_BIT32_ARRAY_SIZE)
# define BIT32_ZERO BIT32_C(00000000)
#if (FWCDT_BIT32_ARRAY_SIZE == 1)
# define bit32_and(bits, mask)    __bitN_and_ONE(bits, mask, 32)
# define bit32_or(bits, mask)     __bitN_or_ONE(bits, mask, 32)
# define bit32_xor(bits, mask)    __bitN_xor_ONE(bits, mask, 32)
# define bit32_not(bits)          __bitN_not_ONE(bits, 32)
# define bit32_Lshift(bits, mask) __bitN_Lshift_ONE(bits, mask, 32)
# define bit32_Rshift(bits, mask) __bitN_Rshift_ONE(bits, mask, 32)
# define bit32_isequal(a, b)      __bitN_isequal_ONE(a, b)
#elif (FWCDT_BIT32_ARRAY_SIZE == 2)
# define bit32_and(bits, mask)    __bitN_and_TWO(bits, mask, 32, 16)
# define bit32_or(bits, mask)     __bitN_or_TWO(bits, mask, 32, 16)
# define bit32_xor(bits, mask)    __bitN_xor_TWO(bits, mask, 32, 16)
# define bit32_not(bits)          __bitN_not_TWO(bits, 32, 16)
# define bit32_Lshift(bits, mask) __bitN_Lshift_TWO(bits, mask, 32, 16)
# define bit32_Rshift(bits, mask) __bitN_Rshift_TWO(bits, mask, 32, 16)
# define bit32_isequal(a, b)      __bitN_isequal_TWO(a, b, 32)
#elif (FWCDT_BIT32_ARRAY_SIZE == 4)
# define bit32_and(bits, mask)    __bitN_and_FOUR(bits, mask, 32, 8)
# define bit32_or(bits, mask)     __bitN_or_FOUR(bits, mask, 32, 8)
# define bit32_xor(bits, mask)    __bitN_xor_FOUR(bits, mask, 32, 8)
# define bit32_not(bits)          __bitN_not_FOUR(bits, 32, 8)
# define bit32_Lshift(bits, mask) __bitN_Lshift_FOUR(bits, mask, 32, 16)
# define bit32_Rshift(bits, mask) __bitN_Rshift_FOUR(bits, mask, 32, 16)
# define bit32_isequal(a, b)      __bitN_isequal_FOUR(a, b, 8)
#endif /* FWCDT_BIT16_ARRAY_SIZE */
FWCDT_INLINE_FUNCTION(32)
#endif /* FWCDT_BIT16_ARRAY_SIZE */

#endif /* BIT32_H */
