#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <set>
#include <utility>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using Matrix = vector<vector<int>>;
using Point = pair<int,int>;

Matrix Chiton;
Matrix Dist;
Matrix Visited;

int Size = 500;

void printMatrix(Matrix& Matrix)
{
    for(int Line = 0; Line < Matrix.size(); ++Line)
    {
        for(int Sym = 0; Sym < Matrix[Line].size(); ++Sym)
        {
            cout << (int)Matrix[Line][Sym] << "\t";
        } 
        cout << endl;
    }
    cout << endl;
    return;
}

pair<int, int> minDistance()
{
    // Initialize min value
    int min = INT_MAX;
    pair<int, int> minIndex {0, 0};
 
    for(int i = 0; i < Size; ++i)
    {
        for(int j = 0; j < Size; ++j)
        {
            if (Visited[i][j] == false && Dist[i][j] <= min)
            {
                min = Dist[i][j];
                minIndex = {i, j};
            }
        }   
    }   
    return minIndex;
}

bool isNeighbor(Point a, Point b)
{
    if(a.first == b.first && abs(a.second - b.second) == 1)
        return 1;
    else if(abs(a.first - b.first) == 1 && a.second == b.second)
        return 1;
    return 0;
}

void dijkstra()
{
    for(int i = 0; i < Size; ++i)
    {
        for(int j = 0; j < Size; ++j)
        {
            auto u = minDistance();

            Visited[u.first][u.second] = true;
 
            for(int k = 0; k < Size; ++k)
            {
                for(int l = 0; l < Size; ++l)
                {
                    if (!Visited[k][l] && isNeighbor(u, {k,l}) && Dist[u.first][u.second] != INT_MAX
                        && Dist[u.first][u.second] + Chiton[k][l] < Dist[k][l])
                        Dist[k][l] = Dist[u.first][u.second] + Chiton[k][l];
                }
            }
        }
    }
}
int main()
{
    fstream ifs("input");

    vector<int> Line;
    char in = 0;
    while(!ifs.eof())
    {
        in = ifs.get()-48;
        if (in == -38 || in == -49)
        {
            Chiton.push_back(Line);
            Line = vector<int> {};
        }
        else 
            Line.push_back(in);
    }
    for(auto& j : Chiton)
    {
        for(int i = 0; i < 4; ++i)
        {
            for(int k = 0; k < Size/5; ++k)
                j.push_back((j[k]+i)%9+1);
        }
    }
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < Size/5; ++j)
            Chiton.push_back(Chiton[j]);
    }
    for(int i = 1; i < 5; ++i)
    {
        for(int k = 0; k < Size/5; ++k)
        {
            for(int j = 0; j < Size; ++j)
                Chiton[i*100+k][j] = (Chiton[i*100+k][j]-1+i)%9+1;
        }
    }
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
            cout << Chiton.at(i*100).at(j*100) << endl;
        cout << endl;
    }

    cout << Chiton.size() << " " << Chiton[0].size() << endl;
    Chiton.at(0).at(0) = 0;
    Dist = Chiton;
    Visited = Chiton;
    for(auto &i : Visited)
    {
        fill(i.begin(), i.end(), 0); 
    }
    for(auto &i : Dist)
    {
        fill(i.begin(), i.end(), INT_MAX); 
    }
    Dist.at(0).at(0) = 0;

    dijkstra();

    cout << Dist.at(Size-1).at(Size-1) << endl;
    return 0;
}