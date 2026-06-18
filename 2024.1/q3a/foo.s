/*

void foo (double *vd, int n) {
    while (n--) {
        *vd = 0.0;
        vd++;
    }
}

*/

.text
.globl foo
foo:

while_loop:

    cmpl $0, %esi
    je fim

    movq $0, (%rdi)
    addq $8, %rdi

    subl $1, %esi

    jmp while_loop

fim:
    ret