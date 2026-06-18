.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp

    movl $10, %edi
    movl $20, %esi
    movl $30, %edx

    movq %rdi, %rsi
    movq %rdi, %rdx
    movq %rsi, %rdi
    movq %rdx, %rdi
    movq %rdx, %rsi

    movabsq $0x1122334455667788, %rax

    call *%rax

    leave
    ret