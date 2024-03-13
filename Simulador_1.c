#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Definición de los mutexes
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Función que ejecuta el hilo 1
void* hilo1(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex1); // Adquiere el primer mutex
        printf("Hilo 1 ha adquirido el mutex 1\n");
        sleep(1); // Espera para hacer más fácil que ocurra el deadlock
        
        printf("Hilo 1 intenta adquirir el mutex 2\n");
        pthread_mutex_lock(&mutex2); // Intenta adquirir el segundo mutex
        printf("Hilo 1 ha adquirido el mutex 2\n");
        
        pthread_mutex_unlock(&mutex2); // Libera el segundo mutex
        pthread_mutex_unlock(&mutex1); // Libera el primer mutex
        sleep(1);
    }
}

// Función que ejecuta el hilo 2
void* hilo2(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex2); // Adquiere el segundo mutex
        printf("Hilo 2 ha adquirido el mutex 2\n");
        sleep(1); // Espera para hacer más fácil que ocurra el deadlock
        
        printf("Hilo 2 intenta adquirir el mutex 1\n");
        pthread_mutex_lock(&mutex1); // Intenta adquirir el primer mutex
        printf("Hilo 2 ha adquirido el mutex 1\n");
        
        pthread_mutex_unlock(&mutex1); // Libera el primer mutex
        pthread_mutex_unlock(&mutex2); // Libera el segundo mutex
        sleep(1);
    }
}

int main() {
    pthread_t t1, t2;
    
    // Creación de los hilos
    pthread_create(&t1, NULL, hilo1, NULL);
    pthread_create(&t2, NULL, hilo2, NULL);
    
    // Espera a que los hilos terminen (lo cual nunca sucederá en este caso)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
