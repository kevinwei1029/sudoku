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
t2, t3, t4 = array for testing use
x, y = as smae as i and j which indicates where you are in the array
N = n * n
K = numbers to remove
unr = unused in row
unc = unusedd in column
unb = unused in box
fill = create the basic pattren
fillr = fill in the remaining blanks
rkd = remove k digits
*/
#include "generate.h"

int main(){
    /*
    pt(2, 0, 0);
    pt(3, 0, 0);
    cout << "Hello World!\n";
    Sudoku* sudoku = new Sudoku(9, 20);
    for (int i = 0; i < 30; i++) {
        cout << "i = " << 2*i + 5 << " and geRe = " << sudoku->randomGenerator(2*i+5) << endl;
    }
    */
    
    int N = 9, K = 20;
    char n;
    sta = 1;
    switch (sta) {
        case 1:  //  main page
            cout << "Welcome to this sudoku game.\nEnter 2, 3, 4 to start a game with 4*4, 9*9, 16*16 scale : ";
            cin >> n;
            while (!(n == '2' || n == '3' || n == '4')) {
                cout << "ERROR\nEnter again";
                cin >> n;
            }
            N = (n - '0') * (n - '0');
            //cout << N << endl;
            //exit(0);
            sta = 2;
            

        case 2:  //  in game
            Sudoku* sudoku = new Sudoku(N, K);
            sudoku->fill();
            //sudoku->ptSudoku('a');
            //exit(0);
            while (1) {
                ///*
                sudoku->pt(sqrt(N), x, y);
                cin >> n;
                if (n == 105 && x-1 >= 0) {  //  upward
                    x -= 1;
                }
                else if (n == 106 && y-1 >= 0) {  //  left
                    y -= 1;
                }
                else if (n == 107 && x+1 < N) {  //  down
                    x += 1;
                }
                else if (n == 108 && y+1 < N) {  //  right
                    y += 1;
                }
                else if (n == 27) {  //  esc
                    sta = 1;
                    break;
                }
                //*/
            }
            break;
    }
}
