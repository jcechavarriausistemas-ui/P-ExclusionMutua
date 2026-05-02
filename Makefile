CC=gcc
CFLAGS=-O2 -pthread

all: spinlock mutex

spinlock:
	$(CC) $(CFLAGS) src/main.c -o simulador_spinlock

mutex:
	$(CC) $(CFLAGS) src/mutex_sim.c -o simulador_mutex

clean:
	rm -f simulador_spinlock simulador_mutex