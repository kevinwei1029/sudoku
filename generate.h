#include <bits/stdc++.h>
using namespace std;

int x = 0, y = 0, sta = 1;

class Sudoku {
public:
    //  declear 2D array pointer
    int** res;
    int** mat;
    int** ans;

    //  number of columns and rows.
    int N;
    //  numbers of missing digits
    int K;
    //  record the time
    time_t clk = time(0);
    //  record ask for hint times
    int aht = 0;

    //  if sudoku end
    bool ise;

    //  construct a cool ending output
    string cgl = "";

    //  Constructor
    Sudoku(int N, int K)
    {
        this->N = N;
        this->K = K;

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

            // Initialize all entries as false to indicate that there are no edges initially
            memset(mat[i], 0, N * sizeof(int));
            memset(ans[i], 0, N * sizeof(int));
            memset(res[i], 0, N * sizeof(int));
        }
    }

    //  Sudoku Generator
    void fill()
    {
        //  Fill the diagonal of sqrt(N) x sqrt(N) matrices
        fillDiagonal();

        // Fill remaining blocks
        fillr(0, sqrt(N));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ans[i][j] = mat[i][j];
            }
        }

        //  remove K numbers to create quesion
        rkd();
    }

    // Fill the diagonal sqrt(N) number of sqrt(N) x sqrt(N) matrices
    void fillDiagonal()
    {
        for (int i = 0; i < N; i = i + sqrt(N))
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
        for (int i = 0; i < sqrt(N); i++) {
            for (int j = 0; j < sqrt(N); j++) {
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
        if (i < sqrt(N)) {
            if (j < sqrt(N)) {
                j = sqrt(N);
            }
        }
        else if (i < N - sqrt(N)) {
            if (j == (int)(i / sqrt(N)) * sqrt(N)) {
                j = j + sqrt(N);
            }
        }
        else {
            if (j == N - sqrt(N)) {
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

    // Check if safe to put in cell
    bool CheckIfSafe(int i, int j, int num)
    {
        int p = sqrt(N);
        return (
            unr(i, num) && unc(j, num)
            && unb(i - i % p, j - j % p, num));
    }

    // Returns false if given 3 x 3 block contains num.
    bool unb(int rowStart, int colStart, int num)
    {
        for (int i = 0; i < sqrt(N); i++) {
            for (int j = 0; j < sqrt(N); j++) {
                if (mat[rowStart + i][colStart + j] == num) {
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
        for (int c = K; c > 0; c--) {
            int i = mt() % N;
            int j = mt() % N;
            if (mat[i][j] != 0)  mat[i][j] = 0;
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

    //  print a line of blank or with words
    void ptb(int n, string s) {
        //cout << "enter ptb\nwidth = " << (n + 1) * (n + 1) + 2 * n * n - 2 << " size of s = " << s.size() << endl;
        if (s.size() >((n + 1) * (n + 1) + 2 * n * n - 2)) cout << s << endl;
        else {
            int bw = ((n + 1) * (n + 1) + 2 * n * n - 2) - s.size();
            cout << "|" << s;
            for (int i = 0; i < bw; i++) {
                cout << " ";
            }
            cout << "|\n";
        }
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
        this->ptb(n, to_string(now - clk) + " seconds have passed since you start this turn.");
        //cout << now - clk << " seconds have passed since you start this turn.\n";
        this->ptv(n, '-');
        for (int i = 0; i < N; i++) {
            cout << "|";
            for (int j = 0; j < N; j++) {
                if (i == x && j == y) {  //  if there is where mouse is
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

                SetColor();  //  reset cout color

                if (j % n == n - 1) {
                    cout << " |";
                }
            }
            cout << endl;
            if (i % n == n - 1) {
                this->ptv(n, '-');
            }
        }
        //this->ptb(n, "");
        //this->ptb(n, "");
        this->ptb(n, "press 'ESC' to leave");
        this->ptb(n, "press 'H' to get a hint");
        this->ptv(n, '-');

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
        if(mat[i][j] != 0)
            cout << "Your input h is an unvalid command.\n";
        else
        {
            aht++;
            mat[i][j] = ans[i][j];
            cout << "You have asked for a hint " << aht << " times.\n";
        }
    };
};