#ifndef FWCDT_HELPER_H
#define FWCDT_HELPER_H 1

#if !defined(__STDC__)
# error "Use only ISO C89 or later."
#endif /* __STDC__ */

#include <limits.h>

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
# include <stdint.h> /* Defines exact-width integer types. */
#else
# define inline
#endif /* __STDC_VERSION__ */

#define __bitN_and_ONE(bits, mask, N)    ((bit ## N ## _t)((bits) & (mask)))
#define __bitN_or_ONE(bits, mask, N)     ((bit ## N ## _t)((bits) | (mask)))
#define __bitN_xor_ONE(bits, mask, N)    ((bit ## N ## _t)((bits) ^ (mask)))
#define __bitN_not_ONE(bits, N)          ((bit ## N ## _t)(~(bits)))
#define __bitN_Lshift_ONE(bits, mask, N) ((bit ## N ## _t)((bits) << (mask)))
#define __bitN_Rshift_ONE(bits, mask, N) ((bit ## N ## _t)((bits) >> (mask)))
#define __bitN_isequal_ONE(a, b)         ((a) == (b))

#define __bitN_and_TWO(bits, mask, N, N2) (\
   (bit ## N ## _t){ .m_BitField = {\
   bit ## N2 ## _and(bits.m_BitField[0], mask.m_BitField[0]), \
   bit ## N2 ## _and(bits.m_BitField[1], mask.m_BitField[1])}}\
)
#define __bitN_or_TWO(bits, mask, N, N2) (\
   (bit##N##_t){ .m_BitField = {\
   bit ## N2 ## _or(bits.m_BitField[0], mask.m_BitField[0]), \
   bit ## N2 ## _or(bits.m_BitField[1], mask.m_BitField[1])}}\
)
#define __bitN_xor_TWO(bits, mask, N, N2) (\
   (bit ## N ## _t){ .m_BitField = {\
   bit ## N2 ## _xor(bits.m_BitField[0], mask.m_BitField[0]), \
   bit ## N2 ## _xor(bits.m_BitField[1], mask.m_BitField[1])}}\
)
#define __bitN_not_TWO(bits, N, N2) (\
   (bit ## N ## _t){ .m_BitField = {\
   bit ## N2 ## _not(bits.m_BitField[0]),\
   bit ## N2 ## _not(bits.m_BitField[1])}}\
)
#define __bitN_Lshift_TWO(bits, mask, N, N2) (\
   (!(mask)) ? \
      (bits) : \
   ((((unsigned int)(mask)) >= N ## U) ? \
      BIT ## N ## _ZERO : (\
   (((unsigned int)(mask)) >= N2 ## U) ? \
      (bit ## N ## _t){ .m_BitField = {\
         bit ## N2 ## _Lshift(\
            bits.m_BitField[0],\
            (unsigned int)(mask) - N2 ## U\
         ),\
         BIT ## N2 ## _ZERO\
      }} : \
      (bit ## N ## _t){ .m_BitField = {\
         bit ## N2 ## _or(\
            bit ## N2 ## _Lshift(bits.m_BitField[1], mask), \
            bit ## N2 ## _Rshift(\
               bits.m_BitField[0],\
               N2 ## U - (unsigned int)(mask)\
            )\
         ),\
         bit ## N2 ## _Lshift(bits.m_BitField[0], mask)\
      }}\
   ))\
)
#define __bitN_Rshift_TWO(bits, mask, N, N2) (\
   (!(mask)) ? \
      (bits) : \
   ((((unsigned int)(mask)) >= N ## U) ? \
      BIT ## N ## _ZERO : (\
   (((unsigned int)(mask)) >= N2 ## U) ? \
      (bit ## N ## _t){ .m_BitField = {\
         BIT ## N2 ## _ZERO,\
         bit ## N2 ## _Rshift(\
            bits.m_BitField[1],\
            (unsigned int)(mask) - N2 ## U\
         )\
      }} : \
      (bit ## N ## _t){ .m_BitField = {\
         bit ## N2 ## _Rshift(bits.m_BitField[1], mask),\
         bit ## N2 ## _or(\
            bit ## N2 ## _Rshift(bits.m_BitField[0], mask), \
            bit ## N2 ## _Lshift(\
               bits.m_BitField[1],\
               N2 ## U - (unsigned int)(mask)\
            )),\
      }}\
   ))\
)
#define __bitN_isequal_TWO(a, b, N2) (\
   bit ## N2 ## _isequal(a.m_BitField[0], b.m_BitField[0]) && \
   bit ## N2 ## _isequal(a.m_BitField[1], b.m_BitField[1])\
)

#define __bitN_and_FOUR(bits, mask, N, N4) (\
   (bit ## N ## _t){ .m_BitField = {\
   bit ## N4 ## _and(bits.m_BitField[0], mask.m_BitField[0]), \
   bit ## N4 ## _and(bits.m_BitField[1], mask.m_BitField[1]), \
   bit ## N4 ## _and(bits.m_BitField[2], mask.m_BitField[2]), \
   bit ## N4 ## _and(bits.m_BitField[3], mask.m_BitField[3])}}\
)
#define __bitN_or_FOUR(bits, mask, N, N4) (\
   (bit##N##_t){ .m_BitField = {\
   bit ## N4 ## _or(bits.m_BitField[0], mask.m_BitField[0]), \
   bit ## N4 ## _or(bits.m_BitField[1], mask.m_BitField[1]), \
   bit ## N4 ## _or(bits.m_BitField[2], mask.m_BitField[2]), \
   bit ## N4 ## _or(bits.m_BitField[3], mask.m_BitField[3])}}\
)
#define __bitN_xor_FOUR(bits, mask, N, N4) (\
   (bit ## N ## _t){ .m_BitField = {\
   bit ## N4 ## _xor(bits.m_BitField[0], mask.m_BitField[0]), \
   bit ## N4 ## _xor(bits.m_BitField[1], mask.m_BitField[1]), \
   bit ## N4 ## _xor(bits.m_BitField[2], mask.m_BitField[2]), \
   bit ## N4 ## _xor(bits.m_BitField[3], mask.m_BitField[3])}}\
)
#define __bitN_not_FOUR(bits, N, N4) (\
   (bit ## N ## _t){ .m_BitField = {\
   bit ## N4 ## _not(bits.m_BitField[0]), \
   bit ## N4 ## _not(bits.m_BitField[1]), \
   bit ## N4 ## _not(bits.m_BitField[2]), \
   bit ## N4 ## _not(bits.m_BitField[3])}}\
)

#define __bitN_Lshift_FOUR(bits, mask, N, N2) (\
   (!(mask)) ? \
      (bits) : \
   ((((unsigned int)(mask)) >= N ## U) ? \
      BIT ## N ## _ZERO : (\
   (((unsigned int)(mask)) >= N2 ## U) ? \
      ((union { bit ## N ## _t m_bitN; bit ## N2 ## _t m_bitN2[2]; }){\
         .m_bitN2 = {\
            bit ## N2 ## _Lshift(\
               ((bit ## N2 ## _t){ bits.m_BitField[0], bits.m_BitField[1] }),\
               (unsigned int)(mask) - N2 ## U\
            ),\
            BIT ## N2 ## _ZERO\
         }\
      }).m_bitN : \
      ((union {bit ## N ## _t m_bitN; bit ## N2 ## _t m_bitN2[2]; }){\
         .m_bitN2 = {\
            bit ## N2 ## _or(\
               (bit ## N2 ## _Lshift)(\
                  ((bit ## N2 ## _t){bits.m_BitField[2], bits.m_BitField[3] }),\
                  mask\
               ), \
               bit ## N2 ## _Rshift(\
                  ((bit ## N2 ## _t){bits.m_BitField[0], bits.m_BitField[1] }),\
                  N2 ## U - (unsigned int)(mask)\
               )\
            ),\
            bit ## N2 ## _Lshift(\
               ((bit ## N2 ## _t){bits.m_BitField[0], bits.m_BitField[1] }),\
               mask\
            )\
         }\
      }).m_bitN\
   ))\
)
#define __bitN_Rshift_FOUR(bits, mask, N, N2) (\
   (!(mask)) ? \
      (bits) : \
   ((((unsigned int)(mask)) >= N ## U) ? \
      BIT ## N ## _ZERO : (\
   (((unsigned int)(mask)) >= N2 ## U) ? \
      ((union { bit ## N ## _t m_bitN; bit ## N2 ## _t m_bitN2[2]; }){\
         .m_bitN2 = {\
            BIT ## N2 ## _ZERO,\
            bit ## N2 ## _Rshift(\
               ((bit ## N2 ## _t){bits.m_BitField[2], bits.m_BitField[3]}),\
               (unsigned int)(mask) - N2 ## U\
            )\
         }\
      }).m_bitN : \
      ((union { bit ## N ## _t m_bitN; bit ## N2 ## _t m_bitN2[2]; }){\
         .m_bitN2 = {\
            bit ## N2 ## _Rshift(\
               ((bit ## N2 ## _t){bits.m_BitField[2], bits.m_BitField[3]}),\
               mask\
            ),\
            bit ## N2 ## _or(\
               bit ## N2 ## _Rshift(\
                  ((bit ## N2 ## _t){bits.m_BitField[0], bits.m_BitField[1] }),\
                  mask\
               ),\
               bit ## N2 ## _Lshift(\
                  ((bit ## N2 ## _t){bits.m_BitField[2], bits.m_BitField[3]}),\
                  N2 ## U - (unsigned int)(mask)\
               )\
            )\
         }\
      }).m_bitN\
   ))\
)
#define __bitN_isequal_FOUR(a, b, N4) (\
   bit ## N4 ## _isequal(a.m_BitField[0], b.m_BitField[0]) && \
   bit ## N4 ## _isequal(a.m_BitField[1], b.m_BitField[1]) && \
   bit ## N4 ## _isequal(a.m_BitField[2], b.m_BitField[2]) && \
   bit ## N4 ## _isequal(a.m_BitField[3], b.m_BitField[3])\
)


#define FWCDT_INLINE_FUNCTION(N) \
static inline bit ## N ## _t (bit ## N ## _and)\
(bit ## N ## _t bits, bit ## N ## _t mask){\
   return bit ## N ## _and(bits, mask);\
}\
static inline bit ## N ## _t (bit ## N ## _or)\
(bit ## N ## _t bits, bit ## N ## _t mask){\
   return bit ## N ## _or(bits, mask);\
}\
static inline bit ## N ## _t (bit ## N ## _xor)\
(bit ## N ## _t bits, bit ## N ## _t mask){\
   return bit ## N ## _xor(bits, mask);\
}\
static inline bit ## N ## _t (bit ## N ## _not)\
(bit ## N ## _t bits){\
   return bit ## N ## _not(bits);\
}\
static inline bit ## N ## _t (bit ## N ## _Lshift)\
(bit ## N ## _t bits, unsigned int mask){\
   return bit ## N ##_Lshift(bits, mask);\
}\
static inline bit ## N ## _t (bit ## N ## _Rshift)\
(bit ## N ##_t bits, unsigned int mask){\
   return bit ## N ## _Rshift(bits, mask);\
}\
static inline int (bit ## N ## _isequal)\
(bit ## N ## _t a, bit ## N ## _t b){\
   return (bit ## N ## _isequal(a, b) ? 1 : 0);\
}

#endif /* FWCDT_HELPER_H */
