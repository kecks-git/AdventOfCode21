#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using tInstructions = vector<tuple<char, char, char>>;

void doInsertion(list<char>& Polymer, const tInstructions& Instructions)
{
    // list<char>::iterator
    for (auto p = next(Polymer.begin(), 1); p != Polymer.end(); ++p)
    {
        for(int i = 0; i < Instructions.size(); ++i)
        {
            if(*(prev(p, 1)) == get<0>(Instructions.at(i)))
            {
                if(*p == get<1>(Instructions.at(i)))
                {
                    Polymer.insert(p, get<2>(Instructions.at(i)));
                    break;
                }
            }
        }
    }
    return;
}

pair<long long, long long> getMostLeastCommon(list<char> p)
{
    long long max = 0;
    char MostCommon = -1;
    map<char,int> m;
    for (auto vi = p.begin(); vi != p.end(); vi++) 
    {
        m[*vi]++;
        if (m[*vi] > max) 
        {
            max = m[*vi]; 
            MostCommon = *vi;
        }
    }
    long long min = m.begin()->second;
    char LeastCommon = m.begin()->first;
    for(auto &i : m)
    {
        if(i.second < min)
        {
            LeastCommon = i.first;
            min = i.second;
        }
    }
    return {max, min};
}

int main()
{
    fstream ifs("input");

    list<char> Polymer;
    tInstructions Instructions;
    string Input;
    while(!ifs.eof())
    {
        Input.clear();
        getline(ifs, Input);
        if(Polymer.size() == 0)
        {
            for(auto &i : Input)
                Polymer.push_back(i);
        }
        else if (Input == "")
            continue;
        else
            Instructions.push_back({Input[0],Input[1],Input[6]});
    }

    for(int i = 0; i < 10; ++i)
    {
        cout << i << endl;
        doInsertion(Polymer, Instructions);
    }

    auto Common =  getMostLeastCommon(Polymer);
    cout << "Most common: " << Common.first << ", least common: " << Common.second << endl;
    cout << "Result = " << Common.first - Common.second << endl;
    return 0;
}