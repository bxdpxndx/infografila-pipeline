#!/usr/bin/env python
from math import pi, cos, sin

def linspace(low, high, leng):
    step = ((high-low) * 1.0 / leng)
    return [low+i*step for i in xrange(leng)]

dist = 3

lookat = [0.5, 0.5, 0.5]

for index, angle in enumerate(linspace(0, 2 * pi, 24)):
    f = open( str(index).zfill(4) + '.cam', 'w')
    f.write(' '.join(str(x+y) for x,y in zip([dist * sin(angle), -1.5, dist * cos(angle)], lookat)))
    f.write('\n')
    f.write(' '.join(str(x) for x in lookat))
    f.write('\n')
    f.close()
