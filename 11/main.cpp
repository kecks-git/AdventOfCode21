#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

struct OctValues {
    int Days = 100;
    int FlashValue = 10;
    int NewValue = -1;
};

void printMatrix(vector<vector<char>> &Matrix)
{
    for(int Line = 0; Line < Matrix.size(); ++Line)
    {
        for(int Sym = 0; Sym < Matrix[Line].size(); ++Sym)
        {
            cout << (int)Matrix[Line][Sym];
        } 
        cout << endl;
    }
    cout << endl;
    return;
}

void IncreaseAdjacent(vector<vector<char>>& Matrix, int x, int y)
{
    char Point = Matrix.at(x).at(y);
    vector<char> Adj = {-1, 0, 1}; 
    for(auto &i : Adj)
    {
        for(auto &j : Adj)
        {
            if(!(i==0 && j==0))
            {
                try
                {
                    Matrix.at(x+i).at(y+j) += 1;
                }
                catch(...)
                {
                }
            }
        }
    }
    return;
}

int IncreaseAdjacentIfTrue(vector<vector<char>>& Matrix, vector<vector<char>>& Values)
{
    int Result = 0;
    for(int Line = 0; Line < Values.size(); ++Line)
    {
        for(int Sym = 0; Sym < Values[Line].size(); ++Sym)
        {
            if(Values[Line][Sym]==1){
                ++Result;
                IncreaseAdjacent(Matrix, Line, Sym);
            }
        }
    }
    return Result;
}

int FlashValues(vector<vector<char>> &Matrix, vector<vector<char>> &AllFlashed, vector<vector<char>> &NewFlashed, OctValues Oct)
{
    int Result = 0;
    for(int Line = 0; Line < Matrix.size(); ++Line)
    {
        for(int Sym = 0; Sym < Matrix[Line].size(); ++Sym)
        {
            if(Matrix[Line][Sym] >= Oct.FlashValue && AllFlashed[Line][Sym] == 0){
                ++Result;
                Matrix[Line][Sym] = Oct.NewValue;
                NewFlashed[Line][Sym] += 1;
            }
        }
    }
    return Result;
}

void ZeroMatrix(vector<vector<char>> &Matrix)
{
    for(int i = 0; i < Matrix.size(); ++i)
    {   
        for(int j = 0; j < Matrix[0].size(); ++j)
            Matrix[i][j]=0;
    }  
    return;
}

void ResetFlashedValues(vector<vector<char>> &Matrix, vector<vector<char>> &Values)
{
    for(int i = 0; i < Matrix.size(); ++i)
    {   
        for(int j = 0; j < Matrix[0].size(); ++j)
        {
            if(Values[i][j] > 1)
                throw;
            else if(Values[i][j] == 1)
                Matrix[i][j] = 0;
        }
    }  
    return;
}
void AddMatrix(vector<vector<char>> &Matrix, const vector<vector<char>> &AddMatrix)
{
    for(int i = 0; i < Matrix.size(); ++i)
    {   
        for(int j = 0; j < Matrix[0].size(); ++j)
        {
            Matrix[i][j] += AddMatrix.at(i).at(j);
        }
    }  
    return;
}

int SimulateFlashes(vector<vector<char>> &Matrix, OctValues Oct)
{
    int Result = 0;
    vector<vector<char>> AllFlashed = Matrix;
    ZeroMatrix(AllFlashed);
    vector<vector<char>> NewFlashed = AllFlashed;
    while(FlashValues(Matrix, AllFlashed, NewFlashed, Oct) > 0)
    {
        Result += IncreaseAdjacentIfTrue(Matrix, NewFlashed);
        AddMatrix(AllFlashed, NewFlashed);
        ZeroMatrix(NewFlashed);
    }
    ResetFlashedValues(Matrix, AllFlashed);
    return Result;
}

void IncreaseValues(vector<vector<char>> &Matrix)
{
    for(int Line = 0; Line < Matrix.size(); ++Line)
    {
        for(int Sym = 0; Sym < Matrix[Line].size(); ++Sym)
        {
            ++Matrix[Line][Sym];
        }
    }
    return;
}
int SimulateFlashesDays(vector<vector<char>> &Matrix, OctValues Oct)
{
    int Result = 0;
    int Part = 0;
    for(int i = 0; i < Oct.Days; ++i)
    {
        IncreaseValues(Matrix);
        Part = SimulateFlashes(Matrix, Oct);
        Result += Part;
        if(Part == 100){
            cout << "Day " << i+1 << " all flashed " << Result << endl;    
            return Result;
        }
        cout << "Day " << i+1 << ", Result: " << Result << endl;

    }
    return Result;
}

int main()
{
    fstream ifs("input");
    
    vector<vector<char>> Octopus;
    vector<char> Line;
    char in = 0;
    while(!ifs.eof())
    {
        in = ifs.get()-48;
        if (in == -38 || in == -49)
        {
            Octopus.push_back(Line);
            Line = vector<char> {};
        }
        else 
            Line.push_back(in);
    }

    //Part 1
    int Result1 = 0;
    OctValues Oct {}; 
    //Result1 = SimulateFlashesDays(Octopus, Oct);
    //cout << "Part 1: " << Result1 << endl;
    Oct.Days = 100'000;
    SimulateFlashesDays(Octopus, Oct);

//    cout << "Part 2: " << Basins.at(0) *  Basins.at(1) *  Basins.at(2) << endl;
    return 0;
}