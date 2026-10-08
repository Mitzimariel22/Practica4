#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/wait.h>

void imprimir_nodo(char *cmd) {
    char *user = getpwuid(getuid())->pw_name;
    char *tty = ttyname(STDIN_FILENO);
    printf("%-7s %-5d %-5d %-13s %s\n", user, getpid(), getppid(), tty ? tty : "?", cmd);
}

void construir_arbol_binario(int nivel_actual, int profundidad_max, char *cmd) {
    if (nivel_actual >= profundidad_max) return;

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Proceso Hijo
            imprimir_nodo(cmd);
            construir_arbol_binario(nivel_actual + 1, profundidad_max, cmd);
            sleep(15);
            exit(0);
        }
    }
    while (wait(NULL) > 0);
}

int main(int argc, char *argv[]) {
    int prof;
    printf("Proporciona el nivel de profundidad de tu Arbol de procesos\n");
    if (scanf("%d", &prof) != 1 || prof <= 0) return 1;

    printf("%-7s %-5s %-5s %-13s %s\n", "UID", "PID", "PPID", "TTY", "COMMAND");
    imprimir_nodo(argv[0]);

    construir_arbol_binario(1, prof, argv[0]);
    sleep(15);
    return 0;
}