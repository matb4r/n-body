# N-body simulator

This simulator is the effect of [engineering thesis](https://github.com/matb4r/praca-inzynierska).

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/Qwm_4tMCfNU/0.jpg)](https://www.youtube.com/watch?v=Qwm_4tMCfNU)

Compile:
```
g++ main.cpp -lGL -lGLEW -lglfw -ltbb -lSOIL -o nbody
```

Parameters:

|Parameter|Default|Description|
|-------------|-------------|-------------|
|-n|600|Number of particles|
|-m|0.01|Mass of particles|
|-r|1.0 0.3 0.1|Color of particles|
|-l|0|Initial position mode|
|-c|1|Computing mode|
|-d|800 600|Window width & height|
|-f|-|Fullscreen mode|
|-h|-|Print help|

Mouse:

| Action        | Effect           |
| ------------- |-------------|
|Move|Change orientation of the camera|
|Scrolling|Change field of view|

Keyboard:

| Key        | Effect           |
| ------------- |-------------|
|W|Move the camera forward|
|S|Move the camera backward|
|A|Move the camera left|
|D|Move the camera right|
|SPACE|New particles|
|Z|Spherical mode|
|X|Gauss mode|
|C|Cubic mode|
|F1|Sequential computing mode|
|F2|Parallel computing mode|
|Q|Decrease the mass of particles|
|E|Increase the mass of particles|
|I|Print info|
|ESC|Close simulator|
