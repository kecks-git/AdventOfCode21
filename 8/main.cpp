#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

// Write included and == functions for std::string 
// characters of std::string a are included in std::string b
bool included(string &a, string & b)
{
    for (auto &i: a)
    {
        if(b.find(i) == string::npos)
            return 0;
    }
    return 1;
}

// std::string contains the same letters, w/o considering order
bool operator==(string a,string b)
{
    if(included(a, b) && included(b, a))
        return 1;
    else
        return 0;
}

// Strategy (Part 2)
// - Get result for each number (PartResult) and sum them up: Result2
// - //Start looking directly at the four output digits
// - Get a vector of all values
// - Some can be immediately defined
// - Other need to follow the rules as described in the SevenSegmentsLogic file
// - Then define all the output digits and sum up the numbers
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
    int Result1 = 0;
    for ( int i = 0 ; i < Input.size(); i++ )
    {
        for ( int j = 10; j < Input[i].size() ; j++ )
        {
            if(Input[i][j].size() == 2 ||Input[i][j].size() == 3||Input[i][j].size() == 4||Input[i][j].size() == 7)
                ++Result1;
        }                
    }
    cout << "Part 1: " << Result1 << endl;

    int Result2 = 0;
    // Part 2
    // For each line
    for ( int i = 0 ; i < Input.size(); i++ )
    {
        vector<string> SevenSegments {};
        // Reserve doesn't initialize the values, resize() would
        SevenSegments.resize(10);
        // For each digit...
        for ( int j = 0; j < 10; j++ )
        {
            if(Input[i][j].size() == 2)
                SevenSegments[1] = Input[i][j];
            else if(Input[i][j].size() == 3)
                SevenSegments[7] = Input[i][j];
            else if(Input[i][j].size() == 4)
                SevenSegments[4] = Input[i][j];
            else if(Input[i][j].size() == 7)
                SevenSegments[8] = Input[i][j];
        }
        for ( int j = 0; j < 10; j++ )
        {
            if(Input[i][j].size() == 6)
            {
                if(!included(SevenSegments[1], Input[i][j]))
                    SevenSegments[6] = Input[i][j];
                else if(!included(SevenSegments[4], Input[i][j]))
                    SevenSegments[0] = Input[i][j];
                else
                    SevenSegments[9] = Input[i][j];
            }
        }
        for ( int j = 0; j < 10; j++ )
        {
            if(Input[i][j].size() == 5)
            {
                if(included(SevenSegments[1], Input[i][j]))
                    SevenSegments[3] = Input[i][j];
                else if(included(Input[i][j], SevenSegments[6]))
                    SevenSegments[5] = Input[i][j];
                else
                    SevenSegments[2] = Input[i][j];
            }
        }
        int PartResult = 0;
        for ( int j = 10; j < Input[i].size(); j++ )
        {
            // TODO: more efficient lookup
            for(int k = 0; k < 10; ++k)
            {
                if(Input[i][j] == SevenSegments[k])
                {
                    // cout << "Found : " << Input[i][j] << " == " << Input[i][k] << endl;
                    // cout << "k = " << k << endl;
                    PartResult += k * pow(10, Input[i].size()-j-1);
                }
            }
        }
        // for (auto & Seg : SevenSegments)
        //     cout << Seg << endl;
        Result2 += PartResult; 
        // cout << "Part 2." << i << ": " << PartResult << endl;
    }
    cout << "Part 2: " << Result2 << endl;
    return 0;
}