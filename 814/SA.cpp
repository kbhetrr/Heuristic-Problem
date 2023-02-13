#include <bits/stdc++.h>

using namespace std;

int dx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int ret = 0;
int flag = 0;

struct Random {
	mt19937 rd;
	Random() : rd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}
	short GetInt(short l = 0, short r = 32767) {
		return uniform_int_distribution<short>(l, r)(rd);
	}
	double GetDouble(double l = 0, double r = 1) {
		return uniform_real_distribution<double>(l, r)(rd);
	}
} Rand;

struct Item {
	int m[8][14] = {};
	int visit[8][14][11] = {};
	
	void setItem(string DB[]) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 14; j++) {
				m[i][j] = DB[i][j] - '0';
			}
		}
	}
	void setVisit() { memset(visit, -1, sizeof(visit)); }
	int getItem(int x, int y) { return m[x][y]; }
	int checkVisit(int x, int y, int dep) { return visit[x][y][dep]; }
} item;

int DFS(Item& item, int x, int y, int n) {
	if (!n) return 1;
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx < 0 || ny < 0 || nx >= 8 || ny >= 14) continue;
		if (item.getItem(nx, ny) == n % 10) {
			if (DFS(item, nx, ny, n / 10)) return 1;
		}
	}
	return 0;
}

int HasNum(Item& item, int n) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 14; j++) {
			if (item.getItem(i, j) == n % 10) {
				if (DFS(item, i, j, n / 10)) return 1;	
			}
		}
	}
	return 0;
}

int GetScore(Item& item) {
	int ret = 1;
	for (; ; ret++) {
		if (!HasNum(item, ret)) return ret - 1;
	}
}

void SA(int lim = 10000, double T = 10.0, double d = 0.9999) {
	int score = GetScore(item);
	ret = score;
	for (int i = 0; i < lim; i++, T *= d) {
		auto n_item = item;
		for (int j = 0; j < Rand.GetInt(1, 3); j++) {	
			n_item.m[Rand.GetInt(0, 7)][Rand.GetInt(0, 13)] = Rand.GetInt(0, 9);
		}
		auto n_score = GetScore(n_item);
		if (n_score > ret) {
			cout << n_score << '\n';
		}
		double p = exp(-(score - n_score) / (1.0 / (double)i) * T);
		if (p > Rand.GetDouble(0, 1)) item = n_item, score = n_score; 
		if (score > ret) {
			flag = 1;
			ret = score;
			cout << ret << '\n';
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 14; y++) {
					cout << item.m[x][y];
				}
				cout << '\n';
			}
		}
	}
}

// DB 지움.

int main() {	
	cout << "814solver" << '\n';
	
	double T = 20.0;
	double d = 0.95;
	int lim = 200000;
	int cnt = 0;
	
	while (1) {
		item.setItem(DB6);
		flag = 0;
		SA();
		
		cnt++;
		if (!flag) {
			cout << cnt << "No Get" << '\n';
			//item.setItem(DB4);
			//cnt = 0;
		}
		if (flag) cnt = 0;
	}	
	return 0;
}
