# TANK-WARS
2D game made in c++ &amp; OpenGl using Object Oriented Programming\
WELCOME TO TANK WARS\
It is a 2 Players Game which is played on the same Device
 
 ## Requirements
 openGl libraries(glut.h),C++ compiler
 
 ## HOW TO RUN
 1.) If you are using Visual Studio the run the .sln file\
 2.) For those who are not using visual studio go to folder "TankWars"\
     compile the file "TankWars.cpp" using the command\
     g++ TankWars.cpp -lglut -lGL -lGLU
 
 #### MOTIVE:
 You need to destroy other Player in Arena,you can Shoot Bullets to Destroy Other Player
 
 ##### RAGE MODE:
 This game contain Rage Mode when your health drops to minimum then Rage\
 mode is activated.This Mode gives you ability to shoot Powerful and Fast Bullets.\
 RAGE IS ON...
 
 #### CONTROLS:
Player1:\
w := move Up\
s := move Down\
a := move Left\
d := move Right\
space := Shoots

Player2:\
up_arrow    := move Up\
down_arrow  := move Down\
left_arrow  := move Left\
right_arrow := move Right\
enter       := Shoots

p   := pause/play\
esc := exit

NOTE: If you want to custimize controls then check 'PlayerControls' function in "global.h"

NOTE: if you are not playing in 1355x720 resolution it is highly recommended to\
commment first line of 'ResetGame' Func in "global.h" and uncomment second line of this func\
in "global.h"

If you want to change Parameters of game like\
No. of bullets that Player Can Shoot you can Change That\
in "GameArea.h".\
Enjoy tweaking...

If you are not using Visual Studio Then You can Remove these Files\
1.)"Tank Wars.vcxproj"\
2.)"Tank Wars.vcxproj.filters"\
3.)"pch.cpp"\
4.)"pch.h"\
5.)remove line " #include "pch.h" " from "TankWars.cpp"

### THANKS FOR PLAYING
### I HOPE YOU ENJOYED THE GAME
