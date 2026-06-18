/*

struct X {                     
  int vi;
  double vd;
  struct X *next;
};

double pack (struct X *px) {
  double acc = 0;
  while (px != NULL) {
    acc += foo(px->vd, px->vi); 
    px = px->next;
  }
  return acc;
}

*/

.text
.globl pack
pack:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rbx, -8(%rbp)

    movq %rdi, %rbx
    movq $0, -16(%rbp)          /* acc = 0 */

while_loop:
    cmpq $0, %rbx
    je fim

    movsd 8(%rbx), %xmm0
    movl 0(%rbx), %edi
    call foo

    movsd -16(%rbp), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, -16(%rbp)

    movq 16(%rbx), %rbx
    jmp while_loop

fim:
    movsd -16(%rbp), %xmm0
    movq -8(%rbp), %rbx
    leave
    ret