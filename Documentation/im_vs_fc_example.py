from rohdeschwarz.instruments.vna import Vna
vna = Vna()
vna.open_tcp()
vna.open_log("SCPI Log.txt")

vna.preset()
vna.pause()

vna.channel().start_frequency_Hz =   1,'GHz'
vna.channel().stop_frequency_Hz  =   1,'GHz'
vna.channel().points             =   1

vna.write("SENS:BAND:SEL HIGH")

vna.write("SENS:FREQ:IMOD:TDIS       1 MHz")
vna.write("SENS:FREQ:IMOD:LTON PORT, 1    ")
vna.write("SENS:FREQ:IMOD:UTON PORT, 3    ")
vna.write("SENS:FREQ:IMOD:REC        2    ")
vna.write("SENS:FREQ:IMOD:ORD3       ON   ")
vna.write("SENS:FREQ:IMOD:ORD5       ON   ")

vna.trace("Trc1").parameter = "LTI"
lti_name   = "Trc1"
uti_name   = vna.create_trace(parameter="UTI")
lto_name   = vna.create_trace(parameter="LTO")
uto_name   = vna.create_trace(parameter="UTO")

im3lo_name = vna.create_trace(parameter="IM3LO")
im3uo_name = vna.create_trace(parameter="IM3UO")
im3mo_name = vna.create_trace(parameter="IM3MO")

im5lo_name = vna.create_trace(parameter="IM5LO")
im5uo_name = vna.create_trace(parameter="IM5UO")
im5mo_name = vna.create_trace(parameter="IM3MO")

#vna.trace(lti_name).diagram = 1
vna.trace(uti_name).diagram = 1
vna.trace(lto_name).diagram = 1
vna.trace(uto_name).diagram = 1

vna.trace(im3lo_name).diagram = 1
vna.trace(im3uo_name).diagram = 1
vna.trace(im3mo_name).diagram = 1

vna.trace(im5lo_name).diagram = 1
vna.trace(im5uo_name).diagram = 1
vna.trace(im5mo_name).diagram = 1