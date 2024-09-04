#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

struct Coordinate {
	double m_coor[2];
	double distance(double coor[2]);
	void Changes(double coor[2]);
};

struct PointStruct : public Coordinate {
	char m_data;
};

struct TreeNode : public PointStruct {
	int m_dimension;    //0为x方向划分，1为y方向划分
	TreeNode* m_pLeftChild;
	TreeNode* m_pRightChild;
};

struct KdTree {
	TreeNode* m_Root;
	TreeNode* buildTree(vector<PointStruct>& pList, int d);
	Coordinate* recurSearch(TreeNode* pNode, int depth, Coordinate point, Coordinate& nearest);
};

void merge(int dimension, vector<PointStruct>& pList, int lo, int mi, int hi) {
	int i = 0;
	int j = 0;
	int lb = mi - lo;
	PointStruct* A = &pList[lo];
	vector<PointStruct> B;
	for (i = 0; i < lb; i++) {
		B.push_back(A[i]);
	}
	int k = 0;
	int lc = hi - mi;
	i = 0;
	PointStruct* C = &pList[mi];
	while ((j < lb) && (k < lc)) {
		A[i++] = (B[j].m_coor[dimension] <= C[k].m_coor[dimension]) ? B[j++] : C[k++];
	}
	while (j < lb) {
		A[i++] = B[j++];
	}
}

void mergeSort(int dimension, vector<PointStruct>& pList, int lo, int hi) {
	if (hi - lo < 2)return;
	int mi = (lo + hi) >> 1;
	mergeSort(dimension, pList, lo, mi);
	mergeSort(dimension, pList, mi, hi);
	merge(dimension, pList, lo, mi, hi);
}

PointStruct findMedialPoint(int dimension, vector<PointStruct>& pList) {
	mergeSort(dimension, pList, 0, pList.size());
	return pList[int((pList.size() - 1) / 2)];
}

double Coordinate::distance(double coor[2]) {
	return sqrt(pow(m_coor[0] - coor[0], 2) + pow(m_coor[1] - coor[1], 2));
}

TreeNode* KdTree::buildTree(vector<PointStruct>& pList, int d) {
	if (pList.empty()) return NULL;
	int dimension = d % 2;
	PointStruct medianP = findMedialPoint(dimension, pList);
	vector<PointStruct> pListLeft, pListRight;
	for (int i = 0; i < pList.size(); i++) {
		if (medianP.m_coor[dimension] > pList[i].m_coor[dimension])
			pListLeft.push_back(pList[i]);
		else if (medianP.m_coor[dimension] < pList[i].m_coor[dimension])
			pListRight.push_back(pList[i]);
		else if (medianP.m_coor[!dimension] != pList[i].m_coor[!dimension])
			pListRight.push_back(pList[i]);
	}
	TreeNode* pTreeNode = new TreeNode();
	pTreeNode->Changes(medianP.m_coor);
	pTreeNode->m_data = medianP.m_data;
	pTreeNode->m_pLeftChild = buildTree(pListLeft, d + 1);
	pTreeNode->m_pRightChild = buildTree(pListRight, d + 1);
	pTreeNode->m_dimension = dimension;
	return pTreeNode;
}
void Coordinate::Changes(double coor[2]) {
	m_coor[0] = coor[0];
	m_coor[1] = coor[1];
}
Coordinate* KdTree::recurSearch(TreeNode* pNode, int depth, Coordinate point, Coordinate& nearest) {
	if (!pNode) return NULL;
	int dimension = depth % 2;
	if (point.distance(pNode->m_coor) < point.distance(nearest.m_coor)) {
		nearest.Changes(pNode->m_coor);
	}
	if (point.m_coor[dimension] < pNode->m_coor[dimension]) {
		recurSearch(pNode->m_pLeftChild, depth + 1, point, nearest);
		if (point.distance(nearest.m_coor) >= pNode->m_coor[dimension] - point.m_coor[dimension]) {
			recurSearch(pNode->m_pRightChild, depth + 1, point, nearest);
		}
	}
	else {
		recurSearch(pNode->m_pRightChild, depth + 1, point, nearest);
		if (point.distance(nearest.m_coor) >= point.m_coor[dimension] - pNode->m_coor[dimension]) {
			recurSearch(pNode->m_pLeftChild, depth + 1, point, nearest);
		}
	}
	return &nearest;
}
int main()
{
	int N = 0;
	int M = 0;
	vector<PointStruct> List;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		PointStruct* P = new PointStruct;
		cin >> P->m_coor[0] >> P->m_coor[1] >> P->m_data;
		List.push_back(*P);
	}
	KdTree K;
	K.m_Root = K.buildTree(List, 0);
	Coordinate Target;
	Coordinate Nearest;
	Nearest.Changes(K.m_Root->m_coor);
	for (int i = 0; i < M; i++) {
		cin >> Target.m_coor[0] >> Target.m_coor[1];
		K.recurSearch(K.m_Root, 0, Target, Nearest);
		printf("%.4f\n", Target.distance(Nearest.m_coor));
	}
}

