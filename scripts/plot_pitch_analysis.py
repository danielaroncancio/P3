import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile

def plot_pitch_analysis(wav_file, segment_duration=0.03):
    # Leer el archivo WAV
    sample_rate, signal = wavfile.read(wav_file)
    
    # Si es estéreo, convertir a mono
    if len(signal.shape) == 2:
        signal = signal[:, 0]

    # Seleccionar un segmento de 30 ms
    segment_samples = int(segment_duration * sample_rate)
    segment = signal[:segment_samples]

    # Calcular autocorrelación
    autocorr = np.correlate(segment, segment, mode='full')
    autocorr = autocorr[autocorr.size // 2:]  # Tomar la mitad positiva

    # Encontrar el primer máximo secundario
    diffs = np.diff(autocorr)
    max_secondary_index = np.argmax((diffs[:-1] > 0) & (diffs[1:] <= 0)) + 1

    # Plotear resultados
    plt.figure(figsize=(12, 6))

    # Señal temporal
    plt.subplot(2, 1, 1)
    time_axis = np.linspace(0, segment_duration, segment_samples)
    plt.plot(time_axis, segment)
    plt.title("Segmento de la señal temporal (30 ms)")
    plt.xlabel("Tiempo (s)")
    plt.ylabel("Amplitud")

    # Autocorrelación
    plt.subplot(2, 1, 2)
    lag_axis = np.arange(len(autocorr)) / sample_rate
    plt.plot(lag_axis, autocorr, label="Autocorrelación")
    plt.axvline(x=lag_axis[max_secondary_index], color='r', linestyle='--', label="Primer máximo secundario")
    plt.title("Autocorrelación de la señal")
    plt.xlabel("Retraso (s)")
    plt.ylabel("Amplitud")
    plt.legend()

    plt.tight_layout()
    plt.show()

# Archivo de entrada
wav_file = "../prueba.wav"  # Ajusta esta ruta si el archivo está en otra carpeta
plot_pitch_analysis(wav_file)
