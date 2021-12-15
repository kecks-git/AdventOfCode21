#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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
    int Result = 0;
    for ( int i = 0 ; i < Input.size(); i++ )
    {
        for ( int j = 10; j < Input[i].size() ; j++ )
        {
            if(Input[i][j].size() == 2 ||Input[i][j].size() == 3||Input[i][j].size() == 4||Input[i][j].size() == 7)
                ++Result;
        }                
    }
    cout << Result << endl;

    return 0;
}