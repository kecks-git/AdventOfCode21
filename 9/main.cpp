#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

bool isLowPoint(vector<vector<char>>& HeightMap, int x, int y)
{
    char Point = HeightMap.at(x).at(y);
    vector<char> Adj = {-1, 0, 1}; 
    for(auto &i : Adj)
    {
        for(auto &j : Adj)
        {
            if(abs(i) == abs(j))
                continue;
            try
            {
                if(Point >= HeightMap.at(x+i).at(y+j))
                    return false;
            }
            catch(...)
            {
            }
        }
    }
    return true;
}

int getBasinSize(vector<vector<char>>& HeightMap, int x, int y)
{
    char Point = 0;
    try
    {
        Point = HeightMap.at(x).at(y);
    }
    catch(...)
    {
        return 0;
    }
    if(Point == 9)
        return 0;
    else
    {
        //cout << x <<  ", " << y << endl;
        HeightMap[x][y] = 9;
        return 1 + getBasinSize(HeightMap, x+1, y) + getBasinSize(HeightMap, x, y+1) + getBasinSize(HeightMap, x-1, y) + getBasinSize(HeightMap, x, y-1); 
    }
}

int getMin(vector<int>& Num)
{
    int Min = Num.at(0);
    for(auto &i : Num)
    {
        if(Min > i)
            Min = i;
    }
    return Min;
}

void updateBasins(vector<int>& Basins, int Basin)
{
    //cout << Basin << endl;
    int Min = getMin(Basins);
    if(Basin > Min)
    {
        for(int i = 0; i < Basins.size(); ++i)
        {
            if(Basins[i] == Min)
            {
                Basins[i] = Basin;
                return;
            }
        }
    }
}

int main()
{
    fstream ifs("input");
    
    vector<vector<char>> HeightMap;
    vector<char> Line;
    char in = 0;
    while(!ifs.eof())
    {
        in = ifs.get()-48;
        if (in == -38 || in == -49)
        {
            HeightMap.push_back(Line);
            Line = vector<char> {};
        }
        else 
            Line.push_back(in);
    }

    //Part 1
    int Result1 = 0;
    for(int i = 0; i < HeightMap.size(); ++i)
    {
        for(int j = 0; j < HeightMap[0].size(); ++j)
        {
            if(isLowPoint(HeightMap, i, j))
                Result1 += 1 + HeightMap[i][j];
        }
    }
    cout << "Part 1: " << Result1 << endl;
    for(auto &i : HeightMap)
        cout << i.size()<<endl;
    cout << HeightMap.size() << endl;
    // Part 2
    vector<int> Basins {0, 0, 0};
    for(int i = 0; i < HeightMap.size(); ++i)
    {
        for(int j = 0; j < HeightMap[0].size(); ++j)
        {
            if(HeightMap[i][j] != 9)
            {
                updateBasins(Basins, getBasinSize(HeightMap, i, j));
            }
       }
    }
    cout << "Part 2: " << Basins.at(0) *  Basins.at(1) *  Basins.at(2) << endl;
    return 0;
}