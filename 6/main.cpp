#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

long long Duplicate (int Days)
{
    if (Days < 6)
        return 1;
    else 
        return Duplicate(Days-7) + Duplicate(Days-9);
}

int main()
{
    fstream ifs("input");
    
    vector<short> Fish;
    short n = 0;
    char c;
    while(!ifs.eof())
    {
        if (ifs >> n)
            Fish.push_back(n);
        ifs >> c;
    }
    auto Fish2 = Fish;
    //Part 1
    int Days = 80;
    for(int i =0; i< Days; ++i)
    {
        cout << "Day: " << i << ", Fish: " << Fish.size() << endl;
        int NewFish = 0;
        for(auto &f : Fish)
        {
            if(f == 0)
            {
                f = 6;
                ++NewFish;
            }
            else if (f <= 8)
                --f;
        }
        Fish.reserve(Fish.size() + NewFish);
        for (int j = 0; j < NewFish; ++j)
            Fish.push_back(8);
    }
    cout << "Part 1: " << Fish.size() << endl;

    //Part 2
    //Start at 0, have 251-255 days
    long long Result = 0;
    map<short, long long> ResultMap {};
    for (auto f : Fish2)
    {
        cout << f << endl;
        if(ResultMap.find(f) == ResultMap.end())
            ResultMap.insert(pair<short, long long>(f, Duplicate(256+5-f)));
        Result += ResultMap[f];
    }
    cout << "Part 1: " << Result << endl;
    return 0;
}