#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <array>
#include <vector>

using namespace std;

int R, C, F, N, B, T;
const int DEBUG = 0;
int index = 0;

typedef struct tup {
    int a, b, x, y, real_s, f, distance, late_s, good_s, index;
} tup;

set<array<int, 9>> tups_s;
vector<array<int, 9>> tups_v;
set<array<int, 2>> starts;
set<array<int, 4>> vehicles;
vector<int> vehicles_starts[10000];
array<int, 10000> done;
int done_count = 0;
int count = 0;

int dist(int a, int b, int x, int y) {
    int xx = a < x ? x - a : a - x;
    int yy = b < y ? y - b : b - y;
    return xx + yy;
}

void add_tuple(int a, int b, int x, int y, int s, int f) {
    array<int, 9> tupi;
    tupi[0] = a;
    tupi[1] = b;
    tupi[2] = x;
    tupi[3] = y;
    tupi[4] = s; //real start
    tupi[5] = f;
    tupi[6] = f - s < dist(a, b, x, y) ? 0 : dist(a, b, x, y);
    tupi[7] = count;
    tupi[8] = 0;
    ++count;
    if (tupi[6] > 0)
        tups_v.push_back(tupi);

//    tups_s.insert(tupi);
}

void add_start(int a, int b) {
    starts.insert({a, b});
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
        add_start(a, b);
    }
    if (DEBUG) {
        for (vector<array<int, 9>>::iterator it = tups_v.begin(); it != tups_v.end(); it++) {
            for (int i = 0; i < 6; ++i) {
                cout << (*it)[i] << " ";
            }
            cout << endl;
        }
    }
}

void create_vehicles() {
    for (int i = 0; i < F; ++i) {
        vehicles.insert({0, i, 0, 0});
    }
}

bool isok(set<array<int, 4>>::iterator veh, vector<array<int, 9>>::iterator req, int *when, int *x, int *y, int *koszt) {
    if ((*req)[8] == 1) {
        return false;
    }
    *x = (*req)[2];
    *y = (*req)[3];
    int dojazd = dist((*veh)[2], (*veh)[3], (*req)[0], (*req)[1]);
    int pkty = (*req)[6];
    int bonus = 0;
    if ((*veh)[0] + dojazd <= (*req)[4]) {
        *when = (*req)[4] + (*req)[6];
        bonus = B;
    } else {
        *when = (*veh)[0] + dojazd + (*req)[6];
    }
    *koszt = bonus;
    return *when < (*req)[5];
}

void assign_starts() {
    set<array<int, 4>>::iterator veh = vehicles.begin();
    int v = (*veh)[1];
    if (done[v]) {
        vehicles.erase(vehicles.begin());
        return;
    }
    int start = -1;
    int max = T, koszt = 0;
    int temp, when = 0, best_when = 0;
    int x, best_x;
    int y, best_y;
    int k = 0;
    vector<array<int, 9>>::iterator best_it;
    for (vector<array<int, 9>>::iterator it = tups_v.begin(); it != tups_v.end(); it++) {
        if (isok(veh, it, &when, &x, &y, &koszt)) {
            if (when + k < max + koszt) {
                max = when;
                k = koszt;
                start = (*it)[7];
                best_when = when;
                best_x = x;
                best_y = y;
                best_it = it;
            }
        }
    }
    vehicles.erase(vehicles.begin());
    if (start != -1) {
        vehicles_starts[v].push_back(start);
        (*best_it)[8] = 1;
        vehicles.insert({best_when, v, best_x, best_y});
    }
}

int main() {
    parse();
    create_vehicles();
    while (!starts.empty() && !vehicles.empty()) {
        assign_starts();
    }
    for (int i = 0; i < F; ++i) {
        cout << vehicles_starts[i].size() << " ";
        for (vector<int>::iterator it = vehicles_starts[i].begin(); it != vehicles_starts[i].end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
    return 0;
}