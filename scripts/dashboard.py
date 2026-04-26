import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# 1. Cargar los datos
try:
    df = pd.read_csv('data/spinlock_metrics.csv')
except FileNotFoundError:
    print("Error: No se encontró el archivo CSV en data/. Ejecuta el simulador primero.")
    exit()

# 2. Pivotar los datos para el mapa de calor (Filas: Hilos, Columnas: Iteraciones)
# Usamos la latencia como el valor de intensidad (color)
pivot_df = df.pivot(index='Hilo_ID', columns=' Iteracion', values=' Latencia_ns')

# 3. Configurar la estética
plt.figure(figsize=(10, 6))
sns.heatmap(pivot_df, annot=True, fmt=".0f", cmap="YlOrRd", cbar_kws={'label': 'Latencia (ns)'})

# 4. Títulos y etiquetas
plt.title('Mapa de Calor: Latencia de Adquisición (Spinlock - TSL)', fontsize=15)
plt.xlabel('Número de Iteración')
plt.ylabel('ID del Hilo')

# 5. Guardar y mostrar
plt.savefig('docs/mapa_calor_spinlock.png')
print("Gráfico guardado en docs/mapa_calor_spinlock.png")
plt.show()