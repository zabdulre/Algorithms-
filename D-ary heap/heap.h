#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>


template<typename T, typename TComparator = std::less<T> >
class Heap {
public:
    // Constructs an m-ary heap for any m >= 2
    Heap(size_t m, TComparator comparator = TComparator());

    // Destructor as needed
    ~Heap();

    // Adds an item
    void push(const T& item);

    // returns the element at the top of the heap
    //  max (if max-heap) or min (if min-heap)
    const T& top() const;

    // Removes the top element
    void pop();

    // returns true if the heap is empty
    bool empty() const;

private:
    // Add whatever helper functions and data members you need below

    // heapify() helper function
    void heapify(size_t loc);
    void TrickleDown();
    void TrickleUp(size_t loc);
    size_t findRoot(size_t loc) const;
    size_t findLeaf(size_t loc) const;
    void swap(size_t loc1, size_t loc2);
    // Data
    std::vector<T> store;
    size_t m;
    TComparator comparator;
};
template<class T, class TComparator>
Heap<T, TComparator>::Heap(size_t m,TComparator comparator){
    if (m >= 2){
        this -> m = m;
    }
    else{
        this -> m = 2;
    }
    this -> comparator = comparator;
    return;
}

template<class T, class TComparator>
Heap<T, TComparator>::~Heap(){
    return;
}

template<class T, class TComparator>
const T& Heap<T, TComparator>::top() const {
    if (store.size() == 0) {throw std::logic_error("can't top an empty heap");}
    return store[0];
}

template<class T, class TComparator>
void Heap<T, TComparator>::pop() {
    if (store.size() == 0) {throw std::logic_error("can't pop an empty heap");}
    store[0] = store[store.size() - 1];
    store.pop_back();
    heapify(0);
    return;
}

template<class T, class TComparator>
bool Heap<T, TComparator>::empty() const{
    return (store.size() == 0);
}

template<class T, class TComparator>
void Heap<T, TComparator>::push(const T& item){
    store.push_back(item);
    heapify(store.size() - 1);
    return;
}

template<class T, class TComparator>
void Heap<T, TComparator>::heapify(size_t loc){
    if (loc == 0){
        if(store.size() <= 1){//no items to sort
            return;
        }
        TrickleDown();
        return;
    }
    TrickleUp(loc);
    return;
}

template<class T, class TComparator>
void Heap<T, TComparator>::TrickleUp(size_t loc){
        int i = loc;
    do{
        if (comparator(store[i], store[findRoot((size_t)i)])){
            swap(i, findRoot((size_t)i));
            i = findRoot((size_t)i);
        }
        else{
            return;
        }
    }
    while (i > 0);
    return;
}

template<class T, class TComparator>
void Heap<T, TComparator>::TrickleDown(){
    size_t i = 1;//leaf of first node
    while (i < store.size()){
        size_t min = i;
        for (int c = 1; c < m; c++){//for all leaves, find the "minimum"
            i++;
            if (i >= store.size()){
                break;
            }
            if (comparator(store[i], store[min])){
                min = i;
            }
        }
        i = findRoot(i);
        if (comparator(store[min], store[i])){
            swap(i, min);
            i = findLeaf(min);
        }
        else{
            return;
        }
    }
    return;
}

template<class T, class TComparator>
size_t Heap<T, TComparator>::findLeaf(size_t loc) const{
    size_t y = ((loc*m)+1);//debug purposes
    return y;
}

template<class T, class TComparator>
size_t Heap<T, TComparator>::findRoot(size_t loc) const{
    if (loc == 0){
        return 0;
    }
    size_t y = ((loc - 1)/m);//debug purposes
    return y;
}


template<class T, class TComparator>
void Heap<T, TComparator>::swap(size_t loc1, size_t loc2){
    T holder = store[loc1];
    store[loc1] = store[loc2];
    store[loc2] = holder;
    return;
}

#endif
