/*

float passa_alta(short *v, int limite);

int foo(short *v, int n, long filtro) {
    int i;
    double soma = 0;
    for(i=0; i<n; i++) {
        if(v[i] > filtro) {
            soma += passa_alta(v[i], 3);
        }
    }
    return soma;
}

*/

.text
.globl foo
foo: 
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    movq %r14, -32(%rbp)

    movl $0, %ebx                   /* int i = 0 */
    movq %rdi, %r12                 /* 1º parâmetro v em %r12 */    
    movl %esi, %r13d                /* 2º parâmetro (n) em %r13d */
    movq %rdx, %r14                 /* 3º parâmetro (filtro) em %r14 */
    movq $0, -40(%rbp)              /* double soma = 0 */

for_loop:
    cmpl %r13d, %ebx
    jge fim

    movq %rbx, %rdi
    imulq $2, %rdi
    addq %r12, %rdi
    
    movswq (%rdi), %r8
    cmpq %r14, %r8
    jle cond

    movl $3, %esi
    call passa_alta
    cvtss2sd %xmm0, %xmm0
    addsd -40(%rbp), %xmm0
    movsd %xmm0, -40(%rbp) 

cond:

    addl $1, %ebx                   /* i++ */
    jmp for_loop

fim:
    cvttsd2si -40(%rbp), %eax
    movq -32(%rbp), %r14
    movq -24(%rbp), %r13
    movq -16(%rbp), %r12
    movq -8(%rbp), %rbx
    leave
    ret
