#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <set>
#include <utility>
#include <map>

using namespace std;
using tPolymer = map<string, uint64_t>;
using tInstructions = map<string, char>;

void printPolymer(const tPolymer& Polymer)
{
    for (const auto& [key, value] : Polymer) 
        std::cout << key << " = " << value << "; ";
    cout << endl;
    return;
}

tPolymer addToPolymer(tPolymer& Polymer, const string toInsert, uint64_t Num = 1)
{
    if(Polymer.find(toInsert) != Polymer.end())
        Polymer[toInsert] += Num;
    else
        Polymer.insert({toInsert, Num});
    return Polymer;
}

void doInsertionRound(tPolymer& Polymer, tInstructions& Instructions)
{
    // list<char>::iterator
    tPolymer NewPolymer = Polymer;
    for(auto it = Polymer.begin(); it != Polymer.end(); ++it)
    {
        char New = Instructions[it->first];
        string New1 = it->first.substr(0,1) + New;
        string New2 = New + it->first.substr(1,1);
        addToPolymer(NewPolymer, New1, it->second);
        addToPolymer(NewPolymer, New2, it->second);
        NewPolymer[it->first] -= it->second;
    }
    Polymer = NewPolymer;
    return;
}

pair<uint64_t, uint64_t> getMostLeastCommon(tPolymer p)
{
    uint64_t max = 0;
    string MostCommon {};
    map<string,uint64_t> m;
    for (auto it = p.begin(); it != p.end(); it++) 
    {
        m[it->first.substr(0,1)] += it->second;
        m[it->first.substr(1,1)] += it->second;
        if (m[it->first.substr(0,1)] > max) 
        {
            max = m[it->first.substr(0,1)]; 
            MostCommon = it->first.substr(0,1);
        }
        if (m[it->first.substr(1,1)] > max) 
        {
            max = m[it->first.substr(1,1)]; 
            MostCommon = it->first.substr(1,1);
        }
    }
    uint64_t min = m.begin()->second;
    string LeastCommon = m.begin()->first;
    for(auto &i : m)
    {
        if(i.second < min)
        {
            LeastCommon = i.first;
            min = i.second;
        }
    }
    return {(max+1)/2, (min+1)/2};
}

int main()
{
    fstream ifs("input");

    tPolymer Polymer;
    tInstructions Instructions;
    string Input;
    while(!ifs.eof())
    {
        Input.clear();
        getline(ifs, Input);
        if(Polymer.size() == 0)
        {
            for (auto p = next(Input.begin(), 1); p != Input.end(); ++p)
            {
                if(Polymer.find({*(p-1), *p}) != Polymer.end())
                    Polymer[{*(p-1), *p}]++;
                else
                    Polymer.insert({{*(p-1), *p},1});
            }   
        }
        else if (Input == "")
            continue;
        else
        {
            Instructions.insert({Input.substr(0,2), *prev(Input.end(), 1)});
        }
    }

    printPolymer(Polymer);
    for(int i = 0; i < 40; ++i)
    {
        cout << "Iteration " << i << endl;
        doInsertionRound(Polymer, Instructions);
        printPolymer(Polymer);
    }

    auto Common =  getMostLeastCommon(Polymer);
    cout << "Most common: " << Common.first << ", least common: " << Common.second << endl;
    cout << "Result = " << Common.first - Common.second << endl;

   return 0;
}