#!/usr/bin/env python3

from subprocess import Popen, PIPE

file = 'simple_example.pad'

print(f'Evaluate {file}')

for numUserLayers in range(33):
    for unknownFlag in [True, False]:
        for additionalStr2 in range(33):
            cmd = ['./build/OpenAllegroParser', '-i', file]

            if numUserLayers > 0:
                cmd += ['--numUserLayers', f'{numUserLayers}']

            if unknownFlag:
                cmd += ['--unknownFlag']

            if additionalStr2 > 0:
                cmd += ['--additionalStr2', f'{additionalStr2}']

            print('Testing command ' + ' '.join(cmd))

            p = Popen(cmd, stdout=PIPE, stderr=PIPE)
            stdout, stderr = p.communicate()
            code = p.returncode

            if code == 0:
                print()
                print('---------------------------------------------')
                print('------- Found valid Parameter Set -----------')
                print('---------------------------------------------')
                print()
                print(' '.join(cmd))
                exit(0)

print('No valid parameter set found!')