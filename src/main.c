#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

// El cerrojo atómico (Nivel Hardware)
atomic_flag lock = ATOMIC_FLAG_INIT;

void* tarea_del_hilo(void* arg) {
    int id = *(int*)arg;
    
    for(int i = 0; i < 3; i++) {
        printf("Hilo %d intentando entrar...\n", id);
        
        // --- ESPERA ACTIVA (TSL) ---
        while (atomic_flag_test_and_set(&lock)) {
            // El hilo se queda aquí gastando ciclos de CPU
            // Esto es lo que generará "calor" en tu simulación
        }
        
        // --- SECCIÓN CRÍTICA ---
        printf(">>> Hilo %d está ADENTRO.\n", id);
        sleep(1); // Simulamos un trabajo pesado
        
        // --- LIBERACIÓN ---
        atomic_flag_clear(&lock);
        printf("Hilo %d salió y liberó el lock.\n", id);
        
        sleep(1); // Descanso antes de volver a pelear
    }
    return NULL;
}

int main() {
    pthread_t hilos[4];
    int ids[4];

    for(int i = 0; i < 4; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], NULL, tarea_del_hilo, &ids[i]);
    }

    for(int i = 0; i < 4; i++) pthread_join(hilos[i], NULL);

    return 0;
}