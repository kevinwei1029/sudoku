//  Codes in this file generate the quesion
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int sta, x = 0, y = 0;

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
};

class Sudoku {
public:
    int** mat;
    int N;

    // number of columns/rows.
    int SRN;

    // square root of N
    int K;
    // No. Of missing digits

    // Constructor
    Sudoku(int N, int K)
    {
        this->N = N;
        this->K = K;

        // Compute square root of N
        double SRNd = sqrt(N);
        SRN = (int)SRNd;
        mat = new int* [N];

        // Create a row for every pointer
        for (int i = 0; i < N; i++)
        {
            // Note : Rows may not be contiguous
            mat[i] = new int[N];

            // Initialize all entries as false to indicate
            // that there are no edges initially
            memset(mat[i], 0, N * sizeof(int));
        }
    }

    // Sudoku Generator
    void fillValues()
    {

        // Fill the diagonal of SRN x SRN matrices
        fillDiagonal();

        // Fill remaining blocks
        fillRemaining(0, SRN);

        // Remove Randomly K digits to make game
        //removeKDigits();
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
    // Returns false if given 3 x 3 block contains num.
    bool unUsedInBox(int rowStart, int colStart, int num)
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
    // Fill a 3 x 3 matrix.
    void fillBox(int row, int col)
    {
        int num;
        for (int i = 0; i < SRN; i++) {
            for (int j = 0; j < SRN; j++) {
                do {
                    num = randomGenerator(N);
                } while (!unUsedInBox(row, col, num));
                mat[row + i][col + j] = num;
            }
        }
    }
    // Random generator
    int randomGenerator(int num)
    {
        return (int)floor(
            (float)(rand() / double(RAND_MAX) * num + 1));
    }
    // Check if safe to put in cell
    bool CheckIfSafe(int i, int j, int num)
    {
        return (
            unUsedInRow(i, num) && unUsedInCol(j, num)
            && unUsedInBox(i - i % SRN, j - j % SRN, num));
    }
    // check in the row for existence
    bool unUsedInRow(int i, int num)
    {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
        return true;
    }
    // check in the row for existence
    bool unUsedInCol(int j, int num)
    {
        for (int i = 0; i < N; i++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
        return true;
    }
    // A recursive function to fill remaining
    // matrix
    bool fillRemaining(int i, int j)
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
                if (fillRemaining(i, j + 1)) {
                    return true;
                }
                mat[i][j] = 0;
            }
        }
        return false;
    }
    // Remove the K no. of digits to
    // complete game
    void removeKDigits()
    {
        int count = K;
        while (count != 0) {
            int cellId = randomGenerator(N * N) - 1;
            // System.out.println(cellId);
            // extract coordinates i and j
            int i = (cellId / N);
            int j = cellId % N;
            if (j != 0) {
                j = j - 1;
            }
            // System.out.println(i+" "+j);
            if (mat[i][j] != 0) {
                count--;
                mat[i][j] = 0;
            }
        }
    }
    // Print sudoku
    void printSudoku()
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(3) << to_string(mat[i][j]) + " ";
                //cout << setw(2) << mat[i][j] + " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    void ptv(int n, char a) {
        for (int i = 0; i < ((n + 1) * (n + 1) + 2 * n * n); i++) {  //  i < n+1 + (n+1)*n + 2*n*n
            cout << a;
        }
        cout << "\n";  //  print a vertical line
    };
    void pt(int n, int x, int y) {
        sta = n;
        this->ptv(n, '-');
        for (int i = 0; i < N; i++) {
            cout << "|";
            for (int j = 0; j < N; j++) {
                if (i == x && j == y) {
                    SetColor(11);
                }

                if (t3[i][j] == 0) {
                    cout << " __";
                }
                else {
                    cout << setw(3) << mat[i][j];
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
        cout << "press 'ESC' to leave\n\n\n";
    };
    void SetColor(int color = 7)
    {
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
};