#include <bits/stdc++.h>

using namespace std;

int dx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };

struct Item {
    int item[8][14] = {};
    int check[8][14] = {};
    int getItem(int y, int x) {
        return item[y][x];
    }
};

bool BackTracking(Item& item, int y, int x, int cursor) {
    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= 8 || nx >= 14) continue;
        if (item.getItem(ny, nx) == cursor % 10) {
            if (BackTracking(item, ny, nx, cursor / 10)) return true;
        }
    }
    return false;
}

bool HasNumber(Item& item, int cursor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 14; j++) {
            if (cursor <= 9) {
                if (item.getItem(i, j) == cursor) return true;
            } else {
                if (item.getItem(i, j) == cursor % 10) {
                    if (BackTracking(item, i, j, cursor / 10)) return true;
                }
            }
        }
    }
    return false;
}

int GetScore(Item& item) {
    for (int i = 1; ; i++) {
        if (!HasNumber(item, i)) return i - 1;
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 9);

    int max_res = 0;
    Item c;
    while (true) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 14; j++) {
                c.item[i][j] = dis(gen);
            }
        }
        int score = GetScore(c);
        max_res = max(max_res, score);

        cout << max_res << '\n';

        if (max_res >= 8140) break;
    }
    return 0;
}
