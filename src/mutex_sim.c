#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// El cerrojo a nivel de Kernel (Sistema Operativo)
pthread_mutex_t lock;

void* simulation_mutex(void* arg) {
    int id = *(int*)arg;
    struct timespec start, end;
    
    FILE *f = fopen("data/mutex_metrics.csv", "a");
    if (f == NULL) return NULL;

    for(int i = 0; i < 10; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start); 
        
        // --- ESPERA BLOQUEADA (Kernel gestiona el sueño del hilo) ---
        pthread_mutex_lock(&lock); 
        
        clock_gettime(CLOCK_MONOTONIC, &end); 
        
        long latency = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        fprintf(f, "%d, %d, %ld\n", id, i, latency);
        
        // Sección Crítica (Simulamos trabajo pesado)
        usleep(10000); 
        
        pthread_mutex_unlock(&lock); // El Kernel despierta al siguiente hilo
        usleep(5000); 
    }

    fclose(f);
    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);
    
    FILE *f = fopen("data/mutex_metrics.csv", "w");
    fprintf(f, "Hilo_ID, Iteracion, Latencia_ns\n");
    fclose(f);

    pthread_t threads[4];
    int ids[4];

    for(int i = 0; i < 4; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, simulation_mutex, &ids[i]);
    }

    for(int i = 0; i < 4; i++) pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
    printf("Simulación Mutex terminada. Datos en data/mutex_metrics.csv\n");
    return 0;
}