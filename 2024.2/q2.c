#include <stdio.h>

int foo(short *v, int n, long filtro);

float passa_alta(short *v, int limite) {
    return (*v) + limite;
}

int main(void) {
    short v[] = {2, 5, 10, 20, 1};
    int n = 5;
    long filtro = 6;

    int r = foo(v, n, filtro);

    printf("Resultado: %d\n", r);

    return 0;
}