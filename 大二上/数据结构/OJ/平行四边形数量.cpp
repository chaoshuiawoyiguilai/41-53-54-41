#include <iostream>
#include <vector>
#include <string.h>
#define MD 199997
using namespace std;

int harsh[MD];
struct POINT {
	int X;
	int Y;
	int dX;
	int dY;
	POINT(int x = 0, int y = 0, int dx = 0, int dy = 0) :X(x), Y(y), dX(dx), dY(dy) {}
};

void harshing(int t, vector<POINT>& mid) {
	int key = (((mid[t].X) * 1000 + (mid[t].Y) * 1234) % MD + MD) % MD;
	while (harsh[key] >= 0) {
		key = (key + 1) % MD;
	}
	harsh[key] = t;
}

int searching(POINT po, vector<POINT>& mid) {
	int num = 0;
	int key = ((po.X * 1000 + po.Y * 1234) % MD + MD) % MD;
	while (harsh[key] >= 0) {
		int t = harsh[key];
		if (mid[t].X == po.X && mid[t].Y == po.Y && mid[t].dX * po.dY != po.dX * mid[t].dY) {
			num++;
		}
		key = (key + 1) % MD;
	}
	return num;
}

int main()
{
	int n;
	vector<POINT> p;
	vector<POINT> mid;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m;
		int num = 0, q = 0;
		cin >> m;
		memset(harsh, -1, sizeof(harsh));
		p.clear();
		mid.clear();
		for (int j = 0; j < m; j++) {
			int x, y;
			cin >> x >> y;
			p.push_back(POINT(x, y));
			for (int t = 0; t < j; t++, q++) {
				mid.push_back(POINT(x + p[t].X, y + p[t].Y, x - p[t].X, y - p[t].Y));
				harshing(q, mid);
			}
		}
		for (int j = 0; j < mid.size(); j++) {
			num += searching(mid[j], mid);
		}
		cout << num / 2 << endl;
	}
}

