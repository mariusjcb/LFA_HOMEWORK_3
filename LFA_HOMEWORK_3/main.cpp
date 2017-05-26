//
//  main.cpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 17/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include "Pair.hpp"
#include "AFN.h"
#include "Readers.h"

int main()
{
    int n;
    f >> n;
    Pair *v[n];
    int m;
    
    for(int i = 0; i < n; i++)
        v[i] = NULL;
    readPairFromFile(n, v, m);
    
    int nr;
    f >> nr;
    int finish[nr];
    readFinalsFromFile(nr, finish);
    
    for (int i = 0; i < n; i++) {
        
        cout << i << ": ";
        for (Pair* index = v[i]; index != NULL; index = index->getLeg()) {
            
            cout << "(" << index->getNod() << " , " << index->getX() << " , " << index ->getPopList() << " , " << index->getPushList() << "), ";
        }
        cout << endl;
    }
    cout << endl;
    
    AFN(v, finish, nr);
    
    return 0;
}

