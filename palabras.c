#include <stdio.h>   // Para getchar() y putchar()
#include <ctype.h>   // Para isspace()

int main()
{
    int c;  // Variable para guardar el carácter leído

    while (1) {  // Bucle infinito: se cortará solo con EOF
        c = getchar();  // Lee un carácter desde la entrada estándar (teclado)

        if (c == EOF) { // Si se presiona Ctrl + D (fin de entrada)
            break;      // Se rompe el bucle y termina el programa
        }

        if (isspace(c)) {  // Si el carácter es un espacio, tab, o salto de línea
            putchar('\n'); // Imprime un salto de línea
        } else {
            putchar(c);    // Si es un carácter "normal", lo imprime tal cual
        }
    }

    return 0; // Fin del programa
}

