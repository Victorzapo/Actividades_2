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

	edge f{4, 5};
	edge e{ 4, 2 };

	graf.Insert(f);
	graf.Insert(e);

	graf.Print(); 

	GraphD cG(graf);

	int index = graf.Index(1);
	

	bool euler = graf.IsEulerian();

	//graf.Remove(f);


	return 0;
}