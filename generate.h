#include <bits/stdc++.h>
using namespace std;

int x = 0, y = 0, sta = 1;

class Sudoku {
public:
    //  declear 2D array pointer
    int** res;
    int** mat;
    int** ans;

    int N, K, aht = 0, bc = 0;

    //  record the time
    time_t clk = time(0);

    //  if sudoku end
    bool ise;

    //  construct a cool ending output
    string cgl = "";

    //  Constructor
    Sudoku(int N, int K)
    {
        this -> N = N;
        this -> K = K;

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
            // for diagonal box, start coordinates -> i==j
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
        int c = K;
        while (c > 0) {
            int i = mt() % N;
            int j = mt() % N;
            if (mat[i][j] != 0)  
            {
                mat[i][j] = 0;
                c--;
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
            if (a == '-') {
                SetColor(13);
                cout << a;
            }
            else
                cout << a;
        }
        SetColor();
        cout << "\n";
    };

    //  print a line of blank or with words
    void ptb(int n, string s) {
        if (s.size() >((n + 1) * (n + 1) + 2 * n * n - 2)) {
            SetColor(13);
            cout << '|';
            SetColor(14);
            cout << s << endl;
            SetColor();
        }
        else {
            int bw = ((n + 1) * (n + 1) + 2 * n * n - 2) - s.size();
            SetColor(13);
            cout << "|";
            SetColor(14);
            cout << s;
            for (int i = 0; i < bw; i++) {
                cout << " ";
            }
            SetColor(13);
            cout << "|\n";
            SetColor();
        }
    };

    //  print congradulation
    void ptc() {
        time_t now = time(0);
        SetColor(236);
        cout << "\n\ncongradulations!";
        cout << "\n\nYou spend " << now - clk << " seconds on completing this sudoku.\n\n";
        SetColor();
        cout << '\n';
    };

    //  print extra rules of 4*4 sudoku
    void ptr() {
        this->ptb(sqrt(N), "");
        this->ptb(sqrt(N), "use a for " + to_string(this->ctoi('a')) + ", b for " + to_string(this->ctoi('b')) + ", c for " + to_string(this->ctoi('c')) + ", d for " + to_string(this->ctoi('d')) + ",");
        this->ptb(sqrt(N), "    e for " + to_string(this->ctoi('e')) + ", f for " + to_string(this->ctoi('f')) + ", g for " + to_string(this->ctoi('g')) + ",");
        this->ptb(sqrt(N), "");
    };

    //  print the sudoku pattren
    void pt(int n, int x, int y, int uin) {
        //  basic setup
        ise = true;
        time_t now = time(0);

        //  put user input into arr
        if (uin != 0 && mat[x][y] == 0) res[x][y] = uin;

        //  print the sudoku pattern
        if (n == 4) ptr();
        this -> ptb(n, to_string(now - clk) + " seconds have passed since you start this turn.");
        this -> ptv(n, '-');
        for (int i = 0; i < N; i++) {
            SetColor(13);
            cout << "|";
            SetColor();
            for (int j = 0; j < N; j++) {
                if (i == x && j == y) SetColor(11);  //  where mouse is
                else if (res[i][j] == ans[i][j] && res[i][j] != 0) SetColor(10);  //  correct answer
                else if (res[i][j] != ans[i][j] && res[i][j] != 0) SetColor(12);  //  wrong answer

                if (res[i][j] + mat[i][j] != ans[i][j]) {
                    ise = false;
                    bc++;
                }

                if (mat[i][j] == 0 && res[i][j] == 0) cout << " __";
                else cout << setw(3) << mat[i][j] + res[i][j];

                SetColor();

                if (j % n == n - 1) {
                    SetColor(13);
                    cout << " |";
                    SetColor();
                }
            }
            cout << endl;
            if (i % n == n - 1) this -> ptv(n, '-');
        }
        this -> ptb(n, "There are " + to_string(bc) + " blanks remaining.");
        this -> ptb(n, "press 'ESC' to leave");
        this -> ptb(n, "press 'H' to get a hint");
        this -> ptv(n, '-');
        bc = 0;
        if (ise) ptc();
    };

    //  set the color of output
    //  refrence website : https://blog.wildsky.cc/posts/c-code-note
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
            this->ptb(sqrt(N), "Your input h is an unvalid command.");
        else
        {
            aht++;
            mat[i][j] = ans[i][j];
            this->ptb(sqrt(N), "You have asked for a hint " + to_string(aht) + " times.");
        }
    };
};
