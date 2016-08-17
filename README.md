IM Spacing Sweep
================

A utility for measuring two-tone intermodulation by sweeping tone spacing. This application works with Rohde &amp; Schwarz Vector Network Analyzers (VNAs).

A binary version of this utility with installation instructions can be found at:  
https://vna.rs-us.net/applications

Requirements
============
This project was created with Qt5 and relies on Qt Creator. It also relies heavily on the RsaToolbox library found here:  
https://github.com/Terrabits/RsaToolbox

To build this project, first build RsaToolbox into a shared library in Qt Creator, then build this project in Qt Creator as well. This project was written for and tested exclusively in Windows environments running Windows XP and later. It should compile to other platforms as well, but it might take some effort. Some of the groundwork to compile for MacOS is in place. Linux has never been attempted.

Version History
===============

- 1.0 Initial release  
    1.0.1  
    - ZVA: Handle source and receiver arbitrary frequencies separately
    - ZVA: Added option for using internal coupler

Frequency conversion SCPI commands
==================================
Intermod measurement with fixed center frequency and swept tone distance is not currently available on the VNA. This must be implemented in software via SCPI commands and with the frequency conversion settings on a per-port and per-channel-and-trace basis.

- Source permanently on  
  `SOUR<Ch>:POW<Port>:PERM          [0/1]`  
  `SOUR<Ch>:POW<Ignore>:GEN<i>:PERM [0/1]`
- Source frequency conversion  
  `SOUR<Ch>:FREQ<Port>:CONV:ARB:IFR                  <Numerator>, <Denominator>, <Offset>, <SweepType>`  
  `SOUR<Ch>:FREQ<Ignore>:CONV:ARB:EFR<Gen> <On/Off>, <Numerator>, <Denominator>, <Offset>, <SweepType>`
- Receiver frequency conversion (ZVA only)
  `SENS<Ch>:FREQ:CONV:ARB                            <Numerator>, <Denominator>, <Offset>, <SweepType>`

Where:  
- `f = (Numerator / Denominator) * fb + Offset`
- `SweepType` = `SWE` (arbitrary frequency is an array calculated from fb)
- On the ZVA the source and receiver can be set independently
- On the ZNB the `SOUR:FREQ:PORT:CONV:ARB:IFR` command sets both the source and receiver for that port simultaneously
- The (ZVA) receiver frequency command applies to all ports (unlike the port specific source command)


Frequency conversion channel settings
=====================================

Definitions
-----------
`fc = center frequency`  
`fd = tone distance`  

Channel base frequency
----------------------
`fb = -fc - 1/2*fd`

Frequency conversion
--------------------
| Position | Order | Numerator | Denominator | Offset   | Note                 |
|----------|-------|-----------|-------------|----------|----------------------|
| Lower    | 1     |  N/A      | N/A         | N/A      | = fb = fc - 1/2 * fd |
| Lower    | N     |  N        | 1           | (1-N)*fc | N >= 3, N odd        |
| Upper    | N     | -N        | 1           | (1+N)*fc | N >= 1, N odd        |

Measurement Types
=================

definitions
-----------

### Type
T  = tone
IM = Intermod
R  = Relative
IP = Intercept Point

### Feature
L = Lower
U = Upper
M = Major (max)

### Location
O  = Output
I  = Input

Traces
------

| Type | Features | Locations | Examples       |
|------|----------|-----------|----------------|
| T    | L, U     | I, O      | LTI,    UTO    |
| IM   | L, U, M  | O         | IM3LO,  IM5MO  |
| IM R | L, U, M  | O         | IM3LOR, IM7MOR |
| IP   | L, U, M  | I, O      | IP3LO,  IP9MI  |

Relative Intermod Definition
----------------------------
`IMR[n] dB = LTO dBm - IM[n] dBm`


Intercept Point Definition
--------------------------
`IP[n] dBm = LT dBm  + IMR[n] dB / (n-1)`
