#include <iostream>
#include <vector>
#include <stack>
using namespace std;

enum VStatus {UNDISCOVERED,DISCOVERED};

struct Vertex {
	int data;
	int inDegree;
	VStatus status;
	vector<int> ancestors;
	Vertex(int const& d = 0) :data(d), inDegree(0), status(UNDISCOVERED) {}
	
};

struct Edge {
	int end;
};

struct Graph : public Vertex, public Edge {
	vector<Vertex> V;
	vector<vector<Edge>> E;
	bool Iscircle();
	bool Isancestor(int A, int B);
};

bool Graph:: Iscircle() {
	stack<int> S;
	int s;
	for (int i = 0; i < V.size(); i++) {
		if (V[i].inDegree == 0) {
			S.push(i);
		}
	}
	if (S.size() == 0) {
		return true;
	}
	while (!S.empty()) {
		s = S.top();
		S.pop();
		V[s].status = DISCOVERED;
		for (int i = 0; i < E[s].size(); i++) {
			int u = E[s][i].end;
			for (int j = 0; j < V[s].ancestors.size(); j++) {
				V[u].ancestors.push_back(V[s].ancestors[j]);
			}
			V[u].ancestors.push_back(s);
			if (V[u].status == UNDISCOVERED) {
				if ((--V[u].inDegree == 0)) {
					S.push(u);
				}
			}
		}
	}
	for (int i = 0; i < V.size(); i++) {
		if (V[i].status != DISCOVERED) {
			return true;
		}
	}
	return false;
}

bool Graph::Isancestor(int A, int B) {
	for (int i = 0; i < V[B].ancestors.size(); i++) {
		if (V[B].ancestors[i] == A) {
			return true;
		}
	}
	return false;
}

int main()
{
	Graph G;
	Edge edge;
	int N, M, K;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		G.V.push_back(Vertex(i));
	}
	G.E.clear();
	G.E.resize(N + 1);
	for (int i = 0; i < M; i++) {
		int V1, V2;
		cin >> V1 >> V2;
		edge.end = V2;
		G.E[V1].push_back(edge);
		G.V[V2].inDegree += 1;
	}
	if (G.Iscircle()) {
		cout << "-1" << endl;
	}
	else {
		for (int i = 0; i < K; i++) {
			int V1, V2;
			cin >> V1 >> V2;
			if (G.Isancestor(V1, V2)) {
				cout << "1" << endl;
			}
			else if (G.Isancestor(V2, V1)) {
				cout << "-1" << endl;
			}
			else {
				cout << "0" << endl;
			}
		}
	}
}


