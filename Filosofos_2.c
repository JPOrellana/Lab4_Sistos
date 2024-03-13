#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

sem_t tenedores[NUM_FILOSOFOS];

void* filosofo(void* num) {
    int* i = (int*)num;

    while (1) {
        printf("Filosofo %d está pensando\n", *i);
        sleep(1);

        sem_wait(&tenedores[*i]); // Intenta agarrar el tenedor izquierdo
        sem_wait(&tenedores[(*i + 1) % NUM_FILOSOFOS]); // Intenta agarrar el tenedor derecho
        
        // Come
        printf("Filosofo %d está comiendo\n", *i);
        sleep(1);
        
        sem_post(&tenedores[*i]); // Suelta el tenedor izquierdo
        sem_post(&tenedores[(*i + 1) % NUM_FILOSOFOS]); // Suelta el tenedor derecho
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_FILOSOFOS];
    int status, i;
    int filosofos[NUM_FILOSOFOS];

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        sem_init(&tenedores[i], 0, 1); // Inicializa los semáforos
    }

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos[i] = i;
        status = pthread_create(&hilos[i], NULL, filosofo, (void*)&filosofos[i]);

        if (status != 0) {
            printf("No se puede crear el hilo\n");
            return -1;
        }
    }

    for (i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
