#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

using Edge = pair<string, string>;

int main()
{
    fstream ifs("input");
    
    vector<Edge> Graph;
    set<string> Nodes;
    string Input;
    while(!ifs.eof())
    {
        Input.clear();
        getline(ifs, Input);
        Graph.push_back({Input.substr(0, Input.find('-')), Input.substr(Input.find('-')+1)});
        Nodes.insert(Graph.back().first);
        Nodes.insert(Graph.back().second);
    }
    cout << "All nodes: " << endl;
    for(auto &i : Nodes)
        cout << i << endl;
    return 0;
}