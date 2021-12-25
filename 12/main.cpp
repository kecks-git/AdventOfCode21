#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>

using namespace std;

using Edge = pair<string, string>;

struct tPath{
    vector<string> Nodes;
    bool visitedSmall = false;
};

set<string> Nodes = {};
vector<Edge> Edges = {};
const regex pattern("^(?=.*[a-z]).+$");

vector<string> getNeighbors(const string& Node)
{
    vector<string> Neighbors {};
    for (auto& e :Edges)
    {
        if(e.first == Node)
            Neighbors.push_back(e.second);
        else if (e.second == Node)
            Neighbors.push_back(e.first);        
    }
    return Neighbors;
}

bool contains(const vector<string>& Path, const string& Node)
{
    for(auto &i : Path)
    {
        if(i == Node)
            return 1;
    }
    return 0;
}

bool isLowerCase(string Node)
{
    return regex_match(Node, pattern);
}

void printPath(tPath& Path)
{
    cout << "Path: ";
    for(auto& i : Path.Nodes)
        cout << " -> " << i;
    cout << endl;
}

// ! Copy needed ! 
int getPaths(tPath Path, string Node)
{
    int Result = 0;
    if(Node == "end")
    {
        Path.Nodes.push_back(Node);
        printPath(Path);
        return 1;
    }
    else if(isLowerCase(Node) && contains(Path.Nodes, Node))
        return 0;
    //else if(isLowerCase(Node) && Node != "start")
    //{
    //    if(Path.visitedSmall)
    //        return 0;
    //    else
    //        Path.visitedSmall = true;
    //}
    Path.Nodes.push_back(Node);
    auto Neighbors = getNeighbors(Node);
    for(auto& i : Neighbors)
        Result += getPaths(Path, i);
    return Result;
}

// ! Copy needed ! 
int getPathsPart2(tPath Path, string Node)
{
    int Result = 0;
    if(Node == "end")
    {
        Path.Nodes.push_back(Node);
        printPath(Path);
        return 1;
    }
    else if(Node == "start" && contains(Path.Nodes, Node))
        return 0;
    else if(isLowerCase(Node) && contains(Path.Nodes, Node) && Node != "start")
    {
        if(Path.visitedSmall)
            return 0;
        else
            Path.visitedSmall = true;
    }
    Path.Nodes.push_back(Node);
    auto Neighbors = getNeighbors(Node);
    for(auto& i : Neighbors)
        Result += getPathsPart2(Path, i);
    return Result;
}

int main()
{
    fstream ifs("input");

    string Input;
    while(!ifs.eof())
    {
        Input.clear();
        getline(ifs, Input);
        Edges.push_back({Input.substr(0, Input.find('-')), Input.substr(Input.find('-')+1)});
        Nodes.insert(Edges.back().first);
        Nodes.insert(Edges.back().second);
    }
//    cout << "All nodes: " << endl;
//    for(auto &i : Nodes)
//        cout << i << endl;

    tPath Path;
    cout << getPaths(Path, "start") << endl;
    return 0;
}