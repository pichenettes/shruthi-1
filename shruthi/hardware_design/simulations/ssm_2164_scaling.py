import numpy

"""
Solution with 5k trimmer:

R_input = 47 * k
R_bias = 47 * k
R_feedback = 22.0 * k

R_divide_ground = 47.0 * k
R_divide_output = 2.2 * k


With 2.0k trimmer:
R_divide_ground = 68.0 * k
R_divide_output = 5.6 * k

"""

k = 1.0e3
m = 1e-3
u = 1e-6
n = 1e-9
p = 1e-12

filter_r = 33 * k
filter_c = 220 * p

def SSM2164CvToFreq(cv):
  max_cutoff = 1 / (2 * numpy.pi * filter_r * filter_c)
  return max_cutoff * 10 ** (-1.5 * cv)


def MidiToHertz(note):
  return 440.0 * 2 ** ((note - 69) / 12.0)


tracking_factor = 1.5  # Fifth
cutoff_min = MidiToHertz(0) * tracking_factor
cutoff_max = MidiToHertz(127) * tracking_factor

def Parallel(a, b):
  return 1 / (1 / a + 1 / b)


def Divide(x, a, b):
  return x * a / (a + b)


def CvScaler(x):
  return -R_feedback * (x / R_input + vee / R_bias)
  

vcc = 5.0
vee = -5.0
gnd = 0.0

R_input = 35.3 * k
R_bias = 34.6 * k 
R_feedback = 15.0 * k

print SSM2164CvToFreq(CvScaler(0)), cutoff_min
print SSM2164CvToFreq(CvScaler(5)), cutoff_max

ideal_gain = (2.168-0.04425) / 5
