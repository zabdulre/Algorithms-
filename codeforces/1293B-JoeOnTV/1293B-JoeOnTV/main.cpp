//
//  main.cpp
//  1293B-JoeOnTV
//
//  Created by Zaid Abdulrehman on 7/15/21.
//  Copyright © 2021 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    long long int opponents = 0;
    long double total = 0;
    std::cin >> opponents;
    for (long long int i = opponents; i > 0; i--){
        total += 1.0/i;
    }
    
    std::cout.precision(12);
    std::cout << std::showpoint << total;
    return 0;
}
