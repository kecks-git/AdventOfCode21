#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::literals::string_literals;

int main(){
    std::ifstream ifs("input");

    vector<int> Bits;
	string in; 
    int Total=0;
	for(;getline(ifs,in); ++Total)
	{
        cout << in << endl;
        for (int i =0; i < in.size(); ++i)
        {
            if (Total==0)
                Bits.push_back(0);
            if(in.at(i) == '1')
                Bits[i] += 1;  
        }          
    }
	ifs.close();

    cout << "Total: " << Total << endl;
    for (auto & i:Bits)
        cout << i << endl;
    
    int gamma = 0;
    int factor = 1;
    for (int i = Bits.size()-1; i != -1 ; --i)
    {
        if (Bits[i] >= Total/2)
            gamma += factor;
        factor *= 2;
    }
    cout << "Factor: " << factor << endl;
    cout << "Gamma: " << gamma << endl;

    cout << "Result " <<  gamma * (factor - 1 - gamma)<< endl;
    return 0;
}