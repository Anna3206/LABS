#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

/*char 150: 150 > 127 (não consta na tabela ASCII); 1001 0110 -> 0x96 (1 byte)*/
/*short -3 = 0000 0011 (~)-> 1111 1100 (+1)-> 1111 1101 -> 0xFD 0xFF (2 bytes)*/
/*int -151 = 1001 0111 (~)-> 0110 1000 (+1)-> 0110 1001 -> 0x69 0xFF 0xFF 0xFF (4 bytes)*/


int main (void) {
  char c = 150;
  short s = -3;
  int i = -151;
  printf("dump de c: \n");
  dump(&c, sizeof(c));
  printf("dump de s: \n");
  dump(&s, sizeof(s));
  printf("dump de i: \n");
  dump(&i, sizeof(i));
  return 0;
}