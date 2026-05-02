import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Cargar ambos datasets
df_spin = pd.read_csv('data/spinlock_metrics.csv')
df_mutex = pd.read_csv('data/mutex_metrics.csv')

# Añadir una columna para identificar el tipo
df_spin['Tipo'] = 'Spinlock (TSL)'
df_mutex['Tipo'] = 'Mutex (Kernel)'

# Combinar ambos
df_total = pd.concat([df_spin, df_mutex])

# Graficar
plt.figure(figsize=(10, 6))
sns.barplot(data=df_total, x='Tipo', y=' Latencia_ns', capsize=.1)
plt.title('Comparación de Latencia Promedio: Spinlock vs Mutex')
plt.ylabel('Latencia (Nanosegundos)')
plt.grid(axis='y', linestyle='--', alpha=0.7)

plt.savefig('docs/comparativa_latencia.png')
plt.show()
