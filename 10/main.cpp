#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <initializer_list>

using namespace std;
using namespace std::literals::string_literals;

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

int main()
{
    fstream ifs("SampleInput");
    
    vector<string> Braces;
    string Line = {};
    while(!ifs.eof())
    {
        getline(ifs, Line);
        Braces.push_back(Line);
        Line = string{};
    }

    //Part 1    
    stack<char> Stack {};
    int ErrorScore1 = 0;
        cout << Braces.size() << endl;

    for (auto it = Braces.begin(); it != Braces.end();)    {
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
                    break;
                }
                Stack.pop();
            }
        }
        ++it;
    }
    cout << Braces.size() << endl;
    cout << "Part 1: " << ErrorScore1 << endl;
    //Part 2
    int Errorscore2 = 0;
    for (auto it = Braces.begin(); it != Braces.end();++it)    {
        int Partscore = 0;
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
        Errorscore2 += Partscore;
    }
    cout << "Part 2: " << Errorscore2 << endl;
    return 0;
}