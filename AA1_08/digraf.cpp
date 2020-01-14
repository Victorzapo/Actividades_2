#include "digraf.h"

GraphD::GraphD()
{
}

GraphD::GraphD(GraphD * g)
{
}

GraphD::GraphD(std::vector<edge> el)
{

	std::map<vertex, std::vector<vertex>>::iterator it;
	


	for (int i = 0; i < el.size(); i++) {
		for (it = g.begin(); it != g.end(); it++) {
			it = g.find(el[i].first);
			if (it == g.end()) {
				g.insert(el[i].first, el[i].second);
				//it->second.push_back(el[i].second);
			}
			else
				it->second.push_back(el[i].second);

			}


	}

}

GraphD::~GraphD()
{
}

void GraphD::Insert(edge)
{
}

void GraphD::Remove(edge)
{
}

bool GraphD::Path(vertex initial, vertex final)
{
	return false;
}

bool GraphD::Path(vertex initial, vertex final, std::forward_list<vertex> vlist)
{
	return false;
}

void GraphD::Print()
{
}

bool GraphD::IsEulerian()
{
	return false;
}

int GraphD::Index(vertex)
{
	return 0;
}
