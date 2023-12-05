//  Codes in this file generate the quesion
#include <bits/stdc++.h>
#include <windows.h>
#include <random>
#include <Windows.h>
using namespace std;

int x = 0, y = 0, sta = 1;

//  testing int array
/*
int t2[4][4] = {
	{0, 2, 0, 4},
	{1, 0, 3, 2},
	{0, 1, 4, 0},
	{2, 3, 0, 0},
};
int t3[9][9] = {
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
	{0, 2, 0, 4, 0, 2, 0, 4, 5},
};*/

class Sudoku {
public:
    //  declear 2D array pointer
    int** mat;
    int** ans;
    int** res;

    //  number of columns and rows.
    int N;
    //  square root of N
    int SRN;
    //  numbers of missing digits
    int K;
    //  record the time
    //int clk;
    time_t clk = time(0);

    //  if sudoku end
    bool ise;

    //  Constructor
    Sudoku(int N, int K)
    {
        this->N = N;
        this->K = K;

        // Compute square root of N
        double SRNd = sqrt(N);
        SRN = (int)SRNd;
        mat = new int* [N];
        ans = new int* [N];
        res = new int* [N];

        // Create a row for every pointer
        for (int i = 0; i < N; i++)
        {
            // Note : Rows may not be contiguous
            mat[i] = new int[N];
            ans[i] = new int[N];
            res[i] = new int[N];

            // Initialize all entries as false to indicate
            // that there are no edges initially
            memset(mat[i], 0, N * sizeof(int));
            memset(ans[i], 0, N * sizeof(int));
            memset(res[i], 0, N * sizeof(int));
        }
    }

    //  Sudoku Generator
    void fill()
    {
        //  Fill the diagonal of SRN x SRN matrices
        fillDiagonal();

        // Fill remaining blocks
        fillr(0, SRN);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ans[i][j] = mat[i][j];
                //cout << "ans [" << i << "][" << j << "] = " << ans[i][j] << endl;
                //cout << "ans [" << i << "][" << j << "] was given by mat[" << i << "][" << j << "]\n";
            }
        }

        // Remove Randomly K digits to make game
        rkd();
    }

    // Fill the diagonal SRN number of SRN x SRN matrices
    void fillDiagonal()
    {
        for (int i = 0; i < N; i = i + SRN)
        {
            // for diagonal box, start coordinates->i==j
            fillBox(i, i);
        }
    }

    // Fill a 3 x 3 matrix.
    void fillBox(int row, int col)
    {
        mt19937 mt(time(nullptr));
        int num;
        for (int i = 0; i < SRN; i++) {
            for (int j = 0; j < SRN; j++) {
                do {
                    //num = randomGenerator(N);
                    num = mt() % N + 1;
                } while (!unb(row, col, num));
                mat[row + i][col + j] = num;
            }
        }
    }

    // A recursive function to fill remaining matrix
    bool fillr(int i, int j)
    {
        // System.out.println(i+" "+j);
        if (j >= N && i < N - 1) {
            i = i + 1;
            j = 0;
        }
        if (i >= N && j >= N) {
            return true;
        }
        if (i < SRN) {
            if (j < SRN) {
                j = SRN;
            }
        }
        else if (i < N - SRN) {
            if (j == (int)(i / SRN) * SRN) {
                j = j + SRN;
            }
        }
        else {
            if (j == N - SRN) {
                i = i + 1;
                j = 0;
                if (i >= N) {
                    return true;
                }
            }
        }
        for (int num = 1; num <= N; num++) {
            if (CheckIfSafe(i, j, num)) {
                mat[i][j] = num;
                if (fillr(i, j + 1)) {
                    return true;
                }
                mat[i][j] = 0;
            }
        }
        return false;
    }

    /* Random generator
    int randomGenerator(int num)
    {
        return (int)floor(
            (float)(rand() / double(RAND_MAX) * num + 1));
    }*/
    // Check if safe to put in cell
    bool CheckIfSafe(int i, int j, int num)
    {
        return (
            unr(i, num) && unc(j, num)
            && unb(i - i % SRN, j - j % SRN, num));
    }

    // Returns false if given 3 x 3 block contains num.
    bool unb(int rowStart, int colStart, int num)
    {
        for (int i = 0; i < SRN; i++) {
            for (int j = 0; j < SRN; j++) {
                if (mat[rowStart + i][colStart + j]
                    == num) {
                    return false;
                }
            }
        }
        return true;
    }

    // check in the row for existence
    bool unr(int i, int num)
    {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
        return true;
    }

    // check in the row for existence
    bool unc(int j, int num)
    {
        for (int i = 0; i < N; i++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
        return true;
    }

    // Remove the K no. of digits to complete game
    void rkd()
    {
        mt19937 mt(time(nullptr));
        int count = K;
        while (count != 0) {
            int i = mt() % N;
            int j = mt() % N;
            if (mat[i][j] != 0) {
                count--;
                mat[i][j] = 0;
            }
        }
    }

    //  print sudoku
    void ptSudoku(char a)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (a == 'a') {
                    cout << "Now pt ans[][] : \n";
                    cout << setw(3) << to_string(ans[i][j]) + " ";
                }
                else if (a == 'm') {
                    cout << "Now pt mat[][] : \n";
                    cout << setw(3) << to_string(mat[i][j]) + " ";
                }
                else {
                    cout << "It's strang since this function dosen't lnow what to print.";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    //  print something vertical
    void ptv(int n, char a) {
        for (int i = 0; i < ((n + 1) * (n + 1) + 2 * n * n); i++) {  //  i < n+1 + (n+1)*n + 2*n*n
            cout << a;
        }
        cout << "\n";
    };

    //  print the sudoku pattren
    void pt(int n, int x, int y, int uin) {
        ise = true;
        time_t now = time(0);
        //  basic setup

        if (uin != 0 && mat[x][y] == 0) {
            res[x][y] = uin;
        }
        //  put user input into arr

        this->ptv(n, '-');
        cout << now - clk << " seconds have passed since you start this turn.\n";
        this->ptv(n, '-');
        for (int i = 0; i < N; i++) {
            cout << "|";
            for (int j = 0; j < N; j++) {
                if (i == x && j == y) {
                    SetColor(11);
                }
                else if (res[i][j] == ans[i][j] && res[i][j] != 0) {  //  correct answer
                    SetColor(10);
                }
                else if (res[i][j] != ans[i][j] && res[i][j] != 0) {  //  wrong answer
                    SetColor(12);
                }

                if (res[i][j] + mat[i][j] != ans[i][j]) {
                    ise = false;
                }

                if (mat[i][j] == 0 && res[i][j] == 0) {
                    cout << " __";
                    ise = false;
                }
                else {
                    cout << setw(3) << mat[i][j] + res[i][j];
                }

                SetColor();

                if (j % n == n - 1) {
                    cout << " |";
                }
            }
            cout << endl;
            if (i % n == n - 1) {
                this->ptv(n, '-');
            }
        }
        cout << "press 'ESC' to leave\npress H to get a hint\n\n\n";

        if (ise) ptc();
    };

    //  print congradulation
    void ptc() {
        time_t now = time(0);
        cout << "\n\ncongradulations!";
        cout << "\n\nYou spend " << now - clk << " seconds on completing this sudoku.\n\n\n";
    };

    //  set the color of output
    //  website : https://blog.wildsky.cc/posts/c-code-note
    void SetColor(int color = 7)
    {
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    //  check if n belongs numbers to fill in
    int ctoi(char n) {
        n = toupper(n);
        if (n > 48 && n < 58) {  //  if n belongs 1 ~ 9
            return  n - '0';
        }
        else if (n > 64 && n < 72) {  //  if n belongs 10 ~ 16
            return 9 + n - '@';
        }
        else {
            return 0;
        }
    };

    //  work if someone ask for a hint
    void ah(int i, int j) {
        mat[i][j] = ans[i][j];
    };
};