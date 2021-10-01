//
//  main.cpp
//  merge sort
//
//  Created by Zaid Abdulrehman on 10/5/20.
//  Copyright © 2020 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>
#include <ctime>

using namespace std;

void InsertionSort(int a[], int len) {
     for (int i = 0; i < len - 1; i++){
         int j = i;
         while(a[j + 1] < a[j] && (j > -1)){
//         swap(a[j+1], a[j]);
             int c = a[j];
                a[j] = a[j + 1];
                a[j+1] = c;
         j--;
         }
     }
    return;
}

void swap(int& a, int& b){
int c = a;
a = b;
b = c;
return;}

void Merge(int arr[], int low, int mid, int high) {
    //Use 'temp' as an array of size high-low+1, for temporary memory.
    //If you haven't taken 103 yet, you are not expected to understand this.
    int *temp = new int[high-low+1];
    
    //Your code here.
//    cerr<< endl;
//    for (int i = 0; i < high-low + 1; i++){
//    temp[i] = arr[i + low];
//    cerr << temp[i] << " ";}//make copy
//     cerr<< endl;
    int arrIndex = low;
    int j = mid + 1;
    int k = 0;
    while (arrIndex <= mid && j <= high && k < (high - low + 1))
    {
    if (arr[arrIndex] <= arr[j]){
        temp[k] = arr[arrIndex];
         arrIndex++;
         k++;
    }
    else{
        temp[k] = arr[j];
        j++;
        k++;}
    }
    int h = mid - (arrIndex) + 1; int y = high - j + 1;
    if (h > 0){
        for (int i = 0; i < h; i++){
        temp[k] = arr[(arrIndex)];arrIndex++;k++;
        }
    }
    else{
    for(int i = 0; i < y; i++){
    
        temp[k] = arr[(j)]; j++; k++;}
    }
    
    for (int c = 0; c < high-low+1; c++){
    arr[low+c] = temp[c];}
//    while (((arrIndex <= high))){
//    arr[arrIndex] = ((temp[tempLower] > temp[tempHigher])? temp[tempLower]:temp[tempHigher]);
//    if ((temp[tempLower] < temp[tempHigher])){tempLower++;}else if ((temp[tempLower] >= temp[tempHigher])){tempHigher++;}
//        if (tempLower == mid-low){tempLower = tempHigher;} else if (tempHigher == high-low+1){tempHigher = tempLower;}
//    cerr << "/" << arr[arrIndex];arrIndex++;}
//    for (int i = 0 ; i < high; i++){
//    if ((tempHigher == (high - low + 1))){arr[arrIndex] = temp[tempLower]; tempLower++; arrIndex++;}
//    else if  ((temp[tempLower] < temp[tempHigher] && tempLower != mid-low)){arr[arrIndex] = temp[tempLower]; tempLower++; arrIndex++;}
//    else{arr[arrIndex] = temp[tempHigher]; tempHigher++; arrIndex++;}}
    delete [] temp;
    return;
}

void MergeSort(int arr[], int low, int high) {
    if ((high - low) <= 0){return;}
    int m = (high+low)/2;
    MergeSort(arr, low, m);
    MergeSort(arr, m + 1, high);
    Merge(arr,low,m,high);
    return;
}

int main(int argc, char* argv[]) {
    int n;
    clock_t start;
    double durationI = 0, durationM = 0;

    cin >> n;
    int *arr = new int[n];
    int *backup = new int[n];
    for (int i = 0; i < n; i++) {
        if (n < 100) cin >> arr[i];
        else arr[i] = n-i;
        backup[i] = arr[i];
    }
    
    start = clock();
    InsertionSort(arr, n);
    durationI += ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    if (n < 100) {
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
    }

    for (int j = 0; j < n; j++) arr[j] = backup[j];

    start = clock();
    MergeSort(arr, 0, n-1);
    durationM += ( clock() - start ) / (double) CLOCKS_PER_SEC;

    if (n < 100) {
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;
    }

    if (n >= 100) {
        cout << "MergeSort on " << n << " elements took " << durationM << " seconds." << endl;
        cout << "InsertionSort took " << durationI << " seconds." << endl;
    }
    
    delete [] arr;
    delete [] backup;
    return 0;
}
