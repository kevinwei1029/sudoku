﻿/*
sudoku.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。

執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

開始使用的提示: 
  1. 使用 [方案總管] 視窗，新增/管理檔案
  2. 使用 [Team Explorer] 視窗，連線到原始檔控制
  3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
  4. 使用 [錯誤清單] 視窗，檢視錯誤
  5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
  6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
*/
//  簡寫變數及函式名稱意義說明：
/*ans = answer of sudoku
que = quesion
sta = status : 
    1 = main page
    2 = in game
x, y = as smae as i and j which indicates where you are in the array
N = n * n
K = how many blanks to remove
unr = unused in row
unc = unusedd in column
unb = unused in box
cks = check if it is safe to put in box
fill = create the basic pattren
fillr = fill in the remaining blanks
rkd = remove k digits from the array
N = number of columns and rows
K = numbers of removed digits
aht = record ask for hint times
bc = count the number of blank
mbw = move backward
mfw = moveforward
co & c = color user choosed
*/
#include "generate.h"

int main() {
    int N = 4, K = 2, co = 0;
    char n;
    Sudoku* sudoku = new Sudoku;
    /*for (int i = 0; i < size(sudoku->cgl); i++)
    {
        //sudoku->ptc();
        cout << sudoku->cgl[i];
        cout << '\n';
    }
    exit(0);*/
    while(1){
        switch (sta) {
        case 1:  //  main page
            system("cls");

            //  enter ? * ?
            cout << "Welcome to this sudoku game.\nEnter 2, 3, or 4 to start a 4 * 4, 9 * 9, or 16 * 16 Sudoku game : ";
            n = _getch();
            if (n == '-') exit(0);
            while (sudoku->ctoi(n) < 2 || 4 < sudoku->ctoi(n)) {
                cout << n << "\nERROR\nEnter again : ";
                n = _getch();
                if (n == '-') exit(0);
                /*
                else if (n == 'm') {
                    cout << "Start making sudoku file......";

                    for (int i = 2; i < 5; i++) {
                        for (int j = 1; j < 11; j++) {
                            Sudoku* make = new Sudoku(i*i, j);
                            delete make;
                        }
                    }
                    break;
                }*/
            }
            N = sudoku->ctoi(n) * sudoku->ctoi(n);
            cout << n << '\n';
            sudoku->ptv(3, '-');

            //  enter difficulty
            cout <<"\nChoose difficulty\nEnter E, M, or H to start a game with Easy, Medium, or Hard difficulty : ";
            n = _getch();
            if (n == '-') exit(0);
            n = toupper(n);
            while (!(n == 'E' || n == 'M' || n == 'H' || n == 'T')) {
                cout << n << "\nERROR !\nEnter again : ";
                n = _getch();
                if (n == '-') exit(0);
                n = toupper(n);
            }
            cout << n << endl;
            sudoku->ptv(3, '-');
            if (n == 'E') K = 0.5 * N * N;
            else if (n == 'M') K = 0.6 * N * N;
            else if (n == 'H') K = 0.75 * N * N;
            else if (n == 'T') K = 2;

            //  enter color
            if (co == 0) {
                while (n != 'Y') {
                    co = sudoku->chc();
                    if (co == 7) {
                        break;
                    }
                    sudoku->SetColor(sudoku->c);
                    cout << "Do you sure that you want to use this color to start? (Y/N) : ";
                    sudoku->SetColor();
                    n = _getch();
                    if (n == '-') exit(0);
                    n = toupper(n);
                }
                co = sudoku->c;
            }

            //  change state
            sta = 2;
            break;

        case 2:  //  in game
            cout << "Do you want to use prebuild quesions? (Y/N) : ";
            n = _getch();
            n = toupper(n);
            system("cls");
            //  create a sudoku
            Sudoku *sudoku = new Sudoku(N, K, co, n);
            n = _getch();
            while (n != 27) {  //  n != ESC
                if (n == '-') exit(0);
                system("cls");
                cout << n << endl;
                sudoku->ptv(sqrt(N), '-');

                //  recieve command
                n = tolower(n);
                if      ((n == 105 || n == 105) && x - 1 >= 0) x -= 1;  //  up     =>  pg up    .
                else if ((n == 107 || n == 112) && x + 1 < N)  x += 1;  //  down   =>  pg down  112
                else if ((n == 106 || n == 106) && y - 1 >= 0) y -= 1;  //  left   =>  home     .
                else if ((n == 108 || n == 109) && y + 1 < N)  y += 1;  //  right  =>  end      109
                else if (n == 104) sudoku->ah(x, y);                    //  hint
                else if (n == 122) sudoku->cz();                        //  undo = C^Z
                else if (n == 121) sudoku->cy();                        //  redo = C^Y
                else if (sudoku->ctoi(n) != 0) ;
                else {
                    string txt = "Your input ";
                    txt.append(1, n);
                    sudoku->ptb(sqrt(N), txt + " is an unvalid command.");
                    //sudoku->ptb(sqrt(N), "Your input " + to_string(n) + " is an unvalid command.");
                }

                //  print updated sudoku pattern
                sudoku->pt(sqrt(N), x, y, sudoku->ctoi(n));

                //  check if ended
                if (sudoku->ise) break;

                n = _getch();
            }
            //  reset and back to main page
            x = y = 0;
            sta = 1;
            delete sudoku;
            system("pause");
            break;
        }
    }
    return 0;
}
