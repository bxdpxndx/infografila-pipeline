#!/usr/bin/env python
import sys, os
import subprocess
import shutil
import glob

cameras = [cam for cam in os.listdir('camera') if cam.endswith('.cam')]

os.makedirs('tmp')
try:

    for cam in cameras:
        call = ['./renderer', sys.argv[1], os.path.join('camera',cam), os.path.join('tmp', "".join(['view', cam[:-4], '.tga']))]
        print (" ".join(call))
        subprocess.call(call)

    print("Converting to GIF")
    command = sorted(glob.glob('tmp/*'))
    command.insert(0, 'convert')
    command.append(sys.argv[2])
    subprocess.call(command)

finally:
    shutil.rmtree('tmp')



