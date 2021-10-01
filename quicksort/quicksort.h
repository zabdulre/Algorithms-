#ifndef QSORT_H
#define QSORT_H

#include <vector>
#include <algorithm>

template<class T, class TComparator>
void swap(T& a, T& b){
    T holder = a;
    a = b;
    b = holder;
    return;
}
template<class T, class TComparator>
T& median_of_three(T& a, T& b, T& c, TComparator comparator) {
    // TODO: implement.
//    T arr[3];
//    arr[0] = a; arr[1] = b; arr[2] = c;
//    char arr2[3]; arr2[0] = 'a'; arr2[1] = 'b'; arr2[2] = 'c';
//    for (int i = 1; i < 3; i++){//insertion sort
//        int y = i;
//        while ((comparator(arr[y-1], arr[y])) && y >= 1){
//            T holder = arr[y];//swap
//            char holder2 = arr2[y];//not using swap function to make the intention of arr2 clear
//            arr[y] = arr[y-1];
//            arr2[y] = arr2[y-1];
//            arr[y-1] = holder;
//            arr2[y-1] = holder2;
//            y--;
//        }
//    }
//    switch(arr2[1]){
//        case 'a':
//            return a;
//        case 'b':
//            return  b;
//        case 'c':
//            return c;
//    }
//    return b;//to avoid compiler warnings
    if (comparator(a, b)){
        if (comparator(b, c)){
            return b;
        }
        else {return c;}
    }
    else{
        if (comparator(a, c)){
            return a;
        }
        else{return b;}
    }
}

template<class T, class TComparator>
size_t partition(std::vector<T>& vec, TComparator& comparator, size_t low, size_t high) {//all things smaller than pivot on left
    if (high - low == 1){//if array is of size 2
        if (comparator(vec[high], vec[low]))
            swap<T, TComparator>(vec[high], vec[low]);
        return high;
    }
    T* pivot = &median_of_three<T, TComparator>(vec[low], vec[((low+high)/2)], vec[high], comparator);//might be prob here
    swap<T, TComparator>(vec[(pivot == &vec[low])? low: (pivot == &vec[(low+high)/2])? (low+high)/2: high], vec[high]);//put the pivot at the highest index
    pivot = &vec[high];
    size_t indexBottom = low;
    size_t indexTop = high - 1;
    while (indexBottom <= indexTop){
        if (comparator(vec[indexBottom], *pivot)){
            indexBottom++;
         }
        else{
                while (comparator(*pivot, vec[indexTop]) && (indexTop > indexBottom)){
                    indexTop--;
                }
                swap<T, TComparator>(vec[indexBottom], vec[indexTop]);
                if (indexTop <= indexBottom){break;}
                indexTop--;
                indexBottom++;
            }
        }
//    if (indexBottom == 0){
//        if (comparator(vec[indexBottom + 1], *pivot)){
//            swap<T, TComparator>(vec[indexBottom + 1], vec[indexBottom + 2]);
//        }
//    }
 //   if (indexBottom == 0 && comparator(vec[indexBottom], *pivot)){indexBottom++;}
  //  if (indexBottom == 0 && !comparator(vec[indexBottom], *pivot)){swap<T, TComparator>(vec[0], vec[high]);}

    if (indexBottom == 0 && !comparator(vec[indexBottom + 1], *pivot)){
        indexBottom++; swap<T, TComparator>(vec[indexBottom], vec[indexBottom + 1]);
        if (comparator(vec[0], *pivot)){indexBottom++;}
        else if (comparator(*pivot, vec[0])){indexBottom = 0;}
    }
 //   else if(indexBottom == 0){indexBottom+= 2;}
//    else if(indexBottom == 0){indexBottom++; swap<T, TComparator>(vec[indexBottom], vec[indexBottom + 1]); indexBottom++;}
    swap<T, TComparator>(vec[indexBottom], vec[high]);//swap pivot into correct position
    if (indexBottom == 0){indexBottom++;}
    return indexBottom;
}

template<class T, class TComparator>
void QuickSortHelper(std::vector<T>& vec, size_t left, size_t right, TComparator& comparator){
    if (left >= right){
        return;
    }
    size_t sortedUpTo = partition(vec, comparator, left, right);
    QuickSortHelper(vec, left, sortedUpTo - 1, comparator);
    QuickSortHelper(vec, sortedUpTo + 1, right, comparator);//break up the arrays
    return;
}

template<class T, class TComparator>
void quicksort(std::vector<T>& vec, TComparator comparator) {
    // TODO: implement.
    if (vec.size() > 1){
        QuickSortHelper(vec, 0, vec.size() - 1, comparator);}
    return;
}




#endif
