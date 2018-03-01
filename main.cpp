#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <array>
#include <vector>

using namespace std;

int R, C, F, N, B, T;
const int DEBUG = 1;
int index = 0;

typedef struct tup {
    int a, b, x, y, real_s, f, distance, late_s, good_s, index;
} tup;

set<array<int, 9>> tups_s;
vector<array<int, 9>> tups_v;
set<array<int, 2>> starts;
set<array<int, 5>> vehicles;
array<int, 10000> done;
int done_count = 0;

void add_tuple(int a, int b, int x, int y, int s, int f) {
    array<int, 9> tupi;
    tupi[0] = a;
    tupi[1] = b;
    tupi[2] = x;
    tupi[3] = y;
    tupi[4] = s;
    tupi[5] = f;
    tups_s.insert(tupi);
    tups_v.push_back(tupi);
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
        for (set<array<int, 9>>::iterator it = tups_s.begin(); it != tups_s.end(); it++) {
            for (int i = 0; i < 6; ++i) {
                cout << (*it)[i] << " ";
            }
            cout << endl;
        }
    }
}

void create_vehicles() {
    for (int i = 0; i < F; ++i) {
        vehicles.insert({0, 0, 0, 0, 0});
    }
}

int main() {
    parse();
    create_vehicles();
    return 0;
}