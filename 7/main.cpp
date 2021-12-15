#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int GetTotalDistance(vector<short> Points, short Ref)
{
    int TotalDistance = 0;
    for (auto &i : Points)
    {
        int Distance =abs(i-Ref);
        TotalDistance += ((Distance+1) * Distance)/2;
    }
    return TotalDistance;
}

int main()
{
    fstream ifs("input");
    
    vector<short> Crabs;
    short n = 0;
    char c;
    while(!ifs.eof())
    {
        if (ifs >> n)
            Crabs.push_back(n);
        ifs >> c;
    }
    
    auto Max = *max_element(Crabs.begin(), Crabs.end());
    cout << "Max.: " << Max << endl;
    auto Result = GetTotalDistance(Crabs, Max/2);
    auto ComparePlus = GetTotalDistance(Crabs, Max/2+1);
    auto CompareMinus = GetTotalDistance(Crabs, Max/2-1);
    cout << Result << endl;
    cout << ComparePlus << endl;
    cout << CompareMinus << endl;
    if (Result > ComparePlus)
    {
        int i = 1;
        while (Result > ComparePlus)
        {
             ++i;
            Result = ComparePlus;
            cout << Max/2 + i << endl;
            cout << Result << endl;
            ComparePlus = GetTotalDistance(Crabs, Max/2 + i);
        }
    }
    else if (Result > CompareMinus)
    {
        int i = 1;
        while (Result > CompareMinus)
        {
             ++i;
            Result = CompareMinus;
            cout << Max/2 - i << endl;
            cout << Result << endl;
            CompareMinus = GetTotalDistance(Crabs, Max/2 - i);
        }
    }
    cout << "Result: " << Result << endl;
    return 0;
}