//
//  Pair.cpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 26/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include "Pair.hpp"

//MARK: Setters
void Pair::setLeg(Pair* pair) {
    this->leg = pair;
}

void Pair::setX(char x) {
    this->x = x;
}

void Pair::setNod(int z) {
    this->nod = z;
}

void Pair::setPushList(string list) {
    this->pushList = list;
}

void Pair::setPopList(char list) {
    this->popList = list;
}

//MARK: Getters
Pair* Pair::getLeg() {
    return this->leg;
}

char Pair::getX() {
    return this->x;
}

int Pair::getNod() {
    return this->nod;
}

string Pair::getPushList() {
    return this->pushList;
}

char Pair::getPopList() {
    return this->popList;
}

//MARK: - Using Pairs
//MARK: Insert new Pair into list with values
void insertPairForValues(Pair *&start, int x, char z, char pop, string push)
{
    //Prepare new Pair
    Pair *t = new Pair;
    
    t->setLeg(NULL);
    t->setX(z);
    t->setNod(x);
    
    t->setPopList(pop);
    t->setPushList(push);
    
    //For Empty list Save as start node and exit
    if (start == NULL)
    {
        start = t;
        return;
    }
    
    //Else: go to the last node and add new Pair after
    Pair *q;
    for (q = start; q->getLeg() != NULL; q = q->getLeg());
    
    //Add new Pair into list
    q->setLeg(t);
}
