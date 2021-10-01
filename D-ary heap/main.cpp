#include <vector>
#include <functional>
#include <iostream>
#include <cstdlib>
#include "heap.h"

using namespace std;

class inty{
    public:
    inty(int key1){this -> key = key1;}
    inty(const inty& rhs){
        this -> key = rhs.key;
    }
    int key;
};

struct intyComp{
    bool operator()(const inty&lhs, const inty&rhs){
        return (lhs.key > rhs.key);
    }
};

int main() {
    Heap<inty, intyComp> max_heap(2);
    srand(time(0));
    for(size_t i = 0; i < 20; i++) {
        max_heap.push(inty(rand() % 100));
    }

    while (!max_heap.empty()) {
        cout << max_heap.top().key << " ";
        max_heap.pop();
    }
    cout << endl;

    Heap<int> min_heap(3);

    for (size_t i = 0; i < 22; i++) {
        min_heap.push(rand() % 100);
    }

    while (!min_heap.empty()) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    cout << endl;

    return 0;
}
