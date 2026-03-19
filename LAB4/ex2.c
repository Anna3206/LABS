#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

/*short -32765 = 0111 1111 1111 1101 (~)-> 1000 0000 0000 0010 (+1)-> 1000 0000 0000 0011 -> 0x03 0x80 (2 bytes)*/
/*unsigned short 32771 = 1000 0000 0000 0011 -> 0x03 0x80 (2 bytes)*/

int main (void) {
  short l = -32765;
  unsigned short k = 32771;
  printf("l=%d, k=%u \n", l, k);
  printf("dump de l: \n");
  dump(&l, sizeof(l));
  printf("dump de k: \n");
  dump(&k, sizeof(k));
  return 0;
}