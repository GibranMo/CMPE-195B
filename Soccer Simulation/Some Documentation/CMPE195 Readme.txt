This file was last edited: May 17, 2015

Use and Copyright:
-----------------
The files within this zip file are the intellectual property of Gibran Morales, 
Carlos Toledo, and Parag Pardeshi and may not be redistributed or commercialized
without written permission.

There is no support or guarantee of any sort as to this projects operations or
correctness. 

Permission to use, copy, and/or alter the source code is hereby granted without 
any fee provided that written permission is granted and the above copyright 
notice is included in all copies. This software is provided “as is” and any 
expressed or implied warranties are disclaimed.


About Soccer Simulation:
-----------------------
This is the release of Soccer Simulation 1.0.0 and the source files were
last edited on May 16, 2015. 

At the highest level, Soccer Simulation is a virtual soccer game played by the 
a computer. It is an application that mimics some features of the dynamics, 
organization, and layout properties of a soccer game. This simulation graphically 
depicts the 2D movements of the ball and players. This application does not 
require input from an user; it merely generates output to be observed.

> Requirements <

To run Soccer Simulation, you will need:

	MAC OSX 10.7 or later
	Xcode 6.0.0 or later https://developer.apple.com/xcode/
	OpenGL 4.5 or later http://opengl.en.softonic.com/download
	SDL 2.0 or later https://www.libsdl.org/download-2.0.php
	SDL2_image 2.0 or later https://www.libsdl.org/projects/SDL_image/
	GLEW 1.2-2.0 or later http://glew.sourceforge.net/

> Setting up and configuring the environment <

Since this project is not a yet prepackaged readily executable file,you need to 
set it up in an Xcode Project as if you were to develop on it. Just add the source
files to a brand new project and make sure the working directory sees the ‘img’ 
directory.  

	1. In an Xcode project, go to Build Settings > Search Paths > 
	Library Search Paths. Then add the the path where the GLEW library is. 
	Under ‘Header Search Paths’, include the the path of the ‘include’ 
	folder that is also within the GLEW library. 
	

	2. In Xcode, select the project name-> Target Name -> Build Phases 
	-> Link Binary With Libraries. Click the plus button to add the OpenGl
	and GLUT frameworks. Also, add the SDL2 and SD2L_image frameworks by 
	clicking on the plus sign again, selecting ‘Add Other…’ and selecting 
	these 2 frameworks. The location of these should be ~/Library/Frameworks.

> Running <

Running is as simple as pressing the ‘Build and Run’ button in Xcode. 
It’s that easy!. 

This distribution contains the following directories:
-----------------------------------------------------
-img:	The images for all the players and the ball.


Latest version Download Documentation:
--------------------------------------
The is some documentation related to the source code itself, but it’s only 
in comments provided inline with the source code.  Other documentation can
be found in Github at GibranMo/CMPE-195B under the “Some Documentation” folder.
To download the latest version of Soccer Simulation visit the same place.  


Contact:
--------
To report a bug, suggestions, or comments contact us at gibran_dena@yahoo.com

enjoy!

		

	

 