#include <stdio.h>

struct X1 {
    int vi;
    float vf;
};

double foo(double a, int b);
double pack1(struct X1 *px, int n);

int main(void) {
    struct X1 v[3];

    v[0].vi = 1;
    v[0].vf = 2.0;

    v[1].vi = 2;
    v[1].vf = 3.0;

    v[2].vi = 3;
    v[2].vf = 4.0;

    double r = pack1(v, 3);

    printf("Resultado = %.2f\n", r);

    return 0;
}