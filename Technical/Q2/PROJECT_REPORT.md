# Audio Signal Recovery from Corrupted WAV
---
 Objective

Recover the original audio signal from a corrupted .wav file using signal processing techniques.
The transformations applied to the signal were unknown and had to be inferred through analysis.

🧠 Approach

The task was approached as a step-by-step investigation, where each stage of analysis revealed the next issue in the signal. FFT and filtering techniques were used as primary tools.

🔍 Stage 1 — Understanding the Received Signal
📊 Actions Performed:
Loaded the corrupted signal
Plotted the signal in the time domain
Computed and plotted its FFT
🔎 Observations:
Time-domain signal appeared highly oscillatory and not like natural audio
FFT showed that energy was concentrated around ~7 kHz, not near 0 Hz
🧠 Conclusion:
Since normal speech lies in 0–4 kHz, the signal was not in baseband
This indicated that the signal had been frequency shifted (modulated)
🔄 Stage 2 — Frequency Recovery (Demodulation)
📊 Actions Performed:
Identified carrier frequency (~7 kHz) from FFT peak
Multiplied the signal with a cosine wave of the same frequency
🔎 Observations:
Signal energy returned to 0–4 kHz
Additional components appeared around ~14 kHz
🧠 Explanation:
Demodulation creates:
Desired signal (baseband)
Unwanted high-frequency component (2 × carrier)
🧠 Conclusion:
The signal had undergone amplitude modulation
Demodulation successfully brought it back to baseband
🧹 Stage 3 — Noise and Interference Removal
📊 Actions Performed:
Computed FFT after demodulation
Identified narrow spikes in frequency domain
🔎 Observations:

Spikes detected at approximately:

891 Hz
2486 Hz
3783 Hz

Later, an additional dominant tone:

~300 Hz
🧠 Interpretation:
These spikes represent narrowband interference
Not part of natural speech (which has smooth spectrum)
🔧 Method Used:
Applied notch filters at detected frequencies
Used multiple nearby frequencies to widen removal band
🧠 Result:
Spikes significantly reduced
Spectrum became smoother and more speech-like
⚠️ Stage 4 — Residual Distortion (Phase Issue)
📊 Observations:
FFT appeared correct after filtering
However, audio still sounded:
distorted
metallic
had background tone
🧠 Key Insight:
FFT magnitude only shows amplitude
It does NOT capture phase information
🧠 Conclusion:
The remaining distortion is due to phase corruption
🔧 Attempts to Fix:
Signal normalization
Signal inversion
Envelope detection using Hilbert transform
📉 Result:
Partial improvement
Distortion still present
📊 Results
✅ Successfully achieved:
Identified and reversed frequency shift
Removed narrowband interference
Recovered baseband signal
⚠️ Limitation:
Phase distortion could not be fully corrected
🔊 Final Output
Recovered audio file: recovered.wav
Audio is intelligible but contains minor residual distortion
🛠️ Tools Used
Python
NumPy
SciPy
Matplotlib
Google Colab
⚠️ Challenges Faced
Identifying carrier frequency from FFT
Designing filters without damaging speech
Removing tonal noise (~300 Hz)
Handling phase distortion not visible in FFT
🚀 Future Improvements
Phase reconstruction techniques
Adaptive filtering
Advanced denoising (e.g., spectral subtraction)
📌 Conclusion

The corrupted signal was successfully analyzed and partially restored using DSP techniques.
While frequency-domain distortions were effectively corrected, residual phase distortion highlighted the importance of phase information in accurate signal reconstruction.

▶️ How to Run
Upload Signals_corrupted.wav in Google Colab
Run the notebook step-by-step
View plots and listen to output audio
