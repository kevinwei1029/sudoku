# Sudoku（數獨） Introduction
Sudoku requires player fill numbers in blanks to make all of the numbers in any rows, colunmns, and blocks are not repeated.

# Operations and Functions
User can choose whether they want to play a 4\*4, 9\*9, or 16\*16 Sudoku.  
To move in the array, press 'J', 'I', 'K', 'L', which represent 'left', 'up', 'down', and 'right'.  
To input numbers, directly press the keyboard; while playing a 16*16 Sudoku, numbers exceed 9 can be inputted by replacing '10' with 'A', '11' with 'B', and so on.  
Right after user enter their answers, they can know if their answers are correct by checking the color of numbers on the screen.  
During the game, users can press 'H' to get the answer of current blank, press 'ESC' to leave the current game, press 'Z' to undo, press 'Y' to redo, and press '-' to immediately end the program at any time.  

# About Possible Compile Mistakes
If you download this project and open it with Visual Studio, you may find it's unable to compile since the compiler tells you that it can't open <bits/stdc++.h>.  
### THAT IS NOT MY FAULT.  
Although you've pre-installed <bits/stdc++.h> for your Visual Studio, it's still pretty possible that this code can not be compiled because I've edited my own <bits/stdc++.h> and added some other headers I usually used.  
Including extra library below in "generate.h" might be helpful.  
```c++
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <stack>
#include <conio.h>
#include <Windows.h>
```

## Authors 
112511142 魏宏凱  
112511098 楊朋翰  
112學年度 計算機概論與程式設計 劉建男 期末專題
