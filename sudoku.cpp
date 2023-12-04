/*
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
  
架構表：
  sudoku.cpp
  ﹂print.h
    ﹂generate.h
*/
/*簡寫變數及函式名稱意義說明：
ans = answer of sudoku
que = quesion
sta = status : 
            1 = main page
            2 = 4*4
            3 = 9*9
            4 = 16*16
t2, t3, t4 = array for testing use
*/
#include <bits/stdc++.h>
#include "print.h"

int main(){
    //pt(2, 0, 0);
    //pt(3, 0, 0);
    //cout << "Hello World!\n";
    int N = 9;
    int K = 20;
    Sudoku* sudoku = new Sudoku(N, K);
    sudoku->fillValues();
    sudoku->printSudoku();
}
