/* Anna Clara Luna 2410494 3WC */
/* Jean Michel 2410531 3WA */

#include "cria_func.h"

/* Insere uma sequência de bytes no vetor codigo[] */
void insere(unsigned char codigo[], int *pos, unsigned char bytes[], int n) {
    for (int i = 0; i < n; i++) {
        codigo[(*pos)++] = bytes[i];
    }
}

/* Insere um inteiro (4 bytes) em codigo[] e incrementa a posição */
void insere_int(unsigned char codigo[], int *pos, int val) {
    *((int *)(codigo + *pos)) = val;
    *pos += 4;
}

/* Insere um ponteiro (8 bytes) em codigo[] e incrementa a posição */
void insere_ptr(unsigned char codigo[], int *pos, void *ptr) {
    *((void **)(codigo + *pos)) = ptr;
    *pos += 8;
}

void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]) {
    int pos = 0;
    int param_recebido = 0;

    /* PRÓLOGO: cria o registro de ativação e mantém a pilha alinhada */
    insere(codigo, &pos, (unsigned char[]){0x55}, 1);                 /* pushq %rbp */
    insere(codigo, &pos, (unsigned char[]){0x48, 0x89, 0xe5}, 3);     /* movq %rsp,%rbp */

    /*
     * Copia argumentos recebidos pela função nova:
     * PARAM #0 -> %r10
     * PARAM #1 -> %r11
     * PARAM #2 -> %rcx
     */

    insere(codigo, &pos, (unsigned char[]){0x49, 0x89, 0xfa}, 3); /* movq %rdi, %r10 */
    insere(codigo, &pos, (unsigned char[]){0x49, 0x89, 0xf3}, 3); /* movq %rsi, %r11 */
    insere(codigo, &pos, (unsigned char[]){0x48, 0x89, 0xd1}, 3); /* movq %rdx, %rcx */

    /* -------------------------------------------------------
     * Loop: coloca cada parâmetro no registrador correto
     * (%rdi = arg1, %rsi = arg2, %rdx = arg3)
     * ------------------------------------------------------- */
    for (int i = 0; i < n; i++) {

        if (params[i].orig_val == PARAM) {

            if (param_recebido == 0) {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0x4c, 0x89, 0xd7}, 3); /* movq %r10,%rdi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0x4c, 0x89, 0xd6}, 3); /* movq %r10,%rsi */
                else             insere(codigo, &pos, (unsigned char[]){0x4c, 0x89, 0xd2}, 3); /* movq %r10,%rdx */
            }

            else if (param_recebido == 1) {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0x4c, 0x89, 0xdf}, 3); /* movq %r11,%rdi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0x4c, 0x89, 0xde}, 3); /* movq %r11,%rsi */
                else             insere(codigo, &pos, (unsigned char[]){0x4c, 0x89, 0xda}, 3); /* movq %r11,%rdx */
            }

            else {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0x48, 0x89, 0xcf}, 3); /* movq %rcx,%rdi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0x48, 0x89, 0xce}, 3); /* movq %rcx,%rsi */
                else             insere(codigo, &pos, (unsigned char[]){0x48, 0x89, 0xca}, 3); /* movq %rcx,%rdx */
            }

            param_recebido++;
        }

        else if (params[i].orig_val == FIX) {

            if (params[i].tipo_val == INT_PAR) {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0xbf}, 1); /* movl $val,%edi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0xbe}, 1); /* movl $val,%esi */
                else             insere(codigo, &pos, (unsigned char[]){0xba}, 1); /* movl $val,%edx */

                insere_int(codigo, &pos, params[i].valor.v_int);
            }

            else {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0x48, 0xbf}, 2); /* movabsq $ptr,%rdi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0x48, 0xbe}, 2); /* movabsq $ptr,%rsi */
                else             insere(codigo, &pos, (unsigned char[]){0x48, 0xba}, 2); /* movabsq $ptr,%rdx */

                insere_ptr(codigo, &pos, params[i].valor.v_ptr);
            }
        }

        else { /* IND */

            insere(codigo, &pos, (unsigned char[]){0x48, 0xb8}, 2); /* movabsq $addr,%rax */
            insere_ptr(codigo, &pos, params[i].valor.v_ptr);

            if (params[i].tipo_val == INT_PAR) {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0x8b, 0x38}, 2); /* movl (%rax),%edi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0x8b, 0x30}, 2); /* movl (%rax),%esi */
                else             insere(codigo, &pos, (unsigned char[]){0x8b, 0x10}, 2); /* movl (%rax),%edx */
            }

            else {
                if (i == 0)      insere(codigo, &pos, (unsigned char[]){0x48, 0x8b, 0x38}, 3); /* movq (%rax),%rdi */
                else if (i == 1) insere(codigo, &pos, (unsigned char[]){0x48, 0x8b, 0x30}, 3); /* movq (%rax),%rsi */
                else             insere(codigo, &pos, (unsigned char[]){0x48, 0x8b, 0x10}, 3); /* movq (%rax),%rdx */
            }
        }
    }

    /* Chama a função original f por chamada indireta */
    insere(codigo, &pos, (unsigned char[]){0x48, 0xb8}, 2); /* movabsq $f,%rax */
    insere_ptr(codigo, &pos, f);
    insere(codigo, &pos, (unsigned char[]){0xff, 0xd0}, 2); /* call *%rax */

    /* EPÍLOGO */
    insere(codigo, &pos, (unsigned char[]){0xc9}, 1); /* leave */
    insere(codigo, &pos, (unsigned char[]){0xc3}, 1); /* ret */
}
