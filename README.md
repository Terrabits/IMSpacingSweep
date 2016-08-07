TwoToneSweep
==============

A utility for measuring two-tone intermodulation by sweeping tone spacing. This application works with Rohde &amp; Schwarz Vector Network Analyzers (VNAs).

A binary version of this utility with installation instructions can be found at:  
https://vna.rs-us.net/applications

Requirements
============
This project was created with Qt5 and relies on Qt Creator. It also relies heavily on the RsaToolbox library found here:  
https://github.com/Terrabits/RsaToolbox

To build this project, first build RsaToolbox into a shared library in Qt Creator, then build this project in Qt Creator as well. This project was written for and tested exclusively in Windows environments running Windows XP and later. It should compile to other platforms as well, but it might take some effort. Some of the groundwork to compile for MacOS is in place. Linux has never been attempted.

Intermod (vs center frequency) SCPI commands
============================================
This measurement (intermod with fixed tone distance, sweeping center frequency) is already available on the instrument. You can ask via SCPI for these measurements and results directly.  

Channel setup
-------------
- Lower tone port  
  `SENS<Ch>:FREQ:IMOD:LTON <source_type>, <source_port>`
- Upper tone port  
  `SENS<Ch>:FREQ:IMOD:UTON PORT, <source_index>`
- Upper tone generator  
  `SENSe<Ch>:FREQuency:IMODulation:UTONe GEN,  <source_index>`
- Receiver port  
  `SENSe<Ch>:FREQuency:IMODulation:RECiever    <port>`
- Tone spacing  
  `SENSe<Ch>:FREQuency:IMODulation:TDIStance   <frequency>`
- Enable order measurement  
  `SENSe<Ch>:FREQuency:IMODulation:ORDer<order>[:STATe] ON`
- Turn off intermod
  `SENSe<Ch>:FREQuency:IMODulation:CONV OFF`

Trace setup
-----------
- Tone  
  `CALCulate<Ch>:PARamater:SDEFine '<trace_name>','<side>T<at: I/O>'`
- Intermod  
  `CALCulate<Ch>:PARamater:SDEFine '<trace_name>','IM<order><side>O'`
- Intercept point  
  `CALCulate<Ch>:PARamater:SDEFine '<trace_name>','IP<order><side>O'`
- Intermod suppression  
  `CALCulate<Ch>:PARamater:SDEFine '<trace_name>','IM<order><side>OR'`

Frequency conversion SCPI commands
==================================
Intermod measurement with fixed center frequency and swept tone distance is not currently available on the VNA. This must be implemented in software via SCPI commands and with the frequency conversion settings on a per-port and per-channel-and-trace basis.

- Source permanently on  
  `SOUR<Ch>:POW<Port>:PERM          [0/1]`  
  `SOUR<Ch>:POW<Ignore>:GEN<i>:PERM [0/1]`
- Source frequency conversion  
  `SOUR<Ch>:FREQ<Port>:CONV:ARB:IFR                  <Numerator>, <Denominator>, <Offset>, <SweepType>`  
  `SOUR<Ch>:FREQ<Ignore>:CONV:ARB:EFR<Gen> <On/Off>, <Numerator>, <Denominator>, <Offset>, <SweepType>`

Where:  
`f = (Numerator / Denominator) * fb + Offset`


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
