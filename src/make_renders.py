#!/usr/bin/env python
import os
import subprocess

# renders all upf files
objects = [(os.path.join('objects', obj), obj[:-4] + '.tga') for obj in os.listdir('objects') if obj.endswith('.upf')]


for obj in objects:
    call = ['./renderer', obj[0], 'camera/0000.cam', obj[1], '480', '480']
    subprocess.call(call)

