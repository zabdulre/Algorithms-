#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "quicksort.h"

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
        return (lhs.key < rhs.key);
    }
};
int main() {
    intyComp comparator;
    srand(time(NULL));
//    for (int c = 0; c < 1000000; c++){
        vector<inty> og;
    vector<inty> test;
    for (int i =0; i < 50; i++) {
        test.push_back(inty(2));
        og.push_back(inty(test[i]));
    }
    test.push_back(inty(100));
//      test.push_back(712); test.push_back(526);  test.push_back(526);  test.push_back(426); test.push_back(481); test.push_back(562);
//        test.push_back(204);
//    test.push_back(81);
//        test.push_back(958);
//    test.push_back(602);
//        test.push_back(958);
    auto start = chrono::high_resolution_clock::now();
    cout << "here";
    quicksort(test, comparator);
    cout << "done";
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() << endl;
    for (size_t i = 0; i < test.size(); i++) {
 //       cout << test[i] << " ";
        if (i < test.size() - 1){
        if (test[i].key < test[i+1].key){
            cout << boolalpha << false;
            break;
        }
        }
    }
  //  cout << endl;
    start = chrono::high_resolution_clock::now();
    cout << "here";
    quicksort(test, comparator);
    cout << "done";
    stop = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration2.count() << endl;
       for (size_t i = 0; i < test.size(); i++) {
    //       cout << test[i] << " ";
           if (i < test.size() - 1){
           if (test[i].key > test[i+1].key){
               cout << boolalpha << false;
               break;
           }
           }
       }
//
//    }
    cout << boolalpha << true;
    cout << endl;
    return 0;
}
