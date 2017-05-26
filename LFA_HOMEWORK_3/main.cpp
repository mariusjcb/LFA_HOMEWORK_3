//
//  main.cpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 17/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include "Readers.cpp"

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
    
    while(1)
        AFN(v, finish, nr);
    
    return 0;
}

