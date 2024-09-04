#include <iostream>
using namespace std;

struct Human {
    int num;
    int weight;
    int start;
    int time;
    int end;
    struct Human* next;
};

int main()
{
    int N;
    int M_max;
    cin >> N >> M_max;
    Human* head = new Human;
    Human* p = head;
    Human* q = head;
    q->num = 1;
    cin >> q->weight >> q->start >> q->time;
    q->end = q->start + q->time;
    for (int i = 2; i <= N; i++) {
        q = new Human;
        q->num = i;
        cin >> q->weight >> q->start >> q->time;
        q->end = q->start + q->time;
        p->next = q;
        p = q;
    }
    p = head;
    q = p;
    int Weight = p->weight;
    while (true) {
        if (Weight > M_max) {
            cout << q->num << endl;
            break;
        }
        if (q->next == NULL) {
            cout << "safe" << endl;
            break;
        }
        if (q->next->end < q->end) {
            q->next->end = q->end;
        }
        q = q->next;
        Weight = Weight + q->weight;
        while (p->end <= q->start) {
            Weight = Weight - p->weight;
            p = p->next;
        }

    }
    
}



