#include "binarySearchTree.h"

node * binarySearchTree::Search(int key)
{
	node* tmp = root;
	node* actualNode = root;
	std::stack<node*> pastNodes;
	pastNodes.push(actualNode);
	
	if (root == nullptr)
		return nullptr;

	while (!pastNodes.empty()) {

		node* tmp = pastNodes.top();
		pastNodes.pop();

		if (tmp->data == key) return tmp;

		if (tmp->izq != nullptr) pastNodes.push(tmp->izq);
		if (tmp->drch != nullptr) pastNodes.push(tmp->drch);

	}

	return nullptr;
}

node * binarySearchTree::Insert()
{
	return nullptr;
}

void binarySearchTree::newTree()
{
	//Arbol a mano 
	root = new node(41);
	root->izq = new node(69);
	root->drch = new node(40);
	root->drch->izq = new node(49);
	root->drch->drch = new node(33);
}
