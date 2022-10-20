import sys
import os
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 1234))

# Adam
#s.send(b'loadPlugin("G:/UD1447/Maya22-Gameplay3D/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')                      # Home

# Oliv
#s.send(b'loadPlugin("C:/Users/Oliver/source/repos/Maya22-Gameplay3D/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')  # Home
#s.send(b'loadPlugin("C:/Users/Olive/source/repos/Maya22-Gameplay3D/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')   # Laptop
#s.send(b'loadPlugin("C:/Users/a/source/repos/Maya22-Gameplay3D/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')       # School

# Examination path:
#s.send(b'loadPlugin("[YOUR PATH HERE]/Maya22-Gameplay3D/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')  # Examinator

s.close()