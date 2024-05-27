import csv
import matplotlib.pyplot as plt
import numpy as np

# Read data from sigD.csv
t = []  # time
data = []  # signal data

with open('sigA.csv') as f:
    reader = csv.reader(f)
    for row in reader:
        t.append(float(row[0]))
        data.append(float(row[1]))

# Calculate sample rate
num_data_points = len(t)
total_time = t[-1] - t[0]
sample_rate = num_data_points / total_time

# FIR filter coefficients for signal A B
fir_coeffs = [0.057983449118322046
, 0.076058876411434606
, 0.091941597683949869
, 0.104337653981733711
, 0.112217996007993162
, 0.114920853593133421
, 0.112217996007993162
, 0.104337653981733711
, 0.091941597683949869
, 0.076058876411434606
, 0.057983449118322046]
# FIR filter coefficients for signal D C
fir_coeffs = [0.036304422348816152
, 0.053773337866256730
, 0.070536329266200334
, 0.085265824496463749
, 0.096761817467658717
, 0.104069976963569261
, 0.106576583182070250
, 0.104069976963569261
, 0.096761817467658717
, 0.085265824496463749
, 0.070536329266200334
, 0.053773337866256730
, 0.036304422348816152]



# Apply FIR filter
fir_filtered_data = np.convolve(data, fir_coeffs, mode='valid')

# Perform FFT
n = len(data)
fft_data = np.fft.fft(data) / n
fft_freqs = np.fft.fftfreq(n, 1.0 / sample_rate)

n_fir_filtered = len(fir_filtered_data)
fft_fir_filtered_data = np.fft.fft(fir_filtered_data) / n_fir_filtered
fft_fir_filtered_freqs = np.fft.fftfreq(n_fir_filtered, 1.0 / sample_rate)

# Plot signal and FFT
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 6))

# Signal plot
ax1.plot(t[:len(fir_filtered_data)], data[:len(fir_filtered_data)], 'k', label='Original Data')
ax1.plot(t[:len(fir_filtered_data)], fir_filtered_data, 'r', label='FIR Filtered Data')
ax1.set_title(f'Signal Comparison (FIR Filter, {len(fir_coeffs)} taps)')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax1.legend()

# FFT plot
ax2.loglog(fft_freqs[fft_freqs >= 0][:len(fft_fir_filtered_data)], np.abs(fft_data[fft_freqs >= 0])[:len(fft_fir_filtered_data)], 'k', label='Original FFT')
ax2.loglog(fft_fir_filtered_freqs[fft_fir_filtered_freqs >= 0], np.abs(fft_fir_filtered_data[fft_fir_filtered_freqs >= 0]), 'r', label='FIR Filtered FFT')
ax2.set_title('FFT Comparison')
ax2.set_xlabel('Frequency (Hz)')
ax2.set_ylabel('Magnitude')
ax2.legend()

plt.tight_layout()
plt.show()