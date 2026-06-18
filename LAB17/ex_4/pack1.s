/*

struct X1 {
  int vi;
  float vf;
};

double pack1 (struct X1 *px, int n) {
  double acc = 0;
  int i;
  for (i=0;i<n;i++)
    acc += foo(px[i].vf, px[i].vi);
  return acc;
}

*/

.text
.globl pack1
pack1:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)

    movq %rdi, %rbx
    movl %esi, %r12d
    movl $0, %r13d              /* int i = 0 */
    movq $0, -32(%rbp)          /* double acc = 0 */

for_loop:
    cmpl %r12d, %r13d
    jge fim

    movq %r13, %r8
    imulq $8, %r8
    addq %rbx, %r8

    movss 4(%r8), %xmm0        /* px[i].vf */
    cvtss2sd %xmm0, %xmm0
    movl 0(%r8), %edi          /* px[i].vi */
    call foo

    movsd -32(%rbp), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, -32(%rbp)

    addl $1, %r13d
    jmp for_loop

fim:
    movsd -32(%rbp), %xmm0
    movq -24(%rbp), %r13
    movq -16(%rbp), %r12
    movq -8(%rbp), %rbx
    leave
    ret