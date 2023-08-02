# Section 5: Overview of Arm Cortex-M DSP Support Features

- Digital Signal Controller: 
    - a combination of a Microcontroller and a Digital Signal Processor
    - Example: ARM Cortex M4, M7, M33, M23

- Floating Point Unit (FPU): 
    - A type of coprocessor that can execute instructions for the floating point arithmetic in a few cycles.
    - Consists of control, status and 32 single precision registers.
    - 32 32-bit register (single precision) ~ 16 64-bit register (double precision)

- Single Instruction Multiple Data (SIMD):
- Multiply Accumulate (MAC): product 2 numbers then add them in a single instruction. 
- CMSIS-DSP: 
    - ARM DSP library
    - Datatype: Signed Int, Unsigned Int, Float and Fraction (q7_t, q15_t, q31_t, q63_t)
