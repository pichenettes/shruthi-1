import numpy

k = 1.0e3
m = 1e-3
u = 1e-6
n = 1e-9

# Measurements
# 55.6mV -> 55 Hz
# 0mV -> 440 Hz
# -35.2mV -> 1760 Hz

# Obviously depends on the small / big resistor values and cap values here,
# and room temperature of course.
def IR3109CvToFreq(cv):
  return 1760 / 2 ** ((cv + 0.0352) / (0.0556 + 0.0352) * 5)


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

def CvScaler(x):
  return Divide(
      -R_feedback * (x / R_input + vee / R_bias),
      R_divide_ground,
      R_divide_output)
  

vcc = 5.0
vee = -5.0
gnd = 0.0

R_input = 33 * k
R_bias = 78.0 * k
R_feedback = 5.6 * k

R_divide_ground = 2.0 * k
R_divide_output = 6.8 * k

print IR3109CvToFreq(CvScaler(0)), cutoff_min
print IR3109CvToFreq(CvScaler(5)), cutoff_max