# Sudoku（數獨）
User can choose whether they want to play a 4\*4, 9\*9, or 16\*16 Sudoku.  
To move in the array, press 'J', 'I', 'K', 'L', which represent 'left', 'up', 'down', and 'right'.  
While playing a 16*16 Sudoku, numbers exceed 9 can be entered by replacing '10' with 'A', '11' with 'B', and so on.  
Right after user enter their answers, they can know if their answers are correct by checking the color of numbers on the screen.  
During the game, users can press 'H' to get the answer of the blank or press 'ESC' to leave the game.  

# About Possible Mistakes
If you download this project and open it with Visual Studio, you may find it's unable to compile since the compiler tells you that it can't open <bits/stdc++.h>.  
### THAT IS NOT MY FAULT.  
Although you've pre-installed <bits/stdc++.h>, it's still possible that this code can't be compiled because I've edited my own <bits/stdc++.h> and added some other headers I usually used.  
Including extra library below in "generate.h" might be helpful.  
```c++
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <windows.h>
#include <Windows.h>
```

## Authors 
112511142 魏宏凱  
112511098 楊朋翰  
112學年度 計算機概論與程式設計 劉建男 期末專題
