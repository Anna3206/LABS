#include <stdio.h>

void foo(double *vd, int n);

int main(void) {
    double v[] = {1.5, 2.5, 3.5, 4.5};
    int n = 4;

    foo(v, n);

    for (int i = 0; i < n; i++) {
        printf("v[%d] = %.1f\n", i, v[i]);
    }

    return 0;
}