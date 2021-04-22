#include <iostream>
#include <vector>
using std::vector,std::cout,std::cin;
int main( )
{
	vector<int> t(10);
	for (auto &i : t)
	{
		cout << i;
	}
}
