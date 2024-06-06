import csv
import matplotlib.pyplot as plt
import numpy as np

# Read data from sigD.csv
t = []  # time
data = []  # signal data

with open('sigD.csv') as f:
    reader = csv.reader(f)
    for row in reader:
        t.append(float(row[0]))
        data.append(float(row[1]))

# Calculate sample rate
num_data_points = len(t)
total_time = t[-1] - t[0]
sample_rate = num_data_points / total_time
#IIR filter
# AB coeffcient
A = 0.4
B = 0.6
filtered_data = [0]
for i in range(1, len(data)):
    new_average = A * data[i-1] + B * data[i]
    filtered_data.append(new_average)
# Moving average filter
#filter_length = 200
#filtered_data = []
#for i in range(filter_length, len(data)):
#    window = data[i - filter_length:i]
#    filtered_data.append(sum(window) / len(window))

# Perform FFT
n = len(data)
fft_data = np.fft.fft(data) / n
fft_freqs = np.fft.fftfreq(n, 1.0 / sample_rate)

n_filtered = len(filtered_data)
fft_filtered_data = np.fft.fft(filtered_data) / n_filtered
fft_filtered_freqs = np.fft.fftfreq(n_filtered, 1.0 / sample_rate)

# Plot signal and FFT
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 6))

ax1.plot(t, data, 'k', label='Original Data')
# Moving average filter
#ax1.plot(t[filter_length:], filtered_data, 'r', label='Filtered Data')
#ax1.set_title(f'Signal vs. Time (Filter Length: {filter_length})')
ax1.plot(t, filtered_data, 'r', label='Filtered Data')
ax1.set_title(f'Signal vs. Time (A = {A}, B = {B})')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax1.legend()

# Use loglog for the FFT plots
ax2.loglog(fft_freqs[fft_freqs >= 0], np.abs(fft_data[fft_freqs >= 0]), 'k', label='Original FFT')
ax2.loglog(fft_filtered_freqs[fft_filtered_freqs >= 0], np.abs(fft_filtered_data[fft_filtered_freqs >= 0]), 'r', label='Filtered FFT')
ax2.set_title('FFT')
ax2.set_xlabel('Frequency (Hz)')
ax2.set_ylabel('Magnitude')
ax2.legend()

plt.tight_layout()
plt.show()

print(f"Number of data points: {num_data_points}")
print(f"Total time: {total_time}")
print(f"Sample rate: {sample_rate} Hz")