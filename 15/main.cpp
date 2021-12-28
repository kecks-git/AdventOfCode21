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

Matrix Chiton;
Matrix Output;
Matrix Visited;

int Size = 50;

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

bool getShortestPath(int x, int y, int Cost)
{
    if(x < 0 || y < 0 || x > Size-1 || y > Size-1)
        return 0;
    if(Visited.at(y).at(x) == 0)
    {
        Output.at(y).at(x) += Cost;
        Visited.at(y).at(x) = 1;
        return 1;
    }
    else if(Output.at(y).at(x) > Chiton.at(y).at(x) + Cost)
    {
        Output.at(y).at(x) = Chiton.at(y).at(x) + Cost;
        return 1;
    }
    return 0;
}

void visitNeighbors(int x, int y)
{
    int Cost = Output.at(y).at(x);
    vector<int> Adj = {-1, 0, 1}; 
    for(auto &i : Adj)
    {
        for(auto &j : Adj)
        {
            if(!(i==0 && j==0) && (abs(j) - abs(i) != 0))
            {
                try
                {
                    if(getShortestPath(x+i, y+j, Cost))
                        visitNeighbors(x+i, y+j);
                }
                catch(...)
                {
                }
            }
        }
    }
    return;
}

int main()
{
    fstream ifs("SampleInput");

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
                Chiton[i*10+k][j] = (Chiton[i*10+k][j]-1+i)%9+1;
        }
    }

    cout << Chiton.size() << " " << Chiton[0].size() << endl;
    //printMatrix(Chiton);
    Chiton.at(0).at(0) = 0;
    Output = Chiton;
    Visited = Chiton;
    for(auto &i : Visited)
    {
        fill(i.begin(), i.end(), 0); 
    }

    visitNeighbors(0, 0);

    cout << Output.at(Size-1).at(Size-1);
    return 0;
}