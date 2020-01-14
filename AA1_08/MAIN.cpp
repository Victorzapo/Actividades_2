#include "digraf.h"
#include <iostream>



int main(){

	


	std::vector<edge> ed;
	edge a{ 1,2 };
	edge b{ 1,4 };
	edge c{ 2,3 };
	edge d{ 3,1 };

	ed.push_back(a);
	ed.push_back(b);
	ed.push_back(c);
	ed.push_back(d);

	GraphD graf(ed);

	return 0;
}