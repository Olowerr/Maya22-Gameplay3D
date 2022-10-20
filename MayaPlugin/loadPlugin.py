import sys
import os
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 1234))

# Examination path:
s.send(b'loadPlugin("[YOUR PATH HERE]/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')  # Examinator

# EXAMPLES:

# Adam
#s.send(b'loadPlugin("G:/UD1447/UD1447_Project_Oliver_Klingspor_Adam_Akesson/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n')                    

# Oliv
#s.send(b'loadPlugin("C:/Users/Oliver/source/repos/UD1447_Project_Oliver_Klingspor_Adam_Akesson/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n') 
#s.send(b'loadPlugin("C:/Users/Oliver/Desktop/UD1447_Project_Oliver_Klingspor_Adam_Akesson/MayaPlugin/build/x64/Debug/UD1447Project.mll")\n') 

s.close()