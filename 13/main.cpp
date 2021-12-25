#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

using tPoint = pair<int, int>;
using tInstruction = pair<string, int>;
using tPaper = vector<tPoint>;
using tInstructions = vector<tInstruction>;

void fold(tPaper& Paper, const tInstruction& Instruction)
{
    cout << Instruction.first << Instruction.second << endl;
    if(Instruction.first == "x")
    {
        sort(Paper.begin(), Paper.end(), [](const tPoint& x, const tPoint& y){ return x.first < y.first; });
        auto Change = lower_bound(Paper.begin(), Paper.end(), Instruction.second, [](const tPoint& x, int n){ return x.first < n; });
        for(; Change != Paper.end(); ++Change)
          Change->first = 2*Instruction.second - Change->first;
    }
    else if(Instruction.first == "y")
    {
        sort(Paper.begin(), Paper.end(), [](const tPoint& x, const tPoint& y){ return x.second < y.second; });
        auto Change = lower_bound(Paper.begin(), Paper.end(), Instruction.second, [](const tPoint& x, int n){ return x.second < n; });
        for(; Change != Paper.end(); ++Change)
           Change->second = 2*Instruction.second - Change->second;
    }
    
    std::set<tPoint> s(Paper.begin(), Paper.end());
    Paper.assign(s.begin(), s.end());
    cout << Paper.size() << endl;
    return;
}

int main()
{
    fstream ifs("input");

    tInstructions Instructions;
    tPaper Paper;
    string Input;
    while(!ifs.eof())
    {
        Input.clear();
        getline(ifs, Input);
        cout << Input << endl;
        if (Input == "")
            continue;
        if(Input[0] == 'f')
            Instructions.push_back({Input.substr(Input.find('=')-1, 1), stoi(Input.substr(Input.find('=')+1))});
        else
            Paper.push_back({stoi(Input.substr(0, Input.find(','))), stoi(Input.substr(Input.find(',')+1))});
    }

    for(auto &i : Paper)
        cout << i.first << " " << i.second << endl;
    for(auto &i : Instructions)
        cout << i.first << " " << i.second << endl;
    // Part 1
    // fold(Paper, Instructions[0]);
    
    // Part 2
    for(auto &i : Instructions)
        fold(Paper, i);

    int MaxX = 0;
    int MaxY = 0;
    for(auto &i : Paper)
    {
        MaxX = max(i.first, MaxX);
        MaxY = max(i.second, MaxY);
    }

    vector<string> Line;
    Line.resize(MaxX+1, "_");
    vector<vector<string>> Output;
    Output.resize(MaxY+1, Line);

    for(auto &i : Paper)
        Output.at(i.second).at(i.first) = "o";

    for(auto &i : Output)
    {
        for(auto &j : i)
        {
            cout << j;
        }
        cout << endl;
    }
    return 0;
}