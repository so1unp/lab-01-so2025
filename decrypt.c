#include <stdio.h>      // Para perror
#include <stdlib.h>     // Para exit, malloc, etc.
#include <fcntl.h>      // Para open
#include <unistd.h>     // Para read, write, lseek, close
#include <sys/stat.h>   // Para struct stat y fstat


int main(int argc, char *argv[]) {
    int in_fd = STDIN_FILENO; // Por defecto, leemos desde la entrada estándar
    struct stat st;           // Para guardar info del archivo
    unsigned char byte;       // Donde se guarda el byte leído
    int total, i;

    //Si se pasa un archivo como argumento:
    if (argc == 2) {
        // Abrir el archivo en modo lectura
        in_fd = open(argv[1], O_RDONLY);
        if (in_fd < 0) {
            perror("open");  // Si falla, muestra error
            return 1;
        }

        // Obtener el tamaño del archivo
        fstat(in_fd, &st);

        // Calculamos cuántos caracteres reales tiene el mensaje:
        // Cada carácter real está precedido por 7 bytes aleatorios → total / 8
        total = st.st_size / 8;

    } else {
        //Si no se pasa archivo → leer desde stdin (entrada estándar):
        // Leer de stdin, carácter por carácter, hasta EOF
        total = 0;
        while (read(in_fd, &byte, 1) == 1) {
            // Cada 8° byte es uno real (los anteriores son basura aleatoria)
            if ((total % 8) == 7) {
                write(STDOUT_FILENO, &byte, 1); // Imprimir solo el real
            }
            total++; // Contador de bytes leídos
        }
        return 0; // Termina acá si leyó desde stdin
    }


    // Si venimos leyendo desde archivo (no stdin), extraemos byte a byte:
    for (i = 0; i < total; i++) {
        lseek(in_fd, 7, SEEK_CUR);       // Saltamos los 7 bytes basura
        read(in_fd, &byte, 1);           // Leemos el byte real
        write(STDOUT_FILENO, &byte, 1);  // Lo imprimimos en salida estándar
    }

    // Cerramos el archivo si fue abierto
    if (in_fd != STDIN_FILENO) {
        close(in_fd);
    }

    return 0;
}
