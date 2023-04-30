/* *****************************************************************************
   This file try to implement a type that storages 64 bit of memory and their
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
#ifndef BIT64_H
#define BIT64_H 1

#include "fwcdt.h"

/* Try to implement a type with exact 64 bits. */
#if (ULONG_MAX == 0xffffffffffffffff)
   typedef unsigned long int bit64_t;
   #define BIT64_C(hex1, hex0) 0x ## hex1 ## hex0 ## UL
   #define FWCDT_BIT64_ARRAY_SIZE 1
#elif (ULLONG_MAX == 0xffffffffffffffff)
   typedef unsigned long long int bit64_t;
   #define BIT64_C(hex1, hex0) 0x ## hex1 ## hex0 ## ULL
   #define FWCDT_BIT64_ARRAY_SIZE 1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
# include <stdint.h> /* Defines exact-width integer types. */
# if defined(UINT64_C)
   typedef uint64_t bit64_t;
   #define BIT64_C(hex1, hex0) UINT64_C(0x ## hex1 ## hex0)
   #define FWCDT_BIT64_ARRAY_SIZE 1
# elif __STDC_VERSION__ >= 202311L
   typedef unsigned _BitInt(64) bit64_t;
   #define BIT64_C(hex1, hex0) ((unsigned _BitInt(64))(0x ## hex1 ## hex0))
   #define FWCDT_BIT64_ARRAY_SIZE 1
# endif
#else
# include "bit32.h"
# if defined(FWCDT_BIT32_ARRAY_SIZE)
#  if (FWCDT_BIT32_ARRAY_SIZE == 1)
   typedef struct { bit32_t m_BitField[2]; } bit64_t;
   #define BIT64_C(hex1, hex0) ((bit64_t){ .m_BitField = {\
      BIT32_C(hex0),\
      BIT32_C(hex1)\
   }})
   #define FWCDT_BIT64_ARRAY_SIZE 2
#  elif (FWCDT_BIT32_ARRAY_SIZE == 2)
   typedef struct { bit16_t m_BitField[4]; } bit64_t;
   #define BIT64_C(hex1, hex0) ((bit64_t){ .m_BitField = {\
      (bit16_t)(0x ## hex0),\
      (bit16_t)(0x ## hex0 >> 16U),\
      (bit16_t)(0x ## hex1 >> 32U),\
      (bit16_t)(0x ## hex1 >> 48U)\
   }})
   #define FWCDT_BIT64_ARRAY_SIZE 4
#  elif (FWCDT_BIT32_ARRAY_SIZE == 4)
   typedef struct { bit32_t m_BitField[2]; } bit64_t;
   #define BIT64_C(hex1, hex0) ((bit64_t){ .m_BitField = {\
      BIT32_C(hex0),\
      BIT32_C(hex1)\
   }})
   #define FWCDT_BIT64_ARRAY_SIZE 8
#  endif /* FWCDT_BIT32_ARRAY_SIZE */
# endif /* FWCDT_BIT32_ARRAY_SIZE */
#endif /* UINT_MAX */


#if defined(FWCDT_BIT64_ARRAY_SIZE)
# define BIT64_ZERO BIT64_C(00000000, 00000000)
#if (FWCDT_BIT64_ARRAY_SIZE == 1)
# define bit64_and(bits, mask)    __bitN_and_ONE(bits, mask, 64)
# define bit64_or(bits, mask)     __bitN_or_ONE(bits, mask, 64)
# define bit64_xor(bits, mask)    __bitN_xor_ONE(bits, mask, 64)
# define bit64_not(bits)          __bitN_not_ONE(bits, 64)
# define bit64_Lshift(bits, mask) __bitN_Lshift_ONE(bits, mask, 64)
# define bit64_Rshift(bits, mask) __bitN_Rshift_ONE(bits, mask, 64)
# define bit64_isequal(a, b)      __bitN_isequal_ONE(a, b)
#elif (FWCDT_BIT64_ARRAY_SIZE == 2)
# define bit64_and(bits, mask)    __bitN_and_TWO(bits, mask, 64, 32)
# define bit64_or(bits, mask)     __bitN_or_TWO(bits, mask, 64, 32)
# define bit64_xor(bits, mask)    __bitN_xor_TWO(bits, mask, 64, 32)
# define bit64_not(bits)          __bitN_not_TWO(bits, 64, 32)
# define bit64_Lshift(bits, mask) __bitN_Lshift_TWO(bits, mask, 64, 32)
# define bit64_Rshift(bits, mask) __bitN_Rshift_TWO(bits, mask, 64, 32)
# define bit64_isequal(a, b)      __bitN_isequal_TWO(a, b, 32)
#elif (FWCDT_BIT64_ARRAY_SIZE == 4)
# define bit64_and(bits, mask)    __bitN_and_FOUR(bits, mask, 64, 16)
# define bit64_or(bits, mask)     __bitN_or_FOUR(bits, mask, 64, 16)
# define bit64_xor(bits, mask)    __bitN_xor_FOUR(bits, mask, 64, 16)
# define bit64_not(bits)          __bitN_not_FOUR(bits, 64, 16)
# define bit64_Lshift(bits, mask) __bitN_Lshift_FOUR(bits, mask, 64, 32)
# define bit64_Rshift(bits, mask) __bitN_Rshift_FOUR(bits, mask, 64, 32)
# define bit64_isequal(a, b)      __bitN_isequal_FOUR(a, b, 16)
#endif /* FWCDT_BIT64_ARRAY_SIZE */
FWCDT_INLINE_FUNCTION(64)
#endif /* FWCDT_BIT64_ARRAY_SIZE */

#endif /* BIT64_H */
