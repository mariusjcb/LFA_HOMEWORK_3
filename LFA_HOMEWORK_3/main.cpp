//
//  main.cpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 17/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////
class PDA
{
    //------------------------------------------------------------------------
public:
    PDA(string filename);
    PDA ();
    void isAccepted(string str);
    //------------------------------------------------------------------------
private:
    void populateTransitionTable(ifstream *p);
    void initialOuput(string s);
    void output(string s, string k, unsigned int i);
    string showCurrentStack();
    void notAccepted(string str);
    int numStates;
    string endStates;
    string alphabet;
    list <string> s;
    map<string, string> m;
    map<string, int> moveNum;
    string currentState;
    //------------------------------------------------------------------------
};
//////////////////////////////////////////////////////////////////////////
int main ()
{
    //Read the DPDA input files
    ifstream inStream;
    inStream.open("teste.in");
    
    int nDPDA;
    inStream >> nDPDA;
    list<PDA> generic;
    
    for (int i = 0; i < nDPDA; i++)
    {
        string temp;
        inStream >> temp;
        generic.push_back(PDA(temp));
    }
    
    inStream.close();
    
    return 0;
}
//////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
PDA::PDA () {}
//------------------------------------------------------------------------
PDA::PDA(string filename)
{
    ifstream file;
    
    file.open(filename.c_str());
    
    if (file.fail())
    {
        cout << "Trouble Opening File\n";
        exit(1);
    }
    
    //set the number of States
    file >> numStates;
    
    //populate the end States
    file >> endStates;
    
    //populate alphabet
    file >> alphabet;
    
    //create our rules/transition table
    ifstream *pointer = &file;
    populateTransitionTable (pointer);
    
    currentState = "0";
    s.push_back("Z0");
    
    //Tests Any Included Test Cases in the File
    //e.g. wont do anything if no test cases
    
    char buff[256];
    file.getline(buff, 256);
    string temp(buff);
    
    while (! file.eof())
    {
        isAccepted(temp);
        file >> temp;
    }
    
    file.close();
}
//------------------------------------------------------------------------
void PDA::populateTransitionTable (ifstream *p)
{
    int n;
    *p >> n;
    
    string temp;
    string key = "";
    string value = "";
    
    for (int k = 0; k < n; k++)
    {
        //read
        for (int i = 0; i < 3; i++)
        {
            *p >> temp;
            key.append (temp);
        }
        for (int i = 0; i < 2; i++)
        {
            *p >> temp;
            value.append(temp);
        }
        moveNum.insert(pair<string, int>(key, k+1));
        m.insert(pair<string, string>(key, value));
        key = "";
        value = "";
    }
}
//------------------------------------------------------------------------
void PDA::isAccepted(string str)
{
    //# represents Lambda, it's reserved it's unconventional enough
    //not to obstruct other languages
    string c = str.substr(0);
    str.append("#");
    alphabet.append("#");
    string tempKey = "";
    string operation = "";
    
    initialOuput(c);
    for (unsigned int i = 0; i < str.size(); i++)
    {
        //check alphabet
        unsigned int alpha = alphabet.find((str.c_str())[i]);
        if (alpha == string::npos)
        {
            cout<<"(Crash)\n";
            break;
        }
        //Prepare Key
        tempKey.append("(");
        tempKey.append(currentState);
        tempKey += (str.c_str())[i];
        tempKey.append(s.back());
        tempKey.append(")");
        
        //Get Value
        
        map<string, string>::iterator it = m.find(tempKey);
        
        if (it != m.end())
        {
            stringstream out;
            out << m.find(tempKey)->second;
            operation = out.str();
            out.str("");
        }
        else
        {
            break;
        }
        
        //Set the new State
        currentState = operation.c_str()[1];
        
        //figure out which action to perform with stack
        
        string decision = operation.substr(2);
        unsigned int found = decision.find("^", 0);
        if (found != string::npos)
        {
            s.pop_back();
        }
        else
        {
            string nextFind = "";
            nextFind+=(str.c_str())[i];
            nextFind+="Z0";
            found = decision.find(nextFind, 0);
            
            if (found != string::npos)
            {
                nextFind=str.c_str()[i];
                s.push_back(nextFind);
            }
            else
            {
                nextFind="";
                nextFind+=(str.c_str())[i];
                found = decision.find(nextFind, 0);
                if (found != string::npos)
                {
                    s.push_back(nextFind);
                }
            }
        }
        output(c, tempKey, i+1);
        //clear values
        tempKey = "";
        operation = "";
    }
    
    unsigned int isEnd = endStates.find(currentState,0);
    
    if (isEnd != string::npos)
    {
        cout << "(Accepted)\n\n\n";
    }
    else
    {
        cout << "(Not Accepted)\n\n\n";
    }
    
    //reset
    currentState = "0";
    s.clear();
    s.push_back("Z0");
}
//------------------------------------------------------------------------
void PDA::initialOuput (string c)
{
    cout << "(initially)\t"<<currentState<<"\t\t"<<c;
    
    if (c.size() < 8) cout<<"\t\t";
    else cout<< "\t";
    
    cout<<showCurrentStack()<<"\n\n"; 
}
//------------------------------------------------------------------------
void PDA::output (string c, string key,unsigned int iteration)
{
    cout<< moveNum.find(key)->second << "\t\t" << currentState 
			 << "\t\t";
    
    if (c.size() > iteration) 
    {
        cout << c.substr(iteration);
        
        if ((c.substr(iteration)).size() < 8)
            cout << "\t\t"; 
        else 
            cout << "\t";
    }
    else { cout << "\t\t"; }
    cout << showCurrentStack() <<"\n";
}
//------------------------------------------------------------------------
string PDA::showCurrentStack ()
{
    string stackState = "";
    list<string> temp (s);
    
    while (temp.size() > 0)
    {
        stackState.append(temp.back());
        temp.pop_back();
    }
    return stackState;
}
//------------------------------------------------------------------------
