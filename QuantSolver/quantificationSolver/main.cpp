//
//  main.cpp
//  quantificationSolver
//
//  Created by Zaid Abdulrehman on 11/2/20.
//  Copyright © 2020 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>
using namespace std;
bool quantificationalSolver(bool data[4][4][4], bool quants[3]){
    bool x = quants[0]; bool y = quants[1]; bool z = quants[2];
    for (int row = 0; row < 4; row++){
        for (int column = 0; column < 4; column++){
            for (int depth = 0; depth < 4; depth++){
                if (quants[2] && !data[row][column][depth]) z = false;//for all z but one of them is false z is now false
                else if (!quants[2] && data[row][column][depth]) z = true;//there exists a z because one of them is true so z is now true
            }
            if (quants[1] && !z) y = false;//if y is for all and the z value came out false y is now false
            else if (!quants[1] && z) y = true;//if y is there exists and z is true y is now true
            z = quants[2];//reset z
        }
        if (quants[0] && !y) x = false;//if x is for all and y is not true then x is not true
        if (!quants[0] && y) x = true;//if x is there exists and y is true then x is true
        y = quants[1];//this line
    }
    return ((x)? true: false);//if x is true then the 'chain' is complete :)
}

int main(int argc, char* argv[]) {
    bool data[4][4][4];
    bool quantifiers[3];
    for (int i = 0; i < 3; i++) cin >> quantifiers[i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                cin >> data[i][j][k];
    cout << quantificationalSolver(data, quantifiers) << endl;
    return 0;
}
