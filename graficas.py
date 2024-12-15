import numpy as np
import matplotlib.pyplot as plt

# Cargar los datos de la señal temporal (30 ms)
signal = np.loadtxt("frame_signal.txt")
n_samples = len(signal)
time = np.linspace(0, 0.03, n_samples)  # 30 ms segment

# Cargar los datos de autocorrelación
autocorr = np.loadtxt("autocorrelation.txt", max_rows=n_samples)
max_secondary = np.loadtxt("autocorrelation.txt", skiprows=n_samples)

# Crear las gráficas
plt.figure(figsize=(10, 5))

# Subplot 1: Señal temporal
plt.subplot(2, 1, 1)
plt.plot(time, signal)
plt.title("Señal temporal (30 ms de fonema sonoro)")
plt.xlabel("Tiempo (s)")
plt.ylabel("Amplitud")

# Indicar el período del pitch
max_pos = np.argmax(signal)
plt.axvline(time[max_pos], color='r', linestyle='--', label='Pitch Period')
plt.legend()

# Subplot 2: Autocorrelación
plt.subplot(2, 1, 2)
lags = np.arange(len(autocorr))
plt.plot(lags, autocorr)
plt.title("Autocorrelación y máximo secundario")
plt.xlabel("Lag")
plt.ylabel("Valor de autocorrelación")

# Indicar el máximo secundario
plt.axvline(max_secondary, color='g', linestyle='--', label='Primer máximo secundario')
plt.legend()

# Mostrar la gráfica
plt.tight_layout()
plt.show()
