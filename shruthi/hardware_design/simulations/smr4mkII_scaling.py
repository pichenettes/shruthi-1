import numpy

k = 1.0e3
m = 1e-3
u = 1e-6
n = 1e-9
VT = 26 * m
GM = 1 / (2 * VT)


def MidiToHertz(note):
  return 440.0 * 2 ** ((note - 69) / 12.0)


tracking_factor = 1.822  # Fifth
cutoff_min = MidiToHertz(0) * tracking_factor
cutoff_max = MidiToHertz(127) * tracking_factor
print 'Target cutoff range: ', cutoff_min, cutoff_max


def Parallel(a, b):
  return 1 / (1 / a + 1 / b)

def Divide(x, a, b):
  return x * a / (a + b)

# vee = -5.0
# gnd = 0.0
# num_poles = 4
# 
# r_cutoff_cv_input = 47 * k
# r_cutoff_negative_trim = 150 * k
# r_cutoff_feedback = 2.2 * k
# r_current_source = 330 * k


# Another variant with a negative voltage reference obtained with a Zener
# vee = -4.7
# gnd = 0.0
# num_poles = 4
# 
# r_cutoff_cv_input = 57.2 * k
# r_cutoff_negative_trim = 150 * k
# r_cutoff_feedback = 2.2 * k
# r_current_source = 330 * k

# Another variant with a 4.7V Zener for offset and a 2.5V wide CV
vee = -4.7
gnd = 0.0
num_poles = 4

r_cutoff_cv_input = 56 * k
r_cutoff_negative_trim = 330 * k
r_cutoff_feedback = 4.7 * k
r_current_source = 330 * k

# Voltage divider resistors in filter stages.
r_small = 220.0
r_big = 10 * k
c = 1 * n
r_input = Divide(1.0, Parallel(r_small, r_big), r_big)

def RcCutoff(r, c):
  return 1 / (2 * numpy.pi * r * c)

def Cutoff(i_con):
  return GM * i_con * r_input / (2 * numpy.pi * c)

def CutoffToIcontrol(cutoff):
  return 2 * numpy.pi * c * cutoff / (GM * r_input)

def CvPostToIcontrol(cv):
  return -vee / r_current_source * numpy.exp(- cv / VT)

def IControlToCvPost(i_con):
  return -numpy.log(i_con / (-vee / r_current_source)) * VT
  
def CvPreToCvPost(cv):
  return -r_cutoff_feedback / r_cutoff_cv_input * cv + \
      -r_cutoff_feedback / r_cutoff_negative_trim * vee

i_min = CutoffToIcontrol(cutoff_min)
i_max = CutoffToIcontrol(cutoff_max)
# print 'Expected control current range:', i_min, i_max

print CvPostToIcontrol(CvPreToCvPost(5.0)) * 1000

min_cutoff = Cutoff(CvPostToIcontrol(CvPreToCvPost(0.0)) / num_poles)
max_cutoff = Cutoff(CvPostToIcontrol(CvPreToCvPost(2.5)) / num_poles)
# max_cutoff = Cutoff(0.003 / num_poles)
print max_cutoff / min_cutoff, 2 ** (128.0 / 12), min_cutoff, max_cutoff
