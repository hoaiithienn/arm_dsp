# Section 4: Quantization and sampling theorem

## Definitions

- Quantization:
    - Sample and Hold: converts x-axis value to discrete ones. 
    - Quantizer: converts y-axis values to discrete ones.

- Proper sampling: Nyquist theorem: fs >= 2*fmax

## DSP system satisfying Nyquist theorem

- Analog Filter: Low-pass anti-aliasing filter
- ADC
- Digital Processor
- DAC 
- Analog Filter: Low-pass reconstruction filter

## Passive lowpass filter

- RC Lowpass Filter: Vin ---- R ---- Vout ---- C ---- GND
    
- A naive explanation:
    - At low frequency, capacitor becomes open-circuit --> Allow low-frequency components to pass through.
    - At high frequency, capacitor becomes short-circuit --> Block high-frequncy components from passing through. 

- Cutoff frequency: -3dB point = 50% power reduction

- Passband, stopband

## Passive highpass filter

- RC Highpass Filter: Vin ---- C ---- Vout ---- R ---- GND

- A naive explanation:
    - At low frequency, capacitor becomes open-circuit --> Block low-frequency components from passing through.
    - At high frequency, capacitor becomes short-circuit --> Allow high-frequency components to pass through. 

- Ideal filter
    - Other name: Brick wall filter

    - No transition frequency band

## Active filter

- Contains: opamp, transistors

- Can amplify signal

## Filter configuration

- Example: Chebyshev, Butterworth, Bessel

- More poles, more electronics, more performance

## Modified Sallen-Key filter

- A building block for active filters.

## Chebyshev filter

- Frequency domain:
    - Sharpest roll-off (i.e the faster frop in amplitude in a frequency response)
    - There are ripples in the passband

- Time domain:
    - Overshoot and oscillation slowly decreasing in amplitude


## Butterworth filter

- Frequency domain:
    - Flattest passband
    - Optimize to have the sharpest roll-off possible without allowing ripple in the passband

- Time domain:
    - Overshoot and oscillation slowly decreasing in amplitude, but less than that of Chebyshev

## Bessel filter

- Frequency domain:
    - Worst roll-off

- Time domain:
    - No overshoot and oscillation. Best step response

## Step response

- Meaning: How the filter respond when the input rapidly changes