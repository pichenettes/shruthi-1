import numpy

k = 1.0e3
m = 1e-3
u = 1e-6
n = 1e-9
VT = 26 * m
GM = 1 / (2 * VT)


def MidiToHertz(note):
  return 440.0 * 2 ** ((note - 69) / 12.0)


tracking_factor = 1.5  # Fifth
cutoff_min = MidiToHertz(0) * tracking_factor
cutoff_max = MidiToHertz(127) * tracking_factor
print 'Target cutoff range: ', cutoff_min, cutoff_max


def Parallel(a, b):
  return 1 / (1 / a + 1 / b)

def Divide(x, a, b):
  return x * a / (a + b)

vcc = 5.0
dvcc = 5.0
gnd = 0.0
num_poles = 4


# Voltage divider resistors in filter stages.
r_small = 220.0
r_big = 10 * k
input_range = 25 * m * 2  #pp. x2 because the first stage has a higher R.

# Experimental, not from the datasheet
tl084_clipping = (7.6 / 8.0) * (vcc - 6) + 4.8
diode_drop = 0.7
# Filter stages capacitor.
c = 1 * n
r_input = Divide(1.0, Parallel(r_small, r_big), r_big)

# Resistor generating the reference current for the expo converter
r_current_source = 330 * k
r_current_clip = 2.2 * k

# Resistors in the audio op-amp gain scaling stage.
r_audio_input = 100 * k
r_audio_feedback = 47.0 * k
c_audio_input = 4.7 * u

# Resistor and caps in the cutoff scaling stage.
r_cutoff_cv_input = 33.00 * k
r_cutoff_negative_trim = 56.00 * k
r_cutoff_feedback = 5.6 * k
c_cutoff_feedback = 0.033 * u
r_cutoff_divider_big = 6.8 * k
r_cutoff_divider_small = 2.0 * k

audio_op_amp_gain = r_audio_feedback / r_audio_input

def RcCutoff(r, c):
  return 1 / (2 * numpy.pi * r * c)

def Cutoff(i_con):
  return GM * i_con * r_input / (2 * numpy.pi * c)

def CutoffToIcontrol(cutoff):
  return 2 * numpy.pi * c * cutoff / (GM * r_input)

def CvPostToIcontrol(cv):
  return vcc / r_current_source * numpy.exp(- cv / VT)

def CvPreToCvPost(cv):
  vout = sum([-vcc * r_cutoff_feedback / r_cutoff_negative_trim,
               cv * r_cutoff_feedback / r_cutoff_cv_input])
  return -Divide(vout, r_cutoff_divider_small, r_cutoff_divider_big)

def IControlToCvPost(i_con):
  return -numpy.log(i_con / (vcc / r_current_source)) * VT

def Near(a, b, tolerance=1.1):
  return numpy.abs(numpy.log(a / b)) < numpy.log(tolerance)

i_min = CutoffToIcontrol(cutoff_min)
i_max = CutoffToIcontrol(cutoff_max)
print 'imin', i_min
print 'imax', i_max

print 'Expected control current range:', i_min, i_max

# Check that the control current is within limits.
print 'Checking current...'
print i_max, i_min
assert i_max < 0.5 * m
assert i_min > 0.05 * u

# Check that the current limiting resistor will not allow very high cutoff
# values.
max_current = (tl084_clipping - diode_drop) / (num_poles * r_current_clip)
print 'Checking current limiting resistor...'
assert max_current > i_max
assert Cutoff(max_current) < 25000

# Check that the resistors around the audio op amp are reasonably sized
print 'Checking audio op amp gain...'
ideal_input_op_amp_gain = (input_range / r_input) / dvcc
print ideal_input_op_amp_gain
print audio_op_amp_gain
assert Near(audio_op_amp_gain, ideal_input_op_amp_gain, tolerance=1.2)
assert Near(RcCutoff(r_audio_input, c_audio_input), 1.0, tolerance=5.0)

# Check that the PWM crap is filtered from the cutoff CV
assert Near(RcCutoff(r_cutoff_feedback, c_cutoff_feedback), 1000, tolerance=1.5)

# Check that the CV scaling op-amp is correctly doing its job
print 'Checking cutoff frequencies...'
v_min = IControlToCvPost(CutoffToIcontrol(cutoff_min))
v_max = IControlToCvPost(CutoffToIcontrol(cutoff_max))
r_cutoff_cv_input_ideal = -dvcc / (v_max - v_min) * r_cutoff_feedback * Divide(
    1.0, r_cutoff_divider_small, r_cutoff_divider_big)
r_cutoff_negative_trim_ideal = dvcc / v_min * r_cutoff_feedback * Divide(
    1.0, r_cutoff_divider_small, r_cutoff_divider_big)
c_cutoff_min = Cutoff(CvPostToIcontrol(CvPreToCvPost(gnd)))
c_cutoff_max = Cutoff(CvPostToIcontrol(CvPreToCvPost(dvcc)))

print 'Estimate cutoff range for current choice of components:', \
    c_cutoff_min, c_cutoff_max
assert Near(c_cutoff_min, cutoff_min)
assert Near(c_cutoff_max, cutoff_max)
