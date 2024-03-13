#include <stdio.h>
#include <stdbool.h>

#define N 5 // Número de procesos
#define M 3 // Número de tipos de recursos

// La matriz de asignación, cuánto recurso ha sido asignado a cada proceso
int asignacion[N][M] = {
    {0, 1, 0}, // Recursos asignados al proceso P0
    {2, 0, 0}, // Recursos asignados al proceso P1
    {3, 0, 2}, // etc.
    {2, 1, 1},
    {0, 0, 2}
};

// La matriz máxima que cada proceso necesita
int maximo[N][M] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Los recursos disponibles
int disponibles[M] = {3, 3, 2};

// La matriz necesidad, calculada como maximo - asignacion
int necesidad[N][M];

// Función para calcular la matriz de necesidad
void calcularNecesidad() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            necesidad[i][j] = maximo[i][j] - asignacion[i][j];
        }
    }
}

// Función para verificar si es seguro conceder recursos a todos los procesos
bool esSeguro() {
    bool finalizado[N] = {0};
    int trabajo[M];
    for (int i = 0; i < M; i++) {
        trabajo[i] = disponibles[i];
    }

    while (true) {
        bool encontrado = false;
        for (int i = 0; i < N; i++) {
            if (!finalizado[i]) {
                bool posible = true;
                for (int j = 0; j < M; j++) {
                    if (necesidad[i][j] > trabajo[j]) {
                        posible = false;
                        break;
                    }
                }

                if (posible) {
                    for (int k = 0; k < M; k++) {
                        trabajo[k] += asignacion[i][k];
                    }
                    finalizado[i] = true;
                    encontrado = true;
                }
            }
        }

        if (!encontrado) {
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        if (!finalizado[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    calcularNecesidad();
    bool seguro = esSeguro();

    if (seguro) {
        printf("El estado es seguro.\n");
    } else {
        printf("El estado no es seguro.\n");
    }

    return 0;
}
