//
//  Pair.hpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 26/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#ifndef Pair_hpp
#define Pair_hpp

#include <iostream>
#include <vector>
#include <cstring>
#include <stack>

using namespace std;

class Pair
{
    char x;
    int nod;
    
    string pushList;
    char popList;
    
    Pair *leg;
    
public:
    //MARK: Setters
    void setLeg(Pair*);
    void setX(char);
    void setNod(int);
    
    void setPushList(string);
    void setPopList(char);
    
    //MARK: Getters
    Pair* getLeg();
    char getX();
    int getNod();
    
    string getPushList();
    char getPopList();
};

void insertPairForValues(Pair*&, int, char, char, string);

#endif /* Pair_hpp */
