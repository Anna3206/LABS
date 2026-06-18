#include <stdio.h>

double foo (double a, int b);

int main(void){
    double a = -2.5;
    int b = 5;

    double c = foo(a, b);
    printf("Resultado: %.2f\n", c);

    return 0;
}