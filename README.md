##Name : Shang-Chun, Lin
#HW 2: Conway's Game of Life

* description :
The codes is made for building program that generates glides automatically and we are able to press some buttons to manipulate the process.

* How I did it :
I have built several functions for the program.
First off, I have declared several global variables to determine characteristic of the program. Such as updating by 1 time step every 0.5s, whether the program is running, or whether the program is in the paused mode.

Secondly, In the while loop, init function helps me to initialize the program.

Thirdly, the process function calculates how many neighbor do we have for every position and result in changing the next universe. After that, the current universe pointer points to the next one and delete the origin one.

The last one is event function for detecting whether we have pressed any button on the keyboard. (e.g. n for taking a single step forward, p for being in the paused mode, q for quitting the program, and x for setting an X on the screen.)

