/* *****************************************************************************
   This file try to implement a type that storages 8 bit of memory and their
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
#ifndef BIT8_H
#define BIT8_H 1

#include "fwcdt.h"

#if (CHAR_BIT == 8)
   typedef unsigned char bit8_t;
   #define BIT8_C(hex) ((unsigned char)(0x ## hex))
   #define FWCDT_BIT8_ARRAY_SIZE 1
#else
# if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#  include <stdint.h> /* Defines exact-width integer types. */
#  if defined(UINT8_C)
   typedef uint8_t bit8_t;
   #define BIT8_C(hex) UINT8_C(0x ## hex)
   #define FWCDT_BIT8_ARRAY_SIZE 1
#  elif __STDC_VERSION__ >= 202311L
   typedef unsigned _BitInt(8) bit8_t;
   #define BIT8_C(hex) ((unsigned _BitInt(8))(0x ## hex))
   #define FWCDT_BIT8_ARRAY_SIZE 1
#  endif /* UINT8_C */
# endif /* __STDC_VERSION__ */
#endif /* CHAR_BIT */


#if defined(FWCDT_BIT8_ARRAY_SIZE) && (FWCDT_BIT8_ARRAY_SIZE == 1)
# define BIT8_ZERO BIT8_C(00)
# define bit8_and(bits, mask)    __bitN_and_ONE(bits, mask, 8)
# define bit8_or(bits, mask)     __bitN_or_ONE(bits, mask, 8)
# define bit8_xor(bits, mask)    __bitN_xor_ONE(bits, mask, 8)
# define bit8_not(bits)          __bitN_not_ONE(bits, 8)
# define bit8_Lshift(bits, mask) __bitN_Lshift_ONE(bits, mask, 8)
# define bit8_Rshift(bits, mask) __bitN_Rshift_ONE(bits, mask, 8)
# define bit8_isequal(a, b)      __bitN_isequal_ONE(a, b)
FWCDT_INLINE_FUNCTION(8)
#else
# error "Isn't possible to define a type with 8 bits."
#endif /* FWCDT_BIT8_ARRAY_SIZE */

#endif /* BIT8_H */
