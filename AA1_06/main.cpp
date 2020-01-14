#include <iostream>
#include "tree.h"


int main() {
	binaryTree tree;
	
	tree.newTree();

	
	int nodes = tree.getNumverNodesIt();
	std::cout << "Numero de nodos it: " << nodes << std::endl;
	nodes = tree.getNumberNodesRec();
	std::cout << "Numero de nodos Rec: " << nodes << std::endl;

	std::cout << "PreOrder " << std::endl;
	tree.PreOrder();
	
	int height = tree.heigth();

	std::cout << "Height:  " << height << std::endl;
	
	return 0;
}