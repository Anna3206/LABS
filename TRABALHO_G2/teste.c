#include <stdio.h>
#include <string.h>
#include "cria_func.h"

/* ============================================================
 * Funcoes usadas nos testes
 * ============================================================ */

int mult(int x, int y) {
    return x * y;
}

int soma(int x, int y) {
    return x + y;
}

int identidade(int x) {
    return x;
}

int tres_args(int a, int b, int c) {
    return a + b * 10 + c * 100;
}

/* ============================================================
 * Infraestrutura de testes
 * ============================================================ */
static int testes_ok = 0;
static int testes_fail = 0;

void check_int(const char *desc, int resultado, int esperado) {
    if (resultado == esperado) {
        printf("  [OK]   %s => %d\n", desc, resultado);
        testes_ok++;
    } else {
        printf("  [FAIL] %s => %d (esperado %d)\n", desc, resultado, esperado);
        testes_fail++;
    }
}

/* Para resultados que so importa ser zero ou nao-zero */
void check_zero(const char *desc, int resultado, int deve_ser_zero) {
    int ok = deve_ser_zero ? (resultado == 0) : (resultado != 0);
    if (ok) {
        printf("  [OK]   %s => %d\n", desc, resultado);
        testes_ok++;
    } else {
        printf("  [FAIL] %s => %d (esperado %s)\n", desc, resultado,
               deve_ser_zero ? "0" : "!= 0");
        testes_fail++;
    }
}

/* ============================================================
 * Teste 1: mult(x, 10) — (INT) PARAM + (INT) FIX
 *
 * Cria f(x) = mult(x, 10)
 * Testes:    x = 1, 5, 10, -3
 * Resultados: 10, 50, 100, -30
 * ============================================================ */
void teste1(void) {
    printf("\n[Teste 1] mult(x, 10) — (INT) PARAM + (INT) FIX\n");
    typedef int (*fp)(int);
    DescParam p[2];
    unsigned char codigo[500];

    p[0].tipo_val = INT_PAR; p[0].orig_val = PARAM;
    p[1].tipo_val = INT_PAR; p[1].orig_val = FIX; p[1].valor.v_int = 10;

    cria_func(mult, p, 2, codigo);
    fp f = (fp)codigo;

    check_int("f(1)  = mult(1,  10) =  10", f(1),   10);
    check_int("f(5)  = mult(5,  10) =  50", f(5),   50);
    check_int("f(10) = mult(10, 10) = 100", f(10), 100);
    check_int("f(-3) = mult(-3, 10) = -30", f(-3), -30);
}

/* ============================================================
 * Teste 2: mult(2, 7) — (INT) FIX + (INT) FIX
 *
 * Cria f() sem parametros, sempre retorna 14
 * Resultado: 14
 * ============================================================ */
void teste2(void) {
    printf("\n[Teste 2] mult(2, 7) — (INT) FIX + (INT) FIX\n");
    typedef int (*fp)(void);
    DescParam p[2];
    unsigned char codigo[500];

    p[0].tipo_val = INT_PAR; p[0].orig_val = FIX; p[0].valor.v_int = 2;
    p[1].tipo_val = INT_PAR; p[1].orig_val = FIX; p[1].valor.v_int = 7;

    cria_func(mult, p, 2, codigo);
    fp f = (fp)codigo;

    check_int("f() = mult(2, 7) = 14", f(), 14);
}

/* ============================================================
 * Teste 3: mult(3, y) — (INT) FIX + (INT) PARAM
 *
 * Cria f(y) = mult(3, y)
 * Testes:    y = 4, 0, -5
 * Resultados: 12, 0, -15
 * ============================================================ */
void teste3(void) {
    printf("\n[Teste 3] mult(3, y) — (INT) FIX + (INT) PARAM\n");
    typedef int (*fp)(int);
    DescParam p[2];
    unsigned char codigo[500];

    p[0].tipo_val = INT_PAR; p[0].orig_val = FIX; p[0].valor.v_int = 3;
    p[1].tipo_val = INT_PAR; p[1].orig_val = PARAM;

    cria_func(mult, p, 2, codigo);
    fp f = (fp)codigo;

    check_int("f(4)  = mult(3,  4) =  12", f(4),   12);
    check_int("f(0)  = mult(3,  0) =   0", f(0),    0);
    check_int("f(-5) = mult(3, -5) = -15", f(-5), -15);
}

/* ============================================================
 * Teste 4: mult(i, 10) — (INT) IND + (INT) FIX
 *
 * Cria f() que le variavel i em tempo de execucao
 * Testes:    i = 1, 5, -3 (modificados entre chamadas)
 * Resultados: 10, 50, -30
 * ============================================================ */
void teste4(void) {
    printf("\n[Teste 4] mult(i, 10) — (INT) IND + (INT) FIX\n");
    typedef int (*fp)(void);
    DescParam p[2];
    unsigned char codigo[500];
    int i;

    p[0].tipo_val = INT_PAR; p[0].orig_val = IND; p[0].valor.v_ptr = &i;
    p[1].tipo_val = INT_PAR; p[1].orig_val = FIX; p[1].valor.v_int = 10;

    cria_func(mult, p, 2, codigo);
    fp f = (fp)codigo;

    i =  1; check_int("i= 1: f() = mult(1,  10) =  10", f(),  10);
    i =  5; check_int("i= 5: f() = mult(5,  10) =  50", f(),  50);
    i = -3; check_int("i=-3: f() = mult(-3, 10) = -30", f(), -30);
}

/* ============================================================
 * Teste 5: identidade(x) — (INT) PARAM
 *
 * Cria f(x) = x
 * Testes:    42, 0, -99
 * Resultados: 42, 0, -99
 * ============================================================ */
void teste5(void) {
    printf("\n[Teste 5] identidade(x) — (INT) PARAM\n");
    typedef int (*fp)(int);
    DescParam p[1];
    unsigned char codigo[500];

    p[0].tipo_val = INT_PAR; p[0].orig_val = PARAM;

    cria_func(identidade, p, 1, codigo);
    fp f = (fp)codigo;

    check_int("f(42)  = 42",  f(42),  42);
    check_int("f(0)   = 0",   f(0),    0);
    check_int("f(-99) = -99", f(-99), -99);
}

/* ============================================================
 * Teste 6: tres_args(1, b, 3) — (INT) FIX + (INT) PARAM + (INT) FIX
 *
 * tres_args(a,b,c) = a + b*10 + c*100
 * Cria f(b) = 1 + b*10 + 300 = 301 + b*10
 * Testes:    b = 0, 1, 5
 * Resultados: 301, 311, 351
 * ============================================================ */
void teste6(void) {
    printf("\n[Teste 6] tres_args(1, b, 3) — (INT) FIX + (INT) PARAM + (INT) FIX\n");
    typedef int (*fp)(int);
    DescParam p[3];
    unsigned char codigo[500];

    p[0].tipo_val = INT_PAR; p[0].orig_val = FIX;   p[0].valor.v_int = 1;
    p[1].tipo_val = INT_PAR; p[1].orig_val = PARAM;
    p[2].tipo_val = INT_PAR; p[2].orig_val = FIX;   p[2].valor.v_int = 3;

    cria_func(tres_args, p, 3, codigo);
    fp f = (fp)codigo;

    check_int("f(0) = tres_args(1, 0, 3) = 301", f(0), 301);
    check_int("f(1) = tres_args(1, 1, 3) = 311", f(1), 311);
    check_int("f(5) = tres_args(1, 5, 3) = 351", f(5), 351);
}

/* ============================================================
 * Teste 7: tres_args(a, b, c) — (INT) PARAM + (INT) PARAM + (INT) PARAM
 *
 * Cria f(a, b, c) = tres_args(a, b, c)
 * Testes:    (2,3,4), (0,0,0), (1,1,1)
 * Resultados: 432, 0, 111
 * ============================================================ */
void teste7(void) {
    printf("\n[Teste 7] tres_args(a, b, c) — (INT) PARAM + (INT) PARAM + (INT) PARAM\n");
    typedef int (*fp)(int, int, int);
    DescParam p[3];
    unsigned char codigo[500];

    p[0].tipo_val = INT_PAR; p[0].orig_val = PARAM;
    p[1].tipo_val = INT_PAR; p[1].orig_val = PARAM;
    p[2].tipo_val = INT_PAR; p[2].orig_val = PARAM;

    cria_func(tres_args, p, 3, codigo);
    fp f = (fp)codigo;

    check_int("f(2,3,4) = tres_args(2,3,4) = 432", f(2,3,4), 432);
    check_int("f(0,0,0) = tres_args(0,0,0) =   0", f(0,0,0),   0);
    check_int("f(1,1,1) = tres_args(1,1,1) = 111", f(1,1,1), 111);
}

/* ============================================================
 * Teste 8: tres_args(a, var_b, c) — (INT) PARAM + (INT) IND + (INT) PARAM
 *
 * Cria f(a, c) = tres_args(a, var_b, c), var_b lida em tempo de execucao
 * Testes:    f(1,3) com var_b=2 e var_b=5
 * Resultados: 321, 351
 * ============================================================ */
void teste8(void) {
    printf("\n[Teste 8] tres_args(a, var_b, c) — (INT) PARAM + (INT) IND + (INT) PARAM\n");
    typedef int (*fp)(int, int);
    DescParam p[3];
    unsigned char codigo[500];
    int var_b;

    p[0].tipo_val = INT_PAR; p[0].orig_val = PARAM;
    p[1].tipo_val = INT_PAR; p[1].orig_val = IND;   p[1].valor.v_ptr = &var_b;
    p[2].tipo_val = INT_PAR; p[2].orig_val = PARAM;

    cria_func(tres_args, p, 3, codigo);
    fp f = (fp)codigo;

    var_b = 2; check_int("var_b=2: f(1,3) = tres_args(1,2,3) = 321", f(1,3), 321);
    var_b = 5; check_int("var_b=5: f(1,3) = tres_args(1,5,3) = 351", f(1,3), 351);
}

/* ============================================================
 * Teste 9: memcmp(fixa, candidata, n) — (PTR) FIX + (PTR) PARAM + (INT) PARAM
 *
 * Reproduz o exemplo do enunciado
 * Cria mesmo_prefixo(candidata, n) = memcmp(fixa, candidata, n)
 * Testes:    prefixo de 12 chars (igual) e 16 chars (diferente)
 * ============================================================ */
void teste9(void) {
    printf("\n[Teste 9] memcmp(fixa, candidata, n) — (PTR) FIX + (PTR) PARAM + (INT) PARAM\n");
    typedef int (*fp)(void*, size_t);
    DescParam p[3];
    unsigned char codigo[500];

    char fixa[] = "quero saber se a outra string e um prefixo dessa";
    char s[]    = "quero saber tudo";

    p[0].tipo_val = PTR_PAR; p[0].orig_val = FIX;   p[0].valor.v_ptr = fixa;
    p[1].tipo_val = PTR_PAR; p[1].orig_val = PARAM;
    p[2].tipo_val = INT_PAR; p[2].orig_val = PARAM;

    cria_func(memcmp, p, 3, codigo);
    fp mesmo_prefixo = (fp)codigo;

    check_zero("mesmo_prefixo(s, 12) == 0 (prefixo igual)",    mesmo_prefixo(s, 12),        1);
    check_zero("mesmo_prefixo(s, 16) != 0 (strings diferem)", mesmo_prefixo(s, strlen(s)),  0);
}

/* ============================================================
 * Teste 10: soma(*pa, *pb) — (INT) IND + (INT) IND
 *
 * Cria f() = soma(*pa, *pb), ambos lidos em tempo de execucao
 * Testes:    (pa=10, pb=20), (pa=-5, pb=5), (pa=0, pb=0)
 * Resultados: 30, 0, 0
 * ============================================================ */
void teste10(void) {
    printf("\n[Teste 10] soma(*pa, *pb) — (INT) IND + (INT) IND\n");
    typedef int (*fp)(void);
    DescParam p[2];
    unsigned char codigo[500];
    int a, b;

    p[0].tipo_val = INT_PAR; p[0].orig_val = IND; p[0].valor.v_ptr = &a;
    p[1].tipo_val = INT_PAR; p[1].orig_val = IND; p[1].valor.v_ptr = &b;

    cria_func(soma, p, 2, codigo);
    fp f = (fp)codigo;

    a = 10; b = 20; check_int("a=10, b=20: f() = soma(10, 20) =  30", f(),  30);
    a = -5; b =  5; check_int("a=-5, b= 5: f() = soma(-5,  5) =   0", f(),   0);
    a =  0; b =  0; check_int("a= 0, b= 0: f() = soma( 0,  0) =   0", f(),   0);
}

/* ============================================================
 * Teste 11: memcmp(fixa, *p_cand, n) — (PTR) FIX + (PTR) IND + (INT) PARAM
 *
 * p_cand e uma variavel char* que muda entre chamadas (PTR_PAR + IND)
 * Cria f(n) = memcmp(fixa, *p_cand, n)
 * Testes:    p_cand apontando para string igual e para string diferente
 * ============================================================ */
void teste11(void) {
    printf("\n[Teste 11] memcmp(fixa, *p_cand, n) — (PTR) FIX + (PTR) IND + (INT) PARAM\n");
    typedef int (*fp)(size_t);
    DescParam p[3];
    unsigned char codigo[500];

    char fixa[]  = "hello world";
    char igual[] = "hello world";
    char diff[]  = "hello xxxxx";
    char *p_cand;

    p[0].tipo_val = PTR_PAR; p[0].orig_val = FIX;   p[0].valor.v_ptr = fixa;
    p[1].tipo_val = PTR_PAR; p[1].orig_val = IND;   p[1].valor.v_ptr = &p_cand;
    p[2].tipo_val = INT_PAR; p[2].orig_val = PARAM;

    cria_func(memcmp, p, 3, codigo);
    fp f = (fp)codigo;

    p_cand = igual; check_zero("p_cand=igual: f(11) == 0 (strings iguais)",    f(11), 1);
    p_cand = diff;  check_zero("p_cand=diff:  f(11) != 0 (strings diferentes)", f(11), 0);
    p_cand = igual; check_zero("p_cand=igual: f(5)  == 0 (prefixo igual)",      f(5),  1);
}

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void) {
    printf("=== Testes cria_func ===\n");

    teste1();
    teste2();
    teste3();
    teste4();
    teste5();
    teste6();
    teste7();
    teste8();
    teste9();
    teste10();
    teste11();

    printf("\n=== Resultado: %d OK, %d FAIL ===\n", testes_ok, testes_fail);
    return testes_fail > 0 ? 1 : 0;
}