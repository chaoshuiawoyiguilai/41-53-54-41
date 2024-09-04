#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdlib>
using namespace std;

struct Node {
    int val;
    int rank;
    int operator > (const Node& temp) const
    {
        return val > temp.val;
    }
    int operator < (const Node& temp) const
    {
        return val < temp.val;
    }
};
int Add(priority_queue<Node>* max, priority_queue<Node, vector<Node>, greater<Node>>* min, int dimension, int id, int* point) {
    long sum;
    int p;
    int out = 0;
    Node x;
    for (int i = 0; i < (1 << dimension); i++) {
        sum = 0;
        p = i;
        for (int j = 0; j < dimension; j++) {
            if (p & 1) {
                sum += point[j];
            }
            else {
                sum -= point[j];
            }
            p >>= 1;
        }
        x.rank = id;
        x.val = sum;
        max[i].push(x);
        min[i].push(x);
        if (out < max[i].top().val - min[i].top().val) {
            out = max[i].top().val - min[i].top().val;
        }
    }
    return out;
}

int Delete(priority_queue<Node>* max, priority_queue<Node, vector<Node>, greater<Node>>* min, int dimension, int id, int* point) {
    point[id - 1] = 1;
    Node h, l;
    int out = 0;
    for (int i = 0; i < (1 << dimension); i++) {
        h = max[i].top();
        l = min[i].top();
        while (point[h.rank - 1]) {
            max[i].pop();
            h = max[i].top();
        }
        while (point[l.rank - 1]) {
            min[i].pop();
            l = min[i].top();
        }
        if (max[i].size() <= 1) {
            out = 0;
        }
        else {
            if (out < h.val - l.val) {
                out = h.val - l.val;
            }
        }
    }
    return out;
}



int main() {
    long n;
    int d;
    int symbol;
    int id;
    cin >> n >> d;
    int* list = new int[n];
    for (int i = 0; i < n; i++) {
        list[i] = 0;
    }
    int* coor = new int[d];
    priority_queue <Node>* max = new priority_queue <Node>[1 << d];
    priority_queue < Node, vector<Node>, greater<Node> >* min = new priority_queue < Node, vector<Node>, greater<Node> >[1 << d];
    vector<int> result;
    for (int i = 1; i <= n; i++) {
        cin >> symbol;
        if (symbol == 1) {
            cin >> id;
            result.push_back(Delete(max, min, d, id, list));
        }
        else {
            for (int j = 0; j < d; j++) {
                cin >> coor[j];
            }
            result.push_back(Add(max, min, d, i, coor));
        }
    }
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
 }

//参考https://www.cnblogs.com/wangfang20/p/3257217.html