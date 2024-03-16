Car Game using OpenGL (GLEW + FreeGLUT)

This project implements a simple car game using OpenGL, GLEW, and FreeGLUT libraries. The objective of the game is to maneuver a car through obstacles and reach the target without colliding. The game includes features such as collision detection, scoring, and game restart.

Prerequisites

Visual Studio
GLEW Library
FreeGLUT Library

How to Run

Clone the repository to your local machine.
Open the project in Visual Studio.
Make sure the GLEW and FreeGLUT libraries are properly linked to the project.
Build and run the project.

Files Included

main.cpp: Contains the main code for the car game.
glew.h: GLEW header file.
freeglut.h: FreeGLUT header file.

Controls

Use the arrow keys to control the movement of the car:
Up Arrow: Move forward
Down Arrow: Move backward
Left Arrow: Move left
Right Arrow: Move right
Press Esc to exit the game.

Game Rules

Avoid collisions with obstacles.
Reach the target to win the game.
The game will restart automatically upon collision or reaching the target.
Additional Notes
The game window size is set to 500x500 pixels.
The game world includes a ground, obstacles, a car, and a target.
Collision detection ensures that the game ends upon collision with obstacles.
Winning detection is triggered upon reaching the target.
The game features an FPS counter in the console window.
Credits

License
This project is licensed under the MIT License.

Feel free to modify and use this project for educational or personal purposes. If you encounter any issues or have suggestions for improvements, please create an issue or pull request. Enjoy playing the car game!
