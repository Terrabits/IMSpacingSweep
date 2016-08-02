TwoToneSweep
==============

A utility for measuring two-tone intermodulation by sweeping tone spacing. This application works with Rohde &amp; Schwarz Vector Network Analyzers (VNAs).

A binary version of this utility with installation instructions can be found at:  
https://vna.rs-us.net/applications


Intermod (vs center frequency) SCPI commands
============================================
This measurement (intermod with fixed tone distance, sweeping center frequency) is already available on the instrument. You can ask via SCPI for these measurements and results directly.  

Channel setup
-------------
- Lower tone port  
  SENSe<Ch>:FREQuency:IMODulation:LTONe <source_type>, <source_port>
- Upper tone port  
  SENSe<Ch>:FREQuency:IMODulation:UTONe PORT, <source_index>
- Upper tone generator  
  SENSe<Ch>:FREQuency:IMODulation:UTONe GEN,  <source_index>
- Receiver port  
  SENSe<Ch>:FREQuency:IMODulation:RECiever    <port>
- Tone spacing  
  SENSe<Ch>:FREQuency:IMODulation:TDIStance <frequency>
- Enable order measurement  
  SENSe<Ch>:FREQuency:IMODulation:ORDer<order>[:STATe] ON
- Turn off intermod
  SENSe<Ch>:FREQuency:IMODulation:CONV OFF

Trace setup
-----------
- Tone  
  CALCulate<Ch>:PARamater:SDEFine '<trace_name>','<side>T<at: I/O>'
- Intermod  
  CALCulate<Ch>:PARamater:SDEFine '<trace_name>','IM<order><side>O'
- Intercept point  
  CALCulate<Ch>:PARamater:SDEFine '<trace_name>','IP<order><side>O'
- Intermod suppression  
  CALCulate<Ch>:PARamater:SDEFine '<trace_name>','IM<order><side>OR'

Frequency conversion SCPI commands
==================================
Intermod measurement with fixed center frequency and swept tone distance is not currently available on the VNA. This must be implemented in software via SCPI commands and with the frequency conversion settings on a per-port and per-channel-and-trace basis.

- Source permanently on  
  SOUR<Ch>:POW<Port>:PERM          [0/1]  
  SOUR<Ch>:POW<Ignore>:GEN<i>:PERM [0/1]
- Source frequency conversion  
  SOUR<Ch>:FREQ<Port>:CONV:ARB:IFR                  <Numerator>, <Denominator>, <Offset>, <SweepType>  
  SOUR<Ch>:FREQ<Ignore>:CONV:ARB:EFR<Gen> <On/Off>, <Numerator>, <Denominator>, <Offset>, <SweepType>

Where:  
f = (Numerator / Denominator) * fb + Offset


Frequency conversion channel settings
=====================================

Definitions
-----------
fc = center frequency  
fd = tone distance  

N-prime:  
Np = (N + 1)/2

Channel base frequency
----------------------
fb = -fc - 1/2*fd

Frequency conversion
--------------------
| Position | Order | Numerator | Denominator | Offset    | Note                 |
|----------|-------|-----------|-------------|-----------|----------------------|
| Lower    | 1     |  N/A      | N/A         | N/A       | = fb = fc - 1/2 * fd |
| Lower    | N     | -Np       | 1           | (1-Np)*fc | N >= 3, N odd        |
| Upper    | N     |  Np       | 1           | (1+Np)*fc | N >= 1, N odd        |
