//
//  main.cpp
//  405A-GravityFlip
//
//  Created by Zaid Abdulrehman on 7/15/21.
//  Copyright © 2021 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>

using namespace std;

void printArray(int** array, int numberOfColumns){
    for (int c = 4; c >= 0; c--){
        for (int i = 0 ; i < numberOfColumns; i++){
            cout << array[i][c];
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    
    //setting up variables
    int numberOfColumns = 0;
    cin >> numberOfColumns;
    int** array =  new int*[numberOfColumns];
    int* scores = new int[numberOfColumns];
    
    //filling up the boxes
    for (int i = 0; i < numberOfColumns; ++i){
        cin >> scores[i];
        array[i] = new int[100];
        for (int c = 0; c < scores[i]; c++){//stacking boxes from bottom to top
            array[i][c] = 1;
        }
        for (int c = scores[i]; c < 100; c++){//filling up empty space
            array[i][c] = 0;
        }
    }
    
    
    //start from the bottom left, move each box to the right until you hit the end or you hit another box
    
   // printArray(array, numberOfColumns);
    
    for (int i = (numberOfColumns - 2); i >= 0; i--){//start from the right
        for (int c = 0; c < 100; c++){
            if (array[i][c] == 0) break;
            int j = i;
            while (array[j][c] == 1){//if there is a box, move it to the right
                if ((j == (numberOfColumns - 1)) || (array[j + 1][c] == 1)){
                    scores[i]--;
                    scores[j]++;
                    break;
                }//reached the end or a box
                else{
                    array[j][c] = 0;//remove the box
                    j++;
                    array[j][c] = 1;//move the box
                }//this code is here for clarity, not needed
            }
            //printArray(array, numberOfColumns);
        }
    }
    
    
    for (int i = 0; i < numberOfColumns; ++i){
        cout << scores[i] << " ";
        delete[] array[i];
    }
    
    delete[] array;
    
    delete[] scores;
    
    return 0;
}
