#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <iostream>

using namespace std;
using namespace std::literals::string_literals;

vector<pair<string, int>> readFile(std::string& fileName)
{
	std::ifstream ifs(fileName);
	vector<pair<string, int>> Data {};
	string in; 
    int c;
	while (ifs >> in)
	{
        if (ifs >> c)
    	{
            pair<string,int> p = make_pair(in, c);
            cout << in << " " << c << endl;
            Data.push_back(p);
        }

    }
	cout << "Size " << Data.size() << endl;
	ifs.close();

	return Data;
}

int main(){
	auto Name = "input"s;
	
    auto Data = readFile(Name);
	
	cout << "Size " << Data.size() << endl;

    int Forw = 0;
    int Depth = 0;
    int Aim = 0;

	for(int i = 0; i!=Data.size(); i++)
	{
		string Dir = get<string>(Data[i]);
        int Num = get<int>(Data[i]);
        if (Dir == "forward")
        {   
            Forw += get<int>(Data[i]);
            Depth += Aim * get<int>(Data[i]);
        }
        else if( Dir == "up")
            Aim -= get<int>(Data[i]);
        else if(Dir == "down")
            Aim += get<int>(Data[i]);
        else
            cout << "Failed to read input" << endl;
	}
	cout << "Forward = " << Forw << ", Depth = " << Depth << endl;
	cout << "Result = " << Forw * Depth << endl;

	return 0;
}
