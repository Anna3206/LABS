#include <stdio.h>

int odd_ones(unsigned int x) {
  int eh_par = 0;

    while (x) {
        eh_par ^= (x & 1);
        x >>= 1;        
    }

    return eh_par;
}
int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}