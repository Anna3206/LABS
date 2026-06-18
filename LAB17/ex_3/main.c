#include <stdio.h>

struct X {
    int vi;
    double vd;
    struct X *next;
};

double foo(double a, int b);
double pack(struct X *px);

int main(void) {
    struct X x3 = {3, 4.0, NULL};
    struct X x2 = {2, 3.0, &x3};
    struct X x1 = {1, 2.0, &x2};

    double r = pack(&x1);

    printf("Resultado: %.2f\n", r);

    return 0;
}