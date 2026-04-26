#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <unistd.h>

atomic_flag lock = ATOMIC_FLAG_INIT;

void* simulation(void* arg) {
    int id = *(int*)arg;
    struct timespec start, end;
    
    // Abrir el archivo en modo "append" (añadir)
    FILE *f = fopen("data/spinlock_metrics.csv", "a");
    if (f == NULL) return NULL;

    for(int i = 0; i < 10; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start); // Marca de tiempo INICIO
        
        // --- ESPERA ACTIVA (TSL) ---
        while (atomic_flag_test_and_set(&lock)); 
        
        clock_gettime(CLOCK_MONOTONIC, &end); // Marca de tiempo FIN
        
        // Cálculo de latencia en nanosegundos
        long latency = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        
        // Guardar: ID_Hilo, Iteracion, Latencia_ns
        fprintf(f, "%d, %d, %ld\n", id, i, latency);
        
        // Sección Crítica
        usleep(10000); // 10ms de trabajo
        
        atomic_flag_clear(&lock);
        usleep(5000); // Pequeño descanso
    }

    fclose(f);
    return NULL;
}

int main() {
    // Crear encabezado del CSV
    FILE *f = fopen("data/spinlock_metrics.csv", "w");
    fprintf(f, "Hilo_ID, Iteracion, Latencia_ns\n");
    fclose(f);

    pthread_t threads[4];
    int ids[4];

    for(int i = 0; i < 4; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, simulation, &ids[i]);
    }

    for(int i = 0; i < 4; i++) pthread_join(threads[i], NULL);

    printf("Simulación terminada. Datos guardados en data/spinlock_metrics.csv\n");
    return 0;
}