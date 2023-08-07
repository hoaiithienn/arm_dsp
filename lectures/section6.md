# Section 6: Linear System and Superpositions

## Definitions

- Signal
- Notation: 
    - x(t), y(t): Continuous time domain
    - x[t], y[t]: Discrete time domain
    - X(f): Continuous frequency domain
    - X[f]: Discrete frequency domain

## Properties of a linear system

- Homogeneity:

    - If output y[n] of a system is produced by an input x[n], then k\*y[n] will correspond to the input k\*x[n].

- Additivity:

    - y<sub>1</sub>[n] is the output of x<sub>1</sub>[n]
    - y<sub>2</sub>[n] is the output of x<sub>2</sub>[n]
    - Then  y<sub>1</sub>[n] + y<sub>2</sub>[n] is the output of  x<sub>1</sub>[n] + x<sub>2</sub>[n]

- Shift invariance:

    - If output y[n] of a system is produced by an input x[n], then y[n + s] will correspond to the input x[n + s], s is the shift of samples.

## Superposition

- Response of a sum of signal is the sum of all responses of each individual input signal

- Synthesis and decomposition

## Impulse decompositions

- Break N samples signal into N component signals, each containing N samples (1 sample from the original, the rest N - 1 samples are zeroes).

## Step decompositions

- Break N samples signal into N component signals, each containing N samples.

- Consider the decomposition of an N point signal, x[n], into the components: x<sub>0</sub>[n], x<sub>1</sub>[n], x<sub>2</sub>[n], …, x<sub>N-1</sub>[n]. The kth component signal, x<sub>k</sub>[n], is composed of zeros for points 0 through (k - 1), while the remaining points have a value of: x[k] - x[k-1]. [(Ref)](https://www.dspguide.com/ch5/7.htm)

