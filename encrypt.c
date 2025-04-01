#include <stdio.h>      // Para printf, fprintf, perror
#include <stdlib.h>     // Para srand, rand, exit
#include <string.h>     // Para strlen
#include <fcntl.h>      // Para open
#include <unistd.h>     // Para write, close
#include <time.h>       // Para time (semilla de random)

int main(int argc, char *argv[]) {
    int i, j;
    char *mensaje;
    int out_fd = STDOUT_FILENO; // Archivo de salida: por defecto, es la salida estándar (pantalla)

    // Inicializa la semilla para generar números pseudoaleatorios distintos cada vez
    srand(time(NULL));

    // Si se pasa solo un argumento (el mensaje), lo usamos y escribimos en pantalla
    if (argc == 2) {
        mensaje = argv[1];

    // Si se pasan dos argumentos (archivo y mensaje)
    } else if (argc == 3) {
        // Abrimos archivo de salida en modo escritura, lo creamos o lo truncamos si existe
        out_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        // Si falla la apertura del archivo, mostramos error y terminamos
        if (out_fd < 0) {
            perror("open");
            exit(1);
        }

        // El mensaje a encriptar es el segundo argumento
        mensaje = argv[2];

    } else {
        // Si no se pasó ni 1 ni 2 argumentos, mostramos cómo se usa el programa
        fprintf(stderr, "Uso: %s [archivo_salida] \"mensaje\"\n", argv[0]);
        return 1;
    }

    // Recorremos cada carácter del mensaje original
    for (i = 0; i < strlen(mensaje); i++) {
        // Por cada carácter, escribimos primero 7 bytes aleatorios
        for (j = 0; j < 7; j++) {
            unsigned char r = rand() % 256;   // Número aleatorio entre 0 y 255
            write(out_fd, &r, 1);             // Escribimos 1 byte aleatorio en el archivo o salida
        }

        // Luego escribimos el carácter real del mensaje
        write(out_fd, &mensaje[i], 1);
    }

    // Si el archivo de salida no es la salida estándar, lo cerramos
    if (out_fd != STDOUT_FILENO) {
        close(out_fd);
    }

    return 0; // Fin del programa
}
