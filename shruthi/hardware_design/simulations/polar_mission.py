import pylab
import numpy

f = 20 * (2 ** numpy.linspace(0, 10.0, 1000))
w = 2 * numpy.pi * f
R = 33000.0
C = 220e-12
f_cv = 1
s = 1j * w * R * C / (10 ** (-1.5 * f_cv))

def response(a, b, c, d, lp1):
  if lp1:
    t = a / (1 + s) - b / (1 + s) ** 2 + c / (1 + s) ** 3 - d / (1 + s) ** 4
  else:
    t = a - b / (1 + s) + c / (1 + s) ** 2 - d / (1 + s) ** 3
  return t

settings = [
  (0, 0, 0, 1),  # 4LP / 3LP
  (0, 1, 0, 0),  # 2LP / 1LP
  (1, 1, 0, 0),  # 2BP / 1HP
  (1, 2, 1, 0),  # 2HP 1LP / 2HP
  (1, 3, 3, 1),  # 3HP 1LP / 3HP
  (0, 1, 2, 1),  # 4BP / 2HP 1LP
  (1, 2, 2, 0),  # 2NO 1LP / 2NO
  (1, 3, 6, 4),  # 3AP + 1LP 1LP / 3AP + 1LP
]

pylab.figure(figsize=(8, 16))
k = 0
for i in xrange(8):
  for j in xrange(2):
    pylab.subplot(8, 2, 1 + i * 2 + j)
    a, b, c, d = settings[i]
    lp1 = 1 - j
    t = response(a, b, c, d, lp1)
    pylab.semilogx(f, 20 * numpy.log10(abs(t)).T)
    axes = pylab.gca()
    pylab.semilogx(f, (numpy.angle(t) + numpy.pi) % (2 * numpy.pi), 'g')
    axes.set_ylim(-60, 10)
pylab.savefig('response.pdf')
