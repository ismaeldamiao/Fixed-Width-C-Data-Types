/*
   EXPAND:
      cc -E -P main.c
      cc -std=c89 -E -P main.c
      clang -std=c89 -m32 -E -P main.c
      clang -std=c2x -E -P main.c
   COMPILE (one of):
      cc main.c -o main
      cc -std=c89 main.c
      clang -std=c89 -m32 main.c -o main
      clang -std=c2x main.c -o main
   EXECUTE:
   ./main
*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/fwcdt.h"


int main(void){

   {
      bit8_t var[2];
      var[1] = BIT8_C(0b);
      if(bit8_isequal(var[0], var[1])) puts("Here 1.");
      if((bit8_isequal)(var[0], var[1])) puts("Here 2.");
   }

   {
      bit16_t var;
      var = BIT16_C(0fe7);
      if(!(bit16_isequal)(bit16_Lshift(var, 2U), (bit16_Lshift)(var, 2U)))
      puts("Here 3.");
   }

   {
      bit32_t var;
      var = BIT32_C(0fe74c57);
      if(!(bit32_isequal)(bit32_Rshift(var, 19U), (bit32_Rshift)(var, 19U)))
      puts("Here 4.");
   }

   {
      bit64_t var;
      var = BIT64_C(59fe4ac8, 8456bcde);
      if(!(bit64_isequal)(bit64_Rshift(var, 19U), (bit64_Rshift)(var, 19U)))
      puts("Here 5.");
   }

   {
      bit128_t var;
      var = BIT128_C(16584324, 59fe4ac8, 8456bcde, 651826ec);
      if(!(bit128_isequal)(bit128_Rshift(var, 19U), (bit128_Rshift)(var, 19U)))
      puts("Here 6.");
   }

   return EXIT_SUCCESS;
}
