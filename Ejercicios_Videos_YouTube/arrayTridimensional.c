#include <stdio.h>

int main() {
    int array[3][3][3];
    
    // Inicialización del array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                array[i][j][k] = i * 9 + j * 3 + k; // Ejemplo de inicialización
            }
        }
    }

    // Iteración sobre el array y mostrando los valores
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                printf("array[%d][%d][%d] = %d\n", i, j, k, array[i][j][k]);
            }
        }
    }

    return 0;
}
