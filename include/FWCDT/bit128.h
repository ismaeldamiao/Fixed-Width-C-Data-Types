/* *****************************************************************************
   This file try to implement a type that storages 128 bit of memory and their
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
#ifndef BIT128_H
#define BIT128_H 1

#include "fwcdt.h"

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202000L)
   typedef unsigned _BitInt(128) bit128_t;
   /*#define BIT128_C(hex3, hex2, hex1, hex0) \
   ((bit128_t)(0x ## hex3 ## hex2 ## hex1 ## hex0 ## UWB))*/
   #define BIT128_C(hex3, hex2, hex1, hex0) (\
      ((union { bit128_t m_bitN; unsigned _BitInt(64) m_bitN2[2]; }){\
         .m_bitN2 = {0x ## hex3 ## hex2, 0x ## hex1 ## hex0 }\
      }).m_bitN\
   )
   #define FWCDT_BIT128_ARRAY_SIZE 1
#else
# include "bit64.h"
# if defined(FWCDT_BIT64_ARRAY_SIZE)
#  if (FWCDT_BIT64_ARRAY_SIZE == 1)
   typedef struct { bit64_t m_BitField[2]; } bit128_t;
   #define BIT128_C(hex3, hex2, hex1, hex0) ((bit128_t){ .m_BitField = {\
      BIT64_C(hex1, hex0),\
      BIT64_C(hex3, hex2)\
   }})
   #define FWCDT_BIT128_ARRAY_SIZE 2
#  elif (FWCDT_BIT64_ARRAY_SIZE == 2)
   typedef struct { bit32_t m_BitField[4]; } bit128_t;
   #define BIT128_C(hex3, hex2, hex1, hex0) ((bit128_t){ .m_BitField = {\
      BIT32_C(hex0),\
      BIT32_C(hex1),\
      BIT32_C(hex2),\
      BIT32_C(hex3)\
   }})
   #define FWCDT_BIT128_ARRAY_SIZE 4
#  elif (FWCDT_BIT64_ARRAY_SIZE > 2)
   typedef struct { bit64_t m_BitField[2]; } bit128_t;
   #define BIT128_C(hex3, hex2, hex1, hex0) ((bit128_t){ .m_BitField = {\
      BIT64_C(hex1, hex0),\
      BIT64_C(hex3, hex2)\
   }})
   #define FWCDT_BIT128_ARRAY_SIZE (FWCDT_BIT64_ARRAY_SIZE*2)
#  endif /* FWCDT_BIT64_ARRAY_SIZE */
# endif /* FWCDT_BIT64_ARRAY_SIZE */
#endif /* __STDC_VERSION__ */

#if defined(FWCDT_BIT128_ARRAY_SIZE)
# define BIT128_ZERO BIT128_C(00000000, 00000000, 00000000, 00000000)
#if (FWCDT_BIT128_ARRAY_SIZE == 1)
# define bit128_and(bits, mask)    __bitN_and_ONE(bits, mask, 128)
# define bit128_or(bits, mask)     __bitN_or_ONE(bits, mask, 128)
# define bit128_xor(bits, mask)    __bitN_xor_ONE(bits, mask, 128)
# define bit128_not(bits)          __bitN_not_ONE(bits, 128)
# define bit128_Lshift(bits, mask) __bitN_Lshift_ONE(bits, mask, 128)
# define bit128_Rshift(bits, mask) __bitN_Rshift_ONE(bits, mask, 128)
# define bit128_isequal(a, b)      __bitN_isequal_ONE(a, b)
#elif (FWCDT_BIT128_ARRAY_SIZE == 2)
# define bit128_and(bits, mask)    __bitN_and_TWO(bits, mask, 128, 64)
# define bit128_or(bits, mask)     __bitN_or_TWO(bits, mask, 128, 64)
# define bit128_xor(bits, mask)    __bitN_xor_TWO(bits, mask, 128, 64)
# define bit128_not(bits)          __bitN_not_TWO(bits, 128, 64)
# define bit128_Lshift(bits, mask) __bitN_Lshift_TWO(bits, mask, 128, 64)
# define bit128_Rshift(bits, mask) __bitN_Rshift_TWO(bits, mask, 128, 64)
# define bit128_isequal(a, b)      __bitN_isequal_TWO(a, b, 64)
#elif (FWCDT_BIT128_ARRAY_SIZE == 4)
# define bit128_and(bits, mask)    __bitN_and_FOUR(bits, mask, 128, 32)
# define bit128_or(bits, mask)     __bitN_or_FOUR(bits, mask, 128, 32)
# define bit128_xor(bits, mask)    __bitN_xor_FOUR(bits, mask, 128, 32)
# define bit128_not(bits)          __bitN_not_FOUR(bits, 128, 32)
# define bit128_Lshift(bits, mask) __bitN_Lshift_FOUR(bits, mask, 128, 64)
# define bit128_Rshift(bits, mask) __bitN_Rshift_FOUR(bits, mask, 128, 64)
# define bit128_isequal(a, b)      __bitN_isequal_FOUR(a, b, 32)
#endif /* FWCDT_BIT64_ARRAY_SIZE */
FWCDT_INLINE_FUNCTION(128)
#endif /* FWCDT_BIT64_ARRAY_SIZE */

#endif /* BIT128_H */
