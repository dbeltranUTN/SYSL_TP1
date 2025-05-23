#include <stdio.h>

int main() {
    printf("¡Hola desde Alpine C devcontainer!\n");
    printf("¿Cual es tu nombre?\n");
    char nombre[50];
    scanf("%s", nombre);
    printf("Un gusto conocerte ");
    printf(nombre);
    printf("\n");
    return 0;
}