# Bitácora de Desarrollo - Sesión #1

**Fecha:** 24 de abril de 2026

**Estado:** Infraestructura Base Completada

## 1. Resumen de Actividades

- **Definición del Proyecto:** Se estableció el desarrollo de un visualizador y simulador de exclusión mutua para comparar mecanismos de **Spinlock**, **Mutex** y **Monitores**.
    
- **Configuración del Entorno:** Instalación de herramientas esenciales en **Linux Mint - Cinnamon**, incluyendo `build-essential` (GCC/Make), `git` y **Obsidian** para documentación técnica.
    
- **Sincronización de Repositorio:** Creación y clonación del repositorio de GitHub `Visualizador-de-ExclusionMutua` para trabajo colaborativo.


- **Estructura de Directorios:** Se organizó el espacio de trabajo con las siguientes carpetas:
    
    - `/src`: Código fuente en C (Capa de Hardware y OS).
        
    - `/scripts`: Scripts de Python para el Dashboard de análisis.
        
    - `/docs`: Documentación técnica y diagramas de flujo.
        
    - `/data`: Almacenamiento de métricas (latencia, throughput, context switches).
        
1.1- Instalamos dependencias necesarias del Codigo:
`sudo apt update`
`sudo apt install build-essential git python3 python3-pip gdb`


## 2. Definición Técnica de Mecanismos a Implementar

|**Mecanismo**|**Nivel**|**Técnica de Espera**|**Instrucción/Syscall Base**|
|---|---|---|---|
|**Spinlock**|Hardware|Activa (Busy-wait)|`TSL` / `XCHG` / `CAS`|
|**Mutex**|Kernel|Bloqueada (Sleep)|`futex(FUTEX_WAIT)`|
|**Monitor**|POSIX|Bloqueada + Señal|`pthread_cond_wait`|

## 3. Próximos Pasos

- Implementar la lógica del **Spinlock** en `src/main.c` usando instrucciones atómicas de la CPU para garantizar atomicidad en el bus de memoria.
    
- Configurar el hilo observador que muestreará el estado de los hilos cada 1 ms para el mapa de calor.

___________________________________
### (25/04/2026)  Actualización: Sesión #1 - Capa de Hardware e Infraestructura

#### 1. Automatización de Compilación (Makefile)

Se implementó un `Makefile` para estandarizar el proceso de construcción. Los parámetros clave son:
- **Flags de optimización (`-O2`)**: Necesarios para que el compilador no elimine los bucles de espera activa por considerarlos "innecesarios".
- **Librería POSIX (`-pthread`)**: Para la gestión de hilos en Linux Mint.

El makefile se crea en un archivo de texto sin formato
por lo que es recomendado en la terminal (Linux Especificamente), escribir 
nano Makefile -> Enter
Copiar el siguiente Codigo, y despues Ctrl+O ( Para guardar ) y Ctrl+X para salir

```
CC=gcc
CFLAGS=-O2 -pthread
SRC=src/main.c
OBJ=simulador

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ)
```
Este queda adjunto con [[src/main.c]]
Para hacer las pruebas correspondientes
`make`
`./simulador`
para subidas a repositorios se recomienda  `make clean`antes de subir a un repositorio 
#### 2. Implementación del Spinlock (Instrucción TSL)

Se codificó el primer mecanismo de exclusión mutua en `src/main.c`.
- **Mecanismo**: `atomic_flag_test_and_set`.
- **Comportamiento observado**: Los hilos entran en un estado de **espera activa (busy-wait)**. Durante las pruebas, se observó que los hilos no ceden el procesador, manteniendo un núcleo ocupado al 100% mientras el cerrojo está en uso.

#### 3. Diagrama de Lógica de Ejecución

El flujo actual sigue este orden:

1. **Intento de Entrada**: El hilo ejecuta la instrucción atómica.
2. **Condición de Bloqueo**: Si el valor es `true`, el hilo repite el bucle infinitamente (consumo de energía/CPU).
3. **Sección Crítica**: Solo un hilo accede al recurso protegido.
4. **Liberación**: `atomic_flag_clear` permite que el siguiente hilo en el bucle de espera tome el control.

---

### Tareas pendientes para la Sesión #2:

- [ ] Modificar `src/main.c` para exportar tiempos de latencia a `/data/spinlock_results.csv`.
    
- [ ] Implementar la **Capa de Sistema Operativo** (Mutex de `pthread`) para comparar el ahorro de CPU.