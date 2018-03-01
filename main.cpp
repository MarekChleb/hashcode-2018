#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <array>

using namespace std;

int R, C, F, N, B, T;
const int DEBUG = 1;

typedef struct tup {
    int a, b, x, y, real_s, f, distance, late_s, good_s;
} tup;

set<array<int, 9>> tups;

void add_tuple(int a, int b, int x, int y, int s, int f) {
    array<int, 9> tupi;
    tupi[0] = a;
    tupi[1] = b;
    tupi[2] = x;
    tupi[3] = y;
    tupi[4] = s;
    tupi[5] = f;
    tups.insert(tupi);
}

void parse() {
    int a, b, x, y, s, f;
    cin >> R >> C >> F >> N >> B >> T;
    if (DEBUG) {
        cout << N << endl;
    }
    for (int i = 0; i < N; ++i) {
        cin >> a >> b >> x >> y >> s >> f;
        add_tuple(a, b, x, y, s, f);
    }
    if (DEBUG) {
        for (set<array<int, 9>>::iterator it = tups.begin(); it != tups.end(); it++) {
            for (int i = 0; i < 6; ++i) {
                cout << (*it)[i] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    parse();
    return 0;
}