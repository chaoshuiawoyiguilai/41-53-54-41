#include <iostream>
#include <vector>
#include <stack>
using namespace std;

enum VStatus { UNDISCOVERED, DISCOVERED };
enum Strenthen { PHYSICS, MAGIC, NO };

struct Vertex {
	int data;
	int outDegree;
	int maxhurt;
	int hurt;
	int kind;
	VStatus status;
	Strenthen type;
	Vertex(int const& d = 0) :data(d), outDegree(0), maxhurt(0),
		hurt(0), kind(2), status(UNDISCOVERED), type(NO) {}
};

struct Edge {
	int start;
};


vector<Vertex> sort(vector<Vertex> V, vector<vector<Edge>> E) {
	stack<int> S;
	vector<Vertex> que;
	int s;
	for (int i = 0; i < V.size(); i++) {
		if (V[i].outDegree == 0) {
			S.push(i);
			que.push_back(V[i]);
		}
	}
	while (!S.empty()) {
		s = S.top();
		S.pop();
		V[s].status = DISCOVERED;
		for (int i = 0; i < E[s].size(); i++) {
			int u = E[s][i].start;
			if (V[u].status == UNDISCOVERED) {
				if ((--V[u].outDegree == 0)) {
					S.push(u);
					que.push_back(V[u]);
				}
			}
		}
	}
	return que;
}


int GetMaxHurt(vector<Vertex> V, vector<vector<Edge>> E, int i) {
	int max = 0; 
	int temp = 0;
	for (int k = 0; k < E[V[i].data].size(); k++) {
		int t =  V[E[V[i].data][k].start].maxhurt;
		if (t > temp) {
			temp = t;
		}
	}
	if (V[i].type == NO) {
		temp = temp + V[i].hurt;
	}
	else if (V[i].type == V[i].kind) {
		temp = temp + 2 * V[i].hurt;
	}
	if (temp > max) {
		max = temp;
	}
	return max;
}

int main()
{
	vector<Vertex> V;
	vector<vector<Edge>> E;
	Edge edge;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		V.push_back(Vertex(i));
	}
	E.clear();
	E.resize(n + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int relation;
			cin >> relation;
			if (relation == 1) {
				edge.start = i;
				E[j].push_back(edge);
				V[i].outDegree += 1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		int c, t;
		cin >> c >> t;
    	V[i].hurt = c;
    	V[i].kind = t;
	}
	vector<Vertex> que;
	que = sort(V, E);
	int max = 0;
	for (int j = 0; j < que.size(); j++) {
		V[que[j].data].type = PHYSICS;
		for (int i = que.size() - 1; i > -1; i--) {
			V[que[i].data].maxhurt = GetMaxHurt(V, E, que[i].data);
			if (V[que[i].data].maxhurt > max) {
				max = V[que[i].data].maxhurt;
			}
		}
	}
	for (int j = 0; j < V.size(); j++) {
		V[j].type = NO;
	}
	for (int j = 0; j < que.size(); j++) {
		V[que[j].data].type = MAGIC;
		for (int i = que.size() - 1; i > -1; i--) {
			V[que[i].data].maxhurt = GetMaxHurt(V, E, que[i].data);
			if (V[que[i].data].maxhurt > max) {
				max = V[que[i].data].maxhurt;
			}
		}
	}
	cout << max << endl;
}


