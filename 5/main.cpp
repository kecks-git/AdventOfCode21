#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

void addLineToMap(vector<vector<int>> &Map, pair<int,int> Start, pair<int,int> End)
{
    if (Start.first > 999 || Start.second > 999 || End.first > 999 || End.second > 999 )
        throw;
    if (Start.first < 0 || Start.second < 0 || End.first < 0 || End.second < 0 )
        throw;
    if (!(Start.first == End.first || Start.second == End.second))
    /*    Part1: return;
          Part2: Implement Vertical lines 
                 Assume diagonal, 45 degree lines */
    { 
        // TODO
    }
    cout << Start.first << " " << Start.second << " " << End.first << " " <<  End.second << endl;
    if (Start.first != End.first){
        for(int x = min(Start.first, End.first); x <= max(Start.first, End.first); ++x)
            Map[x][Start.second] += 1;
    }
    else if(Start.second != End.second)
    {
        for(int y = min(Start.second, End.second); y <= max(Start.second, End.second); ++y)
            Map[Start.first][y] += 1;
    }
    return;
}

void printMap(vector<vector<int>>& Map){

    for ( int i = 0 ; i < Map.size(); i++ )
    {
        for ( int j = 0; j < Map[i].size() ; j++ )
            cout << Map[j][i];
        cout << endl;
    }
    cout << endl;
}

vector<pair<pair<int,int>, pair<int,int>>> getLines()
{
    string c; 
    vector<pair<pair<int,int>, pair<int,int>>> Lines; 
    pair<int,int> Start;
    pair<int,int> End;
    ifstream ifs("input");
    while ( ifs >> c)
    {
        int i = 0;
        while (c[i] != ','){++i;}
        Start.first = stoi(c.substr(0, i));
        Start.second = stoi(c.substr(i+1));
        cout << Start.first << endl;
        cout << Start.second << endl;
        ifs >> c;
        ifs >> c;
        i = 0;
        while (c[i] != ','){++i;}
        End.first = stoi(c.substr(0, i));
        End.second = stoi(c.substr(i+1));
        cout << End.first << endl;
        cout << End.second << endl;
        Lines.push_back(make_pair(Start, End));
    }
    return Lines;
}

int main()
{
    //Create Map Karte of given size
    vector<vector<int>> Map {0};
    vector<int> Line = {};
    for (int i = 0; i < 1'000; ++i)
        Line.push_back(0);
    for (int i = 0; i < 1'000; ++i)
        Map.push_back(Line);

    for ( int i = 0 ; i < Map.size(); i++ )
    {
        for ( int j = 0; j < Map[i].size() ; j++ )
            Map[i][j] = 0;
    }

    //printMap(Map);

    auto LinePairs = getLines();

    for (auto &i : LinePairs)
    {    
        addLineToMap(Map, i.first, i.second);
  //      printMap(Map);
    }
//    printMap(Map);
    int DangerPoints = 0;
    for ( int i = 0 ; i < Map.size(); i++ )
    {
        for ( int j = 0; j < Map[i].size() ; j++ )
        {
            if( Map[i][j] > 1)
                ++DangerPoints;
        }
    }
    cout << "Danger Points: " << DangerPoints << endl;
    return 0;
}