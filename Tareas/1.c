#include <stdio.h>
#include <stdbool.h> //Librería para usar bool 

// Variables globales
int a = 10, b = 1; // <-- Podemos cambiar los valores

// Declaración de la función
void imprimirResultados(int suma, int resta, 
						float mult, float div, bool band);

// Función principal
int main(int argc, char** argv) {
    // Se declaran e inicializan las variables    
    int suma, resta;
    float mult, div;
    bool band = true;
    
    // Se opera
    suma = a + b;
    resta = a - b;
    mult = (float)a * b;
    
    if(b == 0){
		band = false;
	}
	else{
		div = (float)a / b;  // Convertir a float para evitar división entera
    }
	
	imprimirResultados(suma, resta, mult, div, band);
						
    return 0;
}

/**
 * Función que me imprime los resultados de las operaciones en pantalla.
 */ 
void imprimirResultados(int suma, int resta, 
						float mult, float div, bool band){
	
    printf("Hola, Mundo!\n");

    printf("Suma de %d + %d = %d\n", a, b, suma);
    printf("Resta de %d - %d = %d\n", a, b, resta);
    printf("Multiplicación de %d * %d = %.2f\n", a, b, mult);
    
    if(band){
		printf("División de %d / %d = %.2f\n", a, b, div);
	}
    else{
		printf("ERROR: no se puede dividir por cero!\n");
	}						
}
