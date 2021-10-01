//
//  main.cpp
//  1506A-StrangeTable
//
//  Created by Zaid Abdulrehman on 7/18/21.
//  Copyright © 2021 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    long long int numberOfTestCases = 0;
    std::cin >> numberOfTestCases;
    for (long long int i = 0; i < numberOfTestCases; i++){
        long long int rows = 0;
        long long int columns = 0;
        long long int cellNumber = 0;
        std::cin >> rows;
        std::cin >> columns;
        std::cin >> cellNumber;
        //find out the row and column of the cell
        long long int actualColumn = cellNumber/rows;//0 indexed
        long long int actualRow = (cellNumber - (actualColumn * rows));
        if (actualRow == 0){actualRow = rows;
            actualColumn -= 1;
        }
        //convert to numbering by columns
        std::cout << ((actualRow - 1)*columns + (actualColumn + 1)) << std::endl;
    }
    return 0;
}
