#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <bits/stdc++.h>

using namespace std;

map<char, int> Points1 {{')', 3}, {']', 57}, {'}', 1'197}, {'>', 25'137}};
map<char, int> Points2 {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

template<typename First, typename ... T>
bool isIn(First &&first, T && ... t)
{
    return ((first == t) || ...);
}

bool isOpening(const char Compare)
{
    return isIn(Compare, '[', '{', '(', '<');
}

bool isClosing(const char Compare)
{
    return isIn(Compare, ']', '}', ')', '>');
}

bool isCounterpart(const char Opening, const char Closing)
{
    if(Opening == '{' && Closing == '}')
        return true;
    else if(Opening == '(' && Closing == ')')
        return true;
    else if(Opening == '[' && Closing == ']')
        return true;
    else if(Opening == '<' && Closing == '>')
        return true;
    return false;
}
template<typename T>
T middle (vector<T>& v)
{
    sort(v.begin(), v.end());
    return v[v.size()/2];
}

int main()
{
    fstream ifs("input");
    
    vector<string> Braces;
    string Line = {};
    while(!ifs.eof())
    {
        getline(ifs, Line);
        Braces.push_back(Line);
        Line = string{};
    }

    //Part 1    
    int ErrorScore1 = 0;
    cout << Braces.size() << endl;

    for (auto it = Braces.begin(); it != Braces.end();)    
    {
        stack<char> Stack {};
        bool Deleted = false;
        for(auto &j : *it)
        {
            if(isOpening(j))
                Stack.push(j);
            else
            {
                if(!isCounterpart(Stack.top(), j))
                {
                    ErrorScore1 += Points1.find(j)->second;
                    Braces.erase(it);
                    cout << "Delete " << *it<< endl;
                    Deleted = true;
                    break;
                }
                Stack.pop();
            }
        }
        if(!Deleted)
            ++it;
    }
    for(auto &i :Braces)
        cout << i << endl;
    cout << Braces.size() << endl;
    cout << "Part 1: " << ErrorScore1 << endl;
    //Part 2
    vector<long long> Autocompl = {};
    for (auto it = Braces.begin(); it != Braces.end();++it)    {
        long long Partscore = 0;
        stack<char> Stack {};
        for(auto &j : *it)
        {
            if(isOpening(j))
                Stack.push(j);
            else
                Stack.pop();
        }
        while(!Stack.empty())
        {
            cout << Stack.top();
            Partscore *= 5;
            Partscore += Points2.find(Stack.top())->second;
            Stack.pop();
        }
        cout << endl;
        if(Partscore)
            Autocompl.push_back(Partscore);
        cout << Partscore << endl;
    }
    cout << "Part 2: " << middle(Autocompl) << endl;
    return 0;
}