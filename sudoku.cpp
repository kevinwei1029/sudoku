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
*/
//簡寫變數及函式名稱意義說明：
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
N = number of columns and rows.
K = numbers of missing digits
aht = record ask for hint times
bc = cout the number of blank
*/
#include "generate.h"

int main() {
    int N = 4, K = 20;
    char n;
    while(1){
        switch (sta) {
        case 1:  //  main page
            cout << "Welcome to this sudoku game.\nEnter 2, 3, 4 to start a game with 4*4, 9*9, 16*16 scale : ";
            cin >> n;
            while (!(n == '2' || n == '3' || n == '4')) {
                cout << "ERROR\nEnter again : ";
                cin >> n;
            }
            N = (n - '0') * (n - '0');
            cout << "\nChoose difficulty\nEnter E, M, H to start a game with Easy, Medium, Hard difficulty : ";
            cin >> n;
            n = toupper(n);
            while (!(n == 'E' || n == 'M' || n == 'H' || n == 'T')) {
                cout << "ERROR\nEnter again : ";
                cin >> n;
                n = toupper(n);
            }
            if (n == 'E') K = 0.5 * N * N;
            else if (n == 'M') K = 0.6 * N * N;
            else if (n == 'H') K = 0.75 * N * N;
            else if (n == 'T') K = 2;
            sta = 2;
            break;

        case 2:  //  in game
            Sudoku * sudoku = new Sudoku(N, K);
            sudoku->fill();
            sudoku->ptv(sqrt(N), '-');
            sudoku->pt(sqrt(N), x, y, 0);
            cin >> n;
            while (n != 45) {  //  n != -
                sudoku->ptv(sqrt(N), '-');

                n = tolower(n);
                if (n == 105 && x - 1 >= 0) x -= 1;  //  upward
                else if (n == 106 && y - 1 >= 0) y -= 1;  //  left
                else if (n == 107 && x + 1 < N) x += 1;  //  down
                else if (n == 108 && y + 1 < N) y += 1;  //  right
                else if (n == 104) sudoku->ah(x, y);  //  ask for hint
                else if (sudoku->ctoi(n) != 0) ;
                else sudoku->ptb(sqrt(N), "Your input " + to_string(n) +" is an unvalid command.");

                sudoku->pt(sqrt(N), x, y, sudoku->ctoi(n));

                if (sudoku->ise) break;

                cin >> n;
            }
            x = y = 0;
            sta = 1;
            break;
        }
    }
    return 0;
}
