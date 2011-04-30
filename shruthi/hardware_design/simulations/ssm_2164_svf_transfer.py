import pylab
import numpy

f = 20 * (2 ** numpy.linspace(0, 10.0, 1000))
w = 2 * numpy.pi * f

Rg = 33000.0
Ri = 33000.0
Rq = 15000.0
# Rb = 22000.0
R = 33000.0
C = 220e-12


def transfer(f_cv, q_cv, w, output):
  s = 1j * w
  
  alpha = -1 / (R * C * s) * 10 ** (-1.5 * f_cv)
  # beta = Rb / R * 10 ** (-1.5 * q_cv)
  beta = (10 ** (-1.5 * q_cv)) * Rg / Rq

  g = Rg / Ri
  # q = 1 / (2 + g) * 1.0 / beta
  q = 1.0 / beta
  wc = 1 / (R * C) * (10 ** (-1.5 * f_cv))

  lp = -g / (s ** 2 / wc ** 2 + s / w * 1 / q + 1)
  bp = lp / alpha
  hp = bp / alpha
  
  return [lp, bp, hp][output]


params = {'text.usetex': True}
pylab.rcParams.update(params)

if __name__ == '__main__':
  num_freqs = 5
  num_q = 4
  pylab.figure(figsize=(16, 12))
  for mode in xrange(3):
    for row, q_cv in enumerate(numpy.linspace(0, 2.0, num_q)):
      pylab.subplot(num_q, 3, mode + row * 3 + 1)
      t = numpy.zeros((num_freqs, f.shape[0]), dtype=numpy.complex)
      for f_index, f_cv in enumerate(numpy.linspace(0.5, 2.0, num_freqs)):
        t[f_index, :] = transfer(f_cv, q_cv, w, mode)
      pylab.semilogx(f, 20 * numpy.log10(abs(t)).T)
      if mode == 0:
        pylab.ylabel(('$|H(2\pi j f)| (dB)$'))
      if row == num_q - 1:
        pylab.xlabel(('$f (Hz)$'))
  F = pylab.gcf()
  pylab.savefig('curves.pdf', dpi=300)
