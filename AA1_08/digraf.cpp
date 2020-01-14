#include "digraf.h"

GraphD::GraphD()
{
}

GraphD::GraphD(GraphD * gA) 
{
	std::map<vertex, std::vector<vertex>>::iterator it;

	

	for (it = g.begin(); it != g.end(); it++) {
		if (it->second.size() == 0) {
			for (int i = 0; i < it->second.size(); i++)
				g[it->first].push_back(it->second[i]);
		}
		else
			g[it->first];

	 }

	
}

GraphD::GraphD(std::vector<edge> el)
{

	for (int i = 0; i < el.size(); i++) {
		g[el[i].first].push_back(el[i].second);
		g[el[i].second];
	}
		
}

GraphD::~GraphD()
{
}

void GraphD::Insert(edge ed)
{
	g[ed.first].push_back(ed.second);
}

void GraphD::Remove(edge ed)
{
	g.erase(ed.first);
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
	std::map<vertex,std::vector<vertex>>::iterator it;

	for (it = g.begin(); it != g.end(); it++) {
		std::cout << "{ " << it->first << "," << it->second[0] << " }" << std::endl;
		for(int i = 1; i < it->second.size(); i++)
			std::cout << "{ " << it->first << "," << it->second[i] << " }" << std::endl;

	}

}

bool GraphD::IsEulerian()
{
	std::map<vertex, std::vector<vertex>>::iterator it;

	int tmpIndex;
	int oddIndex = 0;

	for (it = g.begin(); it != g.end(); it++) {
		tmpIndex = Index(it->first);
		if (tmpIndex % 2 != 0)
			oddIndex++;
	}

	if (oddIndex <= 2)
		return true;
	else
		return false;
}

int GraphD::Index(vertex v)
{
	return g[v].size();
}
