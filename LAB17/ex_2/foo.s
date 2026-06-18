/*

double foo (double a, int b) {
  return a * (-b);
}

*/

.text
.globl foo
foo:
    movl $0, %esi
    subl %edi, %esi         /* -b */

    cvtsi2sd %esi, %xmm1
    mulsd %xmm1, %xmm0

    ret
