#include<iostream>
#include<queue>
using namespace std;

int IsVisited[201][201] = { 0 };
struct Point
{
	int X;
	int Y;
	int Length = 0;

	Point(int x, int y) :X(x), Y(y) {
	}
};
bool IsInRange(int x, int y)
{
	return x >= -100 && x <= 100 && y >= -100 && y <= 100;
}
void FindMinPath(queue<Point>Que, int n, Point* Cave, int x_final, int y_final)
{
	int NextPoint_X[8] = { 1,1,-1,-1,2,2,-2,-2 };
	int NextPoint_Y[8] = { 2,-2,2,-2,1,-1,1,-1 };
	Que.push(Point(0, 0));
	int t_x, t_y, t_len;
	int IsFound = 0;
	while (!Que.empty())
	{
		t_x = Que.front().X;
		t_y = Que.front().Y;
		t_len = Que.front().Length;
		Que.pop();
		for (int i = 0; i < 8; i++)
		{
			bool IsSafe = true;
			for (int j = 0; j < n; j++)
			{
				if (t_x + NextPoint_X[i] == Cave[j].X && t_y + NextPoint_Y[i] == Cave[j].Y)
				{
					IsSafe = false;
					break;
				}
			}
			if (IsSafe && IsInRange(t_x + NextPoint_X[i], t_y + NextPoint_Y[i]) && IsVisited[100 + t_x + NextPoint_X[i]][100 + t_y + NextPoint_Y[i]] == 0)

			{
				Point P = Point(t_x + NextPoint_X[i], t_y + NextPoint_Y[i]);
				P.Length = t_len + 1;
				Que.push(P);
				IsVisited[100 + t_x + NextPoint_X[i]][100 + t_y + NextPoint_Y[i]] = 1;
				if (t_x + NextPoint_X[i] == x_final && t_y + NextPoint_Y[i] == y_final)
				{
					cout << P.Length;
					IsFound = 1;
					break;
				}
			}
		}
		if (IsFound)break;
	}
	if (IsFound == 0)
		cout << "fail" << endl;
}


int main()
{
	int x_final, y_final;
	cin >> x_final >> y_final;
	int n;
	cin >> n;
	Point* Cave = (Point*)malloc( n* sizeof(Point));
	for (int i = 0; i < n; i++)
	{
		cin >> Cave[i].X >> Cave[i].Y;
	}

	queue<Point> Q;
	FindMinPath(Q, n, Cave, x_final, y_final);
	free(Cave);
	Cave = NULL;
	return 0;

}