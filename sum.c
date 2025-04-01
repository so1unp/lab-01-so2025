#include <stdio.h>      // Para printf() y fgets()
#include <stdlib.h>     // Para atoi()
#include <string.h>     // Para strtok()

int main(int argc, char *argv[])
{
    int suma = 0;  // Variable donde se acumula la suma total

    // Si se pasan argumentos por línea de comandos
    if (argc > 1) {
        // Recorre los argumentos desde argv[1] (el [0] es el nombre del programa)
        for (int i = 1; i < argc; i++) {
            suma += atoi(argv[i]); // Convierte cada argumento a entero y lo suma
        }

    } else {
        // Si no se pasan argumentos, lee desde la entrada estándar
        char linea[10];  // Buffer para leer una línea (hasta 9 caracteres + \0)

        // Lee línea por línea hasta EOF (Ctrl+D)
        while (fgets(linea, sizeof(linea), stdin)) {
            // Divide la línea en "tokens" separados por espacios, tabs o enter
            char *token = strtok(linea, " \t\n");

            // Mientras haya tokens en la línea
            while (token != NULL) {
                suma += atoi(token);  // Convierte el token a entero y lo suma
                token = strtok(NULL, " \t\n");  // Pasa al siguiente token
            }
        }
    }

    printf("%d\n", suma);  // Imprime el resultado de la suma
    return 0;              // Fin del programa con salida exitosa
}

