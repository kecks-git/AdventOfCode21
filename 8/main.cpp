#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class SevenSegment
{
    public: 
    string Num;

    bool includes(SevenSegment & b)
    {
        for (auto &i: b.Num)
        {
            if(Num.find(i) == string::npos)
                return 0;
        }
        return 1;
    }
};

bool operator==(SevenSegment a, SevenSegment b)
{
    if(a.includes(b) && b.includes(a))
        return 1;
    else
        return 0;
}

int main()
{
    fstream ifs("input");
    
    vector<vector<string>> Input;
    vector<string> Vec {};
    string s;
    int i = 5;
    while(!ifs.eof())
    {
        if (ifs >> s)
        {
            if (s == "|")
                i = 0;
            else {
                Vec.push_back(s);
                ++i;
                if(i == 4)
                {
                    Input.push_back(Vec);
                    Vec = vector<string>{};
                }
            }
        }
    }
    // Part 1
    int Result = 0;
    for ( int i = 0 ; i < Input.size(); i++ )
    {
        for ( int j = 10; j < Input[i].size() ; j++ )
        {
            if(Input[i][j].size() == 2 ||Input[i][j].size() == 3||Input[i][j].size() == 4||Input[i][j].size() == 7)
                ++Result;
        }                
    }
    cout << "Part 1: " << Result << endl;

    // Part 2
    for ( int i = 0 ; i < Input.size(); i++ )
    {
        map<SevenSegment, int> Num;
        // Create a map of numbers of 0-9
        for ( int j = 0; j < Input[i].size()-4 ; j++ )
        {
        }
        // Get 4 result numbers 
        for ( int j = 10; j < Input[i].size()-4 ; j++ )
        {
        }                      
    }
    return 0;
}