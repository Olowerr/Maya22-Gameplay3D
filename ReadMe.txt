What you have to do to run the program:

1. Go into loadPlugin.py and change the "s.send" line to your path ending with "/Maya22-Gameplay3D/MayaPlugin/build/x64/Debug/UD1447Project.mll".
There is a premade commented "#s.send" for the examinator to put in their own path.

2. Build the "MayaAPI" to run the plugin.

3. Run the program with "MayaScene" as the startup project.

4. If you want to build the plugin "MayaAPI" while "MayaScene" is already running you have to go into maya -> Windows - > Settings/Preferences -> Plug in Manager
And search for the UD1447Project.mll file. Remember that you will need to build the "MayaAPI" first to get the file to start with.