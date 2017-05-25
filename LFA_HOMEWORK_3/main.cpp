//
//  main.cpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 17/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <stack>

using namespace std;

int viz[101], n;
ifstream f("date.in");

struct pereche
{
    char x;
    int nod;
    string pushList;
    char popList;
    pereche *leg;
};

void stack_show(stack<char> s) {
    
    while (!s.empty()) {
        
        cout << s.top();
        s.pop();
    }
}

void reinit(int nr_stari)
{
    for (int i = 0; i < nr_stari; i++)
        viz[i] = 0;
}

void insert_b(pereche *&p, int x, char z, char pop, string push)
{
    if (p == NULL)
    {
        p = new pereche;
        p -> leg = NULL;
        p -> x = z;
        p -> nod = x;
        p -> pushList = push;
        p -> popList = pop;
        return;
    }
    pereche *q;
    for (q = p; q -> leg != NULL; q = q -> leg);
    pereche *t;
    t = new pereche;
    t -> leg = NULL;
    t -> x = z;
    t -> nod = x;
    t -> popList = pop;
    t -> pushList = push;
    q -> leg = t;
}

void afis(pereche *p)
{
    pereche *q;
    for (q = p; q != NULL; q = q -> leg)
        cout << "(" << q -> x << " " << q -> nod << ") ";
}

pereche *cautare(pereche *p, char a)
{
    pereche *q;
    for (q = p; q != NULL; q = q -> leg)
        if (q -> x == a) return q;
    return NULL;
}

bool search_f(int finish[], int p, int nr)
{
    int i;
    for (i = 0; i < nr; i++)
        if (p == finish[i]) return 1;
    return 0;
}

int parcurgere_afn(int stare, string cuvant, pereche *v[], int finish[], int nr, stack<char> s)
{
    
    if (cuvant.size() == 0)
    {
        if (search_f(finish, stare, nr) == 1 && s.empty())
        {
            return 1;
        }
        
        pereche *index;
        for (index = v[stare]; index != NULL; index = index -> leg)
        {
            if (index -> x == '*'  && s.top() == index -> popList)
            {
                stack<char> temp_stack = s;
                temp_stack.pop();
                for (int index2 = index -> pushList.size() - 1; index2 >= 0; index2--) {
                    
                    if (index->pushList[index2] != '*')
                        temp_stack.push(index->pushList[index2]);
                }
                int next_stare = index -> nod;
                int o = 0;
                o = parcurgere_afn(next_stare, cuvant, v, finish, nr, temp_stack);
                if (o == 1)
                    return o;
            }
        }
        
        return 0;
    }
    
    pereche *index;
    for (index = v[stare]; index != NULL; index = index -> leg)
    {
        
        if (index -> x == '*' && s.top() == index -> popList)  ///lamda este codat cu *
        {
            
            stack<char> temp_stack = s;
            temp_stack.pop();
            for (int index2 = index -> pushList.size() - 1; index2 >= 0; index2--) {
                
                if (index->pushList[index2] != '*')
                    temp_stack.push(index->pushList[index2]);
            }
            int next_stare = index -> nod;
            int o = 0;
            o = parcurgere_afn(next_stare, cuvant, v, finish, nr, temp_stack);
            if (o == 1)
                return o;
        }
        
        else if (index -> x == cuvant[0] && s.top() == index -> popList)
        {
            string b;
            b = cuvant;
            b.erase(0, 1);
            
            stack <char> temp_stack = s;
            temp_stack.pop();
            for (int index2 = index -> pushList.size() - 1; index2 >= 0; index2--) {
                
                if (index->pushList[index2] != '*')
                    temp_stack.push(index->pushList[index2]);
            }
            
            int next_stare = index -> nod;
            int o = 0;
            
            o = parcurgere_afn(next_stare, b, v, finish, nr, temp_stack);
            
            if (o == 1)
                return o;
        }
    }
    
    return 0;
}

void AFN (pereche *v[], int finish[], int nr)
{
    string cuvant;
    cin >> cuvant;
    int o = 0;
    stack<char> s;
    s.push('Z');
    o = parcurgere_afn(0, cuvant, v, finish, nr, s);
    if (o == 1)
        cout << "acceptat\n";
    else
        cout << "neacceptat\n";
}

void citire(int n, pereche *v[], int &m)
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
        /*
         char delimiter('/');
         char delimiter2(',');
         */
        f >> pop;
        f >> pop;
        char temp;
        f >> temp;
        getline(f, push);
        
        insert_b(v[x], y, z, pop, push);
    }
}

void citire_finale(int nr, int finish[])
{
    int i;
    for (i = 0; i < nr; i++)
        f >> finish[i];
}


int main()
{
    f >> n;
    pereche *v[n];
    int i;
    int m;
    for (i = 0; i < n; i++)
        v[i] = NULL;
    citire(n, v, m);
    
    int nr;
    f >> nr;
    int finish[nr];
    citire_finale(nr, finish);
    
    for (int i = 0; i < n; i++) {
        
        cout << i << ": ";
        for (pereche* index = v[i]; index != NULL; index = index->leg) {
            
            cout << "(" << index -> nod << " , " << index -> x << " , " << index -> popList << " , " << index -> pushList << "), ";
        }
        cout << endl;
    }
    cout << endl;
    
    reinit(n);
    AFN(v, finish, nr);
    
    return 0;
}

