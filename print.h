//  Codes in this file conduct all kinds of prints
#include <bits/stdc++.h>
#include "generate.h"
using namespace std;

void ptv(int n, char a) {
	for (int i = 0; i < ((n + 1) * (n + 1) + 2 * n * n); i++) {  //  i < n+1 + (n+1)*n + 2*n*n
		cout << a;
	}
	cout << "\n";  //  print a vertical line
};

void pt(int n, int x, int y) {
	sta = n;
	ptv(n, '-');
	for (int i = 0; i < n * n; i++) {
		cout << "|";
		for (int j = 0; j < n * n; j++) {
			if (t2[i][j] == 0) {
				cout << " __";
			}
			else {
				cout << setw(3) << t2[i][j];
			}
			if (j % n == n - 1) {
				cout << " |";
			}
		}
		cout << endl;
		if (i % n == n - 1) {
			ptv(n, '-');
		}
	}
	cout << "Enter"
};