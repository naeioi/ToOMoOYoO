#include "json.hpp"
#include <iostream>
using namespace std;

int main()
{
	json j = "[{\"username\": \"naeioi\", \"password\": \"rocket\"}]"_json;
	
	for(auto &e : j) {
		cout << e << endl;
	}
	return 0;
}