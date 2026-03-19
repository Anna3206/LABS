#include <stdio.h>

unsigned char rotate_left(unsigned char x, int n) {

    return (x << n) | (x >> (8 - n));

}

int main() {

    unsigned char x = 0x61;

    printf("x = 0x%X\n", x);
    printf("rotate_left(x,1) = 0x%X\n", rotate_left(x,1));
    printf("rotate_left(x,2) = 0x%X\n", rotate_left(x,2));
    printf("rotate_left(x,7) = 0x%X\n", rotate_left(x,7));

    return 0;
}