#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename T>
void readCSV(fstream& File, vector<T>& Numbers, char End = '\n')
{
    T n = 0;
    char c;
    while(!File.eof() && c != End)
    {
        if (File >> n)
            Numbers.push_back(n);
        File.get(c);
    }
    return;
}

template <typename T>
void readSquare(fstream& File, vector<vector<T>>& Square, char End = '\n')
{
    vector<T> Line;
    T n = 0;
    char c;
    while(!File.eof() && c != End)
    {
        readCSV(File, Line, '\n');
        Square.push_back(Line);
        Line = vector<T> {};
        c = File.peek();
    }
}

bool checkForWinners(vector<vector<vector<short>>>& BingoSquares, int& Winner, vector<bool> Skip = { 0 })
{
    // For each square
    for(int i = 0; i < BingoSquares.size(); ++i)
    {
        try{
            if (Skip.at(i))
                continue;
        }
        catch(...){}
        // For each row
        for(int j = 0; j < BingoSquares[0].size(); ++j)
        {
            bool isWinner = 1;
            // For each number
            // If one number not -1 -> it's no bingo
            for(auto &Num : BingoSquares[i][j])
            {
                if(Num != -1)
                    isWinner = 0;
            }
            if(isWinner)
            {
                Winner = i;
                return true;
            }   
        }
        // For each column
        // They are called squares, reuse size of rows
        for(int j = 0; j < BingoSquares[0].size(); ++j)
        {
            bool isWinner = 1;
            // For each number
            // If one number not -1 -> it's no bingo
            for(int k = 0; k < BingoSquares[0].size(); ++k)
            {
                if(BingoSquares[i][k][j] != -1)
                    isWinner = 0;
            }
            if(isWinner)
            {
                Winner = i;
                return true;
            }  
        }
    }
    return false;
}

void updateBingoSquares(vector<vector<vector<short>>>& BingoSquares, int Number)
{
    // For each square
    for(int i = 0; i < BingoSquares.size(); ++i)
    {
        // For each row
        for(int j = 0; j < BingoSquares[0].size(); ++j)
        {
            // For each number
            for(int k = 0; k < BingoSquares[0].size(); ++k)
            {
                if(BingoSquares[i][j][k] == Number)
                    BingoSquares[i][j][k] = -1;
            }
        }
    }
}

template<typename T>
int sumOfSquare(vector<vector<T>> Square)
{
    int Result = 0;
    for(int i = 0; i < Square.size(); ++i)
    {
        for(auto &j : Square[i])
        {
            if(j>0)
                Result += j;
        }
    }
    return Result;
}

template<typename T>
void printSquare(vector<vector<T>> Square)
{
    for (int i = 0; i < Square.size(); ++i)
    {
        for (auto& j : Square[i])
        {
            cout << j << "\t";
        }
        cout << endl;
    }
}

int main()
{
    fstream ifs("input");
    vector<short> Numbers {};
    readCSV(ifs, Numbers, '\n');

    vector<vector<vector<short>>> BingoSquares;
    vector<vector<short>> Square;
    while(!ifs.eof())
    {
        readSquare(ifs, Square);
        BingoSquares.push_back(Square);
        Square = vector<vector<short>> {};
    }  

    //Part 1
    int Winner = -1;
    for(auto& Num : Numbers)
    {
        updateBingoSquares(BingoSquares, Num);
        if(checkForWinners(BingoSquares, Winner))
        {
            // Part 1: 
            cout << "Board: " << Winner << endl;
            cout << "Number: " << Num << endl;
            cout << "Result: " << Num * sumOfSquare(BingoSquares.at(Winner)) << endl;
            break;
        }
    }
    printSquare(BingoSquares[Winner]);

    vector<bool> SkipWinners (BingoSquares.size(), 0);
    for(auto& Num : Numbers)
    {
        updateBingoSquares(BingoSquares, Num);
        while(checkForWinners(BingoSquares, Winner, SkipWinners))
        {
            cout << "Board: " << Winner << endl;
            cout << "Number: " << Num << endl;
            cout << "Result: " << Num * sumOfSquare(BingoSquares.at(Winner)) << endl;
            SkipWinners[Winner] = 1; 
        }
    }
    printSquare(BingoSquares[Winner]);

    return 0;
}