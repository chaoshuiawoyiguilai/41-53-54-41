#include <iostream>
#include <math.h>
#include <stack>
using namespace std;

struct BinTree {
	int data;
	BinTree* lc = NULL;
	BinTree* rc = NULL;
};

BinTree* Insert(BinTree* root,int x) {
	if (root == NULL) {
		root = new BinTree;
		root->data = x;
		return root;
	}
	else if (x > root->data) {
		root->rc = Insert(root->rc, x);
		return root;
	}
	else {
		root->lc = Insert(root->lc, x);
		return root;
	}
}
//BinTree* Search(BinTree* p, int x, int y) {
//	if (y < p->data) {
//		Search(p->lc, x, y);
//	}
//	else if (x > p->data) {
//		Search(p->rc, x, y);
//	}
//	else {
//		return p;
//	}
//}
int Height(BinTree* x) {
	stack<BinTree*> S;
	int H = 0;
	int h = 0;
	while (true) {
		while (x) {
			S.push(x);
			x = x->lc;
			h++;
			if (h > H)H = h;
		}
		while (true) {
			x = S.pop();
			h--;
			if (!x->rc) {
				S.push(x);
				h++;
				x = x->rc;
				break;
			}
		}
		if (S.empty())break;
	}
	return H;
}
int main()
{
	int N;
	int M;
	int data;
	int a;
	int b;
	cin >> N >> M;
	BinTree* root = NULL;
	BinTree* parent;
	for (int i = 0; i < N; i++) {
		cin >> data;
		root = Insert(root, data);
	}
	int height;
	height = Height(root);
	//for (int i = 0; i < M; i++) {
	//	cin >> a >> b;
	//	parent = Search(root, min(a, b), max(a, b));
	//	cout << parent->data << endl;
	//}
}

