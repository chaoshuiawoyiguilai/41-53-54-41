#include <iostream>
#include <stack>
#include <vector>
using namespace std;
enum RBColor { RED, BLACK };

struct BinNode {
	int money;
	int height;
	int num;
	BinNode* lc;
	BinNode* rc;
	BinNode* parent;
	RBColor color;
	BinNode(int e = -1, int h = -1, int n = 0, BinNode* p = NULL, BinNode* lc = NULL, BinNode* rc = NULL, RBColor c = RED) :
		money(e), height(h), num(n), parent(p), lc(lc), rc(rc), color(c) {};
};


struct RedBlack :public BinNode {
	int _size;
	int _plus;
	BinNode* _root;
	BinNode* _hot;
	RedBlack(int s = 0, int plus = 0, BinNode* r = NULL, BinNode* hot = NULL) : _size(s), _plus(plus), _root(r), _hot(hot) {};
	bool BlackHeightUpdated(BinNode* x);
	int updatedHeight(BinNode* x);
	void updatedNum(BinNode* x);
	BinNode* connect34(BinNode* a, BinNode* b, BinNode* c, BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3);
	BinNode* rotateAt(BinNode* x);
	BinNode* removeAt(BinNode* x, BinNode* hot);
	void remove(BinNode* x);
	void solveDoubleRed(BinNode* x);
	void solveDoubleBlack(BinNode* x);
	void Event1(int e);
	void Event2(int e);
	int Event3(int e);
	int Event4(int k);
};


bool RedBlack::BlackHeightUpdated(BinNode* x) {
	if (!x->lc) {
		if ((!x->rc || x->rc->height == -1) && (x->height) == (x->color == RED ? -1 : 0))
			return true;
	}
	else if (!x->rc) {
		if ((x->lc->height == -1) && (x->height) == (x->color == RED ? -1 : 0))
			return true;
	}
	else {
		if ((x->lc->height == x->rc->height) && (x->height) == (x->color == RED ? x->lc->height : x->lc->height++))
			return true;
	}
	return false;
}


int RedBlack::updatedHeight(BinNode* x) {
	if (x->lc == NULL) {
		x->height = (x->rc == NULL) ? -1 : x->rc->height;
	}
	else {
		x->height = (x->rc == NULL) ? x->lc->height : max((x->lc)->height, (x->rc)->height);	
	}
	return (x->color == BLACK) ? x->height++ : x->height;
}

void RedBlack::updatedNum(BinNode* x) {
	if (x->lc == NULL) {
		x->num = (x->rc == NULL) ? 1 : x->rc->num + 1;
	}
	else {
		x->num = (x->rc == NULL) ? x->lc->num + 1 : x->lc->num + x->rc->num + 1;
	}
}

BinNode* RedBlack::connect34(BinNode* a, BinNode* b, BinNode* c, BinNode* T0, BinNode* T1, BinNode* T2, BinNode* T3) { 
	a->lc = T0; if (T0) T0->parent = a;
	a->rc = T1; if (T1) T1->parent = a;
	updatedHeight(a); 
	updatedNum(a);
	c->lc = T2; if (T2) T2->parent = c;
	c->rc = T3; if (T3) T3->parent = c;
	updatedHeight(c);
	updatedNum(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b;
	updatedHeight(b); 
	updatedNum(b);
	return b; 
}

BinNode* RedBlack::rotateAt(BinNode* v) {
	BinNode* p = v->parent;
	BinNode* g = p->parent;
	if (p == g->lc) {
		if (v == p->lc) { 
			p->parent = g->parent; 
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else { 
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else {
		if (v == p->rc) {
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else {
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}

}


BinNode* RedBlack::removeAt(BinNode* x, BinNode* hot) {
	BinNode* w = x; 
	BinNode* succ = NULL; 
	if (x->lc == NULL) {
		BinNode* u = x->parent;
		if (u) {
			((u->rc == x) ? u->rc : u->lc) = succ = x->rc;
		}
		else {
			_root = succ = x->rc;
		}
	}
	else if (x->rc == NULL) {
		BinNode* u = x->parent;
		if (u) {
			((u->rc == x) ? u->rc : u->lc) = succ = x->lc;
		}
		else {
			_root = succ = x->lc;
		}
	}
	else { 
		w = w->rc;
		while (w->lc) {
			w = w->lc;
		}
		swap(x->money, w->money);     
		BinNode* u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;
		
	}
	hot = w->parent;
	if (succ) succ->parent = hot;
	w->parent = NULL;
	w->lc = NULL;
	w->rc = NULL;
	delete w;
	return succ;
}


void RedBlack::remove(BinNode* x) {
	BinNode* r = removeAt(x, _hot);
	if (!(--_size)) return;
	if (!_hot) {
		_root->color = BLACK;
		updatedHeight(_root);
		return;
	}
	BinNode* t = _hot;
	while (t) {
		updatedNum(t);
		t = t->parent;
	}
	if (BlackHeightUpdated(_hot)) {
		return;
	}
	if (r) {
		if (r->color == RED) {
			r->color = BLACK;
			r->height++;
			return;
		}
	}
	solveDoubleBlack(r);
	return;
}

void RedBlack::solveDoubleRed(BinNode* x) {
	if (x == _root) {
		_root->color = BLACK;
		_root->height++;
		return;
	}
	BinNode* p = x->parent;
	if (!p || p->color == BLACK) {
		return;
	}
	BinNode* g = p->parent;
	BinNode* u = (p == g->lc) ? g->rc : g->lc;
	if (!u || u->color == BLACK) {
		if ((x == p->lc) == (p == g->lc)) {
			p->color = BLACK;
		}
		else {
			x->color = BLACK;
		}
		g->color = RED;
		BinNode* gg = g->parent;
		if (!gg) {
			_root = rotateAt(x);
		}
		else {
			BinNode* r = rotateAt(x);
			if (g == gg->lc)
				gg->lc = r;
			else
				gg->rc = r;
			r->parent = gg;
		}
	}
	else {
		p->color = BLACK;
		p->height++;
		u->color = BLACK;
		u->height++;
		if (g != _root) {
			g->color = RED;
		}
		solveDoubleRed(g);
	}
}

void RedBlack::solveDoubleBlack(BinNode* x) {
	BinNode* p = x ? x->parent : _hot;
	if (!p) return;
	BinNode* s = (x == p->lc) ? p->rc : p->lc;
	if (s->color == BLACK) {
		BinNode* t = NULL;
		if (s->rc) {
			if (s->rc->color == RED) {
				t = s->rc;
			}
		}
		if (s->lc) {
			if (s->lc->color == RED) {
				t = s->lc;
			}
		}
		if (t) {
			RBColor oldColor = p->color;
			BinNode* g = p->parent;
			BinNode* b = rotateAt(t);
			b->parent = g;
			if (g) {
				if (p == g->lc)
					g->lc = b;
				else
					g->rc = b;
			}
			else {
				_root = b;
			}
			if (b->lc) {
				b->lc->color = BLACK;
				updatedHeight(b->lc);
			}
			if (b->rc) {
				b->rc->color = BLACK;
				updatedHeight(b->rc);
			}
			b->color = oldColor;
			updatedHeight(b);
		}
		else {
			s->color = RED;
			s->height--;
			if (p->color == RED) {
				p->color = BLACK;
			}
			else {
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}
	else {
		s->color = BLACK;
		p->color = RED;
		BinNode* t = (s == p->lc) ? s->lc : s->rc;
		_hot = p;
		BinNode* g = p->parent;
		BinNode* b = rotateAt(t);
		b->parent = g;
		if (g) {
			if (p == g->lc)
				g->lc = b;
			else
				g->rc = b;
		}
		else {
			_root = b;
		}
		solveDoubleBlack(x);
	}
}

void RedBlack::Event1(int e) {
	e = e - _plus;
	if (!_root) {
		_root = new BinNode(e);
		_size++;
		solveDoubleRed(_root);
	}
	else {
		BinNode* v = _root;
		_hot = NULL;
		while (v) {
			if (e < v->money) {
				_hot = v;
				v = v->lc;
			}
			else {
				_hot = v;
				v = v->rc;
			}
		}
		BinNode* t = new BinNode(e, -1, 1, _hot);
		if (e < _hot->money) {
			_hot->lc = t;
		}
		else {
			_hot->rc = t;
		}
		_size++;
		BinNode* p = t->parent;
		while (p) {
			updatedNum(p);
			p = p->parent;
		}
		solveDoubleRed(t);
	}
}

void RedBlack::Event2(int e) {
	_plus += e;
}

int RedBlack::Event3(int e) {
	e = e - _plus;
	BinNode* x = _root;
	int n = 0;
	while (true) {
		x = _root;
		if (x) {
			while (x->lc) {
				x = x->lc;
			}
			if (x->money <= e) {
				_hot = x->parent;
				n++;
				remove(x);
			}
			else break;
		}
		else break;
	}
	return n;
}

int RedBlack::Event4(int k) {
	if (k > _size) {
		return -1;
	}
	else {
		BinNode* x = _root;
		while (x) {
			if (x->rc) {
				if (k == x->rc->num + 1) {
					return x->money + _plus;
				}
				else if (k < x->rc->num + 1) {
					x = x->rc;
				}
				else {
					k = k - x->rc->num - 1;
					x = x->lc;
				}
			}
			else {
				if (k == 1) {
					return x->money + _plus;
				}
				else {
					k = k - 1;
					x = x->lc;
				}
			}
		}
	}
}

int main()
{
	int k;
	cin >> k;
	int t, x;
	RedBlack q;
	q._root = new BinNode(0, 0, 1, NULL, NULL, NULL, BLACK);
	q._size = 1;
	for (int i = 0; i < k; i++) {
		cin >> t >> x;
		switch (t) {
		case(1): q.Event1(x); break;
		case(2): q.Event2(x); break;
		case(3): {
			int n;
			n = q.Event3(x);
			cout << n << endl;
			break;
		}
		case(4): {
			int m;
			m = q.Event4(x);
			cout << m << endl;
			break;
		}
		}
	}
}

