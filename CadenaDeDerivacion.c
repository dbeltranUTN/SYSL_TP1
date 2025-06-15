//TP grupal N°1: Cadenas de Derivacion
//Grupo: Pieronne Alexis, Beltrán Dante

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX 100

typedef struct {
    char izquierda;
    char derecha1;
    char derecha2;
} Produccion;

typedef struct {
    char terminales[MAX];
    char noTerminales[MAX];
    Produccion producciones[MAX];
    int cantProducciones;
    char axioma;
} Gramatica;

int esTerminal(char c, Gramatica *g) {
    return strchr(g->terminales, c) != NULL;
}

int esNoTerminal(char c, Gramatica *g) {
    return strchr(g->noTerminales, c) != NULL;
}

int validarProduccion(Produccion p, Gramatica *g) {
    if (!esNoTerminal(p.izquierda, g)) return 0; //Si el simbolo de la izquierda NO es un No Terminal...

    // Permitir producción con épsilon (ε) representada como '#'
    if (p.derecha1 == '#' && p.derecha2 == '\0') return 1;

    if (!esTerminal(p.derecha1, g)) return 0; //Si el simbolo de la derecha NO es un Terminal...
    if (p.derecha2 == '\0') return 1;
    return esNoTerminal(p.derecha2, g);
}

int cargarGramatica(Gramatica *g) {
    printf("Ingrese símbolos terminales (sin espacios): ");
    scanf("%s", g->terminales);

    printf("Ingrese símbolos no terminales (sin espacios): ");
    scanf("%s", g->noTerminales);

    printf("Ingrese axioma: ");
    scanf(" %c", &g->axioma);

    printf("Ingrese cantidad de producciones: ");
    scanf("%d", &g->cantProducciones);

    for (int i = 0; i < g->cantProducciones; i++) { //Cargamos las producciones
    char izq, der1, der2 = '\0';
    printf("Producción %d (formato A->aB, A->a o A->#): ", i + 1);
    scanf(" %c->%c%c", &izq, &der1, &der2);

    g->producciones[i].izquierda = izq;

    if (der1 == '#' && !isupper(der2)) { //Organizacion de las producciones
        g->producciones[i].derecha1 = '#';
        g->producciones[i].derecha2 = '\0';
    } else {
        g->producciones[i].derecha1 = der1;
        if (isupper(der2)) {
            g->producciones[i].derecha2 = der2;
        } else {
            g->producciones[i].derecha2 = '\0';
        }
    }
    if (!validarProduccion(g->producciones[i], g)) {
        printf("Producción no válida para gramática regular.\n");
        return 0;
    }
   }
    return 1;
}

void reemplazarPrimero(char *cadena, char nt, char *remplazo) {
    char buffer[MAX] = "";
    int reemplazado = 0;
    for (int i = 0; cadena[i]; i++) {
        if (!reemplazado && cadena[i] == nt) {
            strcat(buffer, remplazo);
            reemplazado = 1;
        } else {
            strncat(buffer, &cadena[i], 1);
        }
    }
    strcpy(cadena, buffer);
}

void generarPalabra(Gramatica *g) {
    char palabra[MAX] = "";
    palabra[0] = g->axioma;
    palabra[1] = '\0';

    printf("\nDerivación: %s", palabra);

    while (1) {
        int cambio = 0;

        for (int i = 0; palabra[i]; i++) {
            if (esNoTerminal(palabra[i], g)) {
                // Buscar producciones aplicables
                Produccion posibles[MAX];
                int cant = 0;

                for (int j = 0; j < g->cantProducciones; j++) {
                    if (g->producciones[j].izquierda == palabra[i]) {
                        posibles[cant++] = g->producciones[j];
                    }
                }

                if (cant == 0) return;

                // Seleccionar aleatoriamente una producción
                int pos = rand() % cant;
                char remplazo[3] = "";

                if (posibles[pos].derecha1 == '#') {
                    remplazo[0] = '\0'; // Cadena vacía
                } else {
                    remplazo[0] = posibles[pos].derecha1;
                    remplazo[1] = posibles[pos].derecha2 != '\0' ? posibles[pos].derecha2 : '\0';
                    remplazo[2] = '\0';
                }

                reemplazarPrimero(palabra, palabra[i], remplazo);
                printf(" => %s", palabra);
                cambio = 1;
                break;  // Solo una producción por paso
            }
        }

        if (!cambio) break;
    }

    printf("\nPalabra generada: %s\n", palabra);
}

int main() {
    Gramatica g;

    srand(time(NULL));  // Inicializar aleatoriedad

    if (!cargarGramatica(&g)) {
        printf("Error: gramática no válida.\n");
        return 1;
    }

    char opcion;
    do {
        generarPalabra(&g);
        printf("\n¿Generar otra palabra? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');

    return 0;
}
