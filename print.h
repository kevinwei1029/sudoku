//  Codes in this file conduct all kinds of prints
#include <bits/stdc++.h>
#include "generate.h"
using namespace std;

void pt(int n, int x, int y) {
	sta = n;
	for (int i = 0; i < ((n+1)*(n+1) + 2 * n * n); i++) {  //  i < n+1 + (n+1)*n + 2*n*n
		cout << "_";
	}
	cout << "\n";
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			cout << "|";
			for (int j = 0; j < n; j++) {
				cout << " " << setw(2) << t2[i][j+k];
			}
			cout << " ";
		}
		cout << "|";  //  pt a block
	}
	cout << "|\n"//  pt a line
};