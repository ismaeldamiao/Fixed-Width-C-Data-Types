/* *****************************************************************************
   This file try to implement a type that storages 16 bit of memory and their
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
