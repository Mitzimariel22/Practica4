#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void generar_petalos(int n_petalos) {
    for (int i = 0; i < n_petalos; i++) {
        if (fork() == 0) {
            sleep(60); // Pétalo en suspensión
            exit(0);
        }
    }
    sleep(60);
    while (wait(NULL) > 0);
    exit(0);
}

int main(void) {
    int nodos_tallo = 4;
    int num_flores = 3;
    int num_petalos = 4;

    // Tallo base lineal (4 nodos)
    for (int i = 0; i < nodos_tallo; i++) {
        pid_t pid = fork();
        if (pid > 0) {
            wait(NULL);
            return 0;
        }
    }

    // Flores (3 nodos) y pétalos (4 por flor)
    for (int i = 0; i < num_flores; i++) {
        pid_t flor = fork();
        if (flor == 0) {
            generar_petalos(num_petalos);
        }

        if (i < num_flores - 1) {
            pid_t sig_tallo = fork();
            if (sig_tallo > 0) {
                wait(NULL);
                wait(NULL);
                return 0;
            }
        }
    }

    sleep(60);
    while (wait(NULL) > 0);
    return 0;
}