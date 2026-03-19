#include <stdio.h>

unsigned char switch_byte(unsigned char x) {

    unsigned char parte_baixa = x & 0x0F;  
    unsigned char parte_alta  = x & 0xF0;  

    parte_baixa <<= 4;  
    parte_alta  >>= 4;   

    return parte_baixa | parte_alta; 
}

int main() {

    unsigned char x = 0xAB;
    unsigned char resultado = switch_byte(x);

    printf("Entrada: 0x%X\n", x);
    printf("Resultado: 0x%X\n", resultado);

    return 0;
}