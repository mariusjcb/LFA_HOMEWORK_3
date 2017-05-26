//
//  AFN.h
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 26/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#ifndef AFN_h
#define AFN_h

//MARK: Check if a state is final
bool checkFinal(int finish[], int p, int nr)
{
    int i;
    for (i = 0; i < nr; i++)
        if (p == finish[i])
            return 1;
    
    return 0;
}

//Parcurge -> cum o fi in engleza???
//MARK: Parcruge AFN-ul using '*' as Lambda char
int crossIntoAFN(int state, string word, Pair *v[], int finish[], int nr, stack<char> s)
{
    if (word.size() == 0)
    {
        if (checkFinal(finish, state, nr) == 1 && s.empty())
        {
            return 1;
        }
        
        Pair *index;
        for (index = v[state]; index != NULL; index = index -> getLeg())
        {
            if (index -> getX() == '*'  && s.top() == index -> getPopList())
            {
                stack<char> temp_stack = s;
                temp_stack.pop();
                for (int index2 = index->getPushList().size() - 1; index2 >= 0; index2--)
                {
                    if (index->getPushList()[index2] != '*')
                        temp_stack.push(index->getPushList()[index2]);
                }
                
                int next_state = index->getNod();
                
                if (crossIntoAFN(next_state, word, v, finish, nr, temp_stack))
                    return 1;
            }
        }
        
        return 0;
    }
    
    Pair *index;
    for (index = v[state]; index != NULL; index = index->getLeg())
    {
        
        if (index->getX() == '*' && s.top() == index->getPopList())
        {
            
            stack<char> temp_stack = s;
            temp_stack.pop();
            for (int index2 = index->getPushList().size() - 1; index2 >= 0; index2--)
            {
                if (index->getPushList()[index2] != '*')
                    temp_stack.push(index->getPushList()[index2]);
            }
            
            int next_state = index->getNod();
            
            if (crossIntoAFN(next_state, word, v, finish, nr, temp_stack))
                return 1;
        }
        
        else if (index->getX() == word[0] && s.top() == index->getPopList())
        {
            string b;
            b = word;
            b.erase(0, 1);
            
            stack <char> temp_stack = s;
            temp_stack.pop();
            for (int index2 = index ->getPushList().size() - 1; index2 >= 0; index2--) {
                
                if (index->getPushList()[index2] != '*')
                    temp_stack.push(index->getPushList()[index2]);
            }
            
            int next_state = index->getNod();
            
            if (crossIntoAFN(next_state, b, v, finish, nr, temp_stack))
                return 1;
        }
    }
    
    return 0;
}

void AFN(Pair *v[], int finish[], int nr)
{
    string word;
    cin >> word;
    
    stack<char> s;
    s.push('Z');
    
    if (crossIntoAFN(0, word, v, finish, nr, s))
        cout << "acceptat\n";
    else
        cout << "neacceptat\n";
}

#endif /* AFN_h */
