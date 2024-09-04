#include <iostream>
using namespace std;

struct ListNode {
    int data;
    ListNode* succ;
};

int main()
{
    int M;
    int N;
    cin >> N >> M;
    ListNode* head = new ListNode;
    ListNode* p = head;
    ListNode* q = head;
    p->data = 1;
    for (int i = 2; i <= N; i++) {
        q = new ListNode;
        q->data = i;
        p->succ = q;
        p = q;
    }
    p->succ = head;
    p = head;
    while (N > 1) {
        for (int i = 1; i < M; i++) {
            p = p->succ;
            q = q->succ;
        }
        p = p->succ;
        q->succ = p;
        N--;
    }
    cout << p->data << endl;
}
