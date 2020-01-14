#pragma once
#include <map>
#include <vector>
#include <forward_list>
#include <iostream>

typedef int vertex;
typedef std::pair<int, int> edge;

class GraphD {
private:
	std::map<vertex, std::vector<vertex>> g;
public:
	GraphD();
	//1. Constructor por copia
	GraphD(GraphD *g);
	//2. Constructor a partir de la lista de arcos
	GraphD(std::vector<edge> el);
		~GraphD();
	//3. Inserta el arco si no existe
	void Insert(edge);
	//4. Borra el arco si existe
	void Remove(edge);

	//5. Verifica si existe un camino desde el vértice initial
	bool Path(vertex initial, vertex final);
		//6. Verifica si existe un camino desde el vértice initial hasta el vértice final, si
		//no existe devuelve false y la vlist estará vacía.Si existe, devuelve true y construye
		//en vlist la lista
		//y final
		bool Path(vertex initial, vertex final, std::forward_list<vertex> vlist);
			//7. Imprime por pantalla la lis
			void Print();
	//8. Verifica que el grafo es euleriano
	bool IsEulerian();
	//9. Calcula el índice de un vértice
	int Index(vertex);

};



