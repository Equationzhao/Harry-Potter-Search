#include <iostream>
#include <vector>
using std::vector,std::cout,std::cin;
int main( )
{
	vector<int> t(10);
	for (vector<int>::iterator i = t.begin( ); i != t.end( ); ++i)
	{
		cout << *i;
	}
}
