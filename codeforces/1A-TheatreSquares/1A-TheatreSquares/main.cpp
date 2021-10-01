//
//  main.cpp
//  1A-TheatreSquares
//
//  Created by Zaid Abdulrehman on 7/15/21.
//  Copyright © 2021 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>
#include <cmath>

int main(int argc, const char * argv[]) {
    long long int length = 0;
    long long int width = 0;
    long long int square = 0;
    long long int numberOfSquares = 0;
    std::cin >> length;
    std::cin >> width;
    std::cin >> square;
    //case 1 the square is larger than the rectangle
    if ((square >= length) && (square >= width)){
        numberOfSquares++;
    }
    //case 2 the square is smaller than the rectangle
    //case 2a the width xor the height is larger than the square
    else if ((square <= length) ^ (square <= width)){
        long long int largest = (length > width)? length: width;
        numberOfSquares = std::ceil(((double)largest)/square);
    }
    //case 2b both are larger than the square
    else{
        long long int largest = (length > width)? length: width;
        long long int min = (length < width)? length: width;
        numberOfSquares = std::ceil(((double)largest)/square);
        numberOfSquares *= std::ceil(((double)min)/square);
    }
    std::cout << numberOfSquares;
    return 0;
}
