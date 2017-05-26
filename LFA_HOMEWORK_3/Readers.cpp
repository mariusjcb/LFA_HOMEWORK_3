//
//  Readers.h
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 26/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include "Pair.hpp"

ifstream f("date.in");
void readPairFromFile(int n, Pair *v[], int &m)
{
    int i;
    f >> m;
    for (i = 0; i < m; i++)
    {
        int x, y;
        char z, pop;
        string push;
        f >> x >> y;
        f >> z;
        
        f >> pop;
        f >> pop;
        char temp;
        f >> temp;
        getline(f, push);
        
        insertPairForValues(v[x], y, z, pop, push);
    }
}

void readFinalsFromFile(int nr, int finish[])
{
    int i;
    for (i = 0; i < nr; i++)
        f >> finish[i];
}
