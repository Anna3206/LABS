/*

struct exam { float val; int tipo; };
double inv (double val);
float boo (double d, float bias) {
    int i;
    struct exam temp[5];
    for (i=0; i<5; i++) {
        temp[i].val = inv(d);
        temp[i].tipo = i;
    }
    return temp[0].val + bias;
}

*/

.text
.globl boo
boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movsd %xmm0, -24(%rbp)
    movss %xmm1, -28(%rbp)

    leaq  -72(%rbp), %r12       /* r12 = &temp[0] */

    movl $0, %ebx               /* i = 0 */

for_loop:
    cmpl $5, %ebx               /* i < 5? */
    jge fim

    movsd -24(%rbp), %xmm0
    call inv

    movq %rbx, %r8             
    imulq $8, %r8             
    addq %r12, %r8
    cvtsd2ss %xmm0, %xmm0
    movss %xmm0, 0(%r8)         /* temp[i].val = inv(d) */
    movl %ebx, 4(%r8)          /* temp[i].tipo = i */

    addl $1, %ebx               /* i++ */
    jmp for_loop

fim:
    movss (%r12), %xmm0     
    addss -28(%rbp), %xmm0      /* temp[0].val + bias */

    movq -16(%rbp), %r12
    movq -8(%rbp), %rbx
    leave
    ret