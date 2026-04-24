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
        

## 2. Definición Técnica de Mecanismos a Implementar

|**Mecanismo**|**Nivel**|**Técnica de Espera**|**Instrucción/Syscall Base**|
|---|---|---|---|
|**Spinlock**|Hardware|Activa (Busy-wait)|`TSL` / `XCHG` / `CAS`|
|**Mutex**|Kernel|Bloqueada (Sleep)|`futex(FUTEX_WAIT)`|
|**Monitor**|POSIX|Bloqueada + Señal|`pthread_cond_wait`|

## 3. Próximos Pasos

- Implementar la lógica del **Spinlock** en `src/main.c` usando instrucciones atómicas de la CPU para garantizar atomicidad en el bus de memoria.
    
- Configurar el hilo observador que muestreará el estado de los hilos cada 1 ms para el mapa de calor.