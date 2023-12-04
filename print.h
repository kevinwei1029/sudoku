//  Codes in this file conduct all kinds of prints
#include <bits/stdc++.h>
#include "generate.h"
using namespace std;

void ptv(int n) {
	for (int i = 0; i < ((n + 1) * (n + 1) + 2 * n * n); i++) {  //  i < n+1 + (n+1)*n + 2*n*n
		cout << "_";
	}
	cout << "\n";  //  print a vertical line
};

void pt(int n, int x, int y) {
	sta = n;
	ptv(n);
	for (int m = 0; m < n; m++) {
		for (int l = 0; l < n; l++) {
			for (int k = 0; k < n; k++) {
				for (int i = 0; i < n; i++) {
					cout << "|";
					for (int j = 0; j < n; j++) {
						if (t2[i + l][j + k] != 0)
							cout << " " << setw(2) << t2[i + l][j + k];
						else
							cout << " __";
					}
					cout << " ";
				}
				cout << "|";  //  pt n numbers
			}
			cout << "|\n";//  pt a line
		}
		ptv(n);
	}
};