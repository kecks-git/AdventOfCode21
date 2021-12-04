#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <iostream>

using namespace std::literals::string_literals;

std::vector<int> readFile(std::string& fileName)
{
	std::ifstream ifs(fileName);
	std::vector<int> Num {};
	int c;
	while (ifs >> c && !ifs.eof())
	{
		Num.push_back(c);
	}
	std::cout << "Size " << Num.size();
	ifs.close();

	return Num;
}

int main(){
	std::cout << "TEST";
	auto Name = "Input1"s;
	/*auto Num = readFile(Name);
	
	std::cout << "Size " << Num.size();

	for(int i = 0; i!=Num.size()-1; i++)
	{
		if (Num[i] <= Num[i+1])
			i = 0;
		else 
			i = 1;
	}
	std::cout << "Result: " << std::accumulate(Num.begin(), Num.end()-1, 0);
	*/
	return 0;
}
