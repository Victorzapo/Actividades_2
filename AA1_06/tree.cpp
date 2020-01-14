#include "tree.h"

int binaryTree::getNumberNodesRecPriv(node* actNode)
{

	if (actNode->drch == nullptr && actNode->izq == nullptr) return 1;


	if (actNode->drch != nullptr && actNode->izq == nullptr)	return 1 + getNumberNodesRecPriv(actNode->drch);
	else if (actNode->izq != nullptr && actNode->drch == nullptr) return 1 + getNumberNodesRecPriv(actNode->izq);
	else return 1 + getNumberNodesRecPriv(actNode->izq) + getNumberNodesRecPriv(actNode->drch);

	
	

}

int binaryTree::getNumberNodesItPriv(node *actnode)
{
	int nodes = 0;
	node* actualNode = root;
	std::stack<node*> pastNodes;
	pastNodes.push(actualNode);
	if (root == nullptr)
		return 0;

	while (!pastNodes.empty()) {

		node* tmp = pastNodes.top();
		pastNodes.pop();
		nodes++;

		if (tmp->izq != nullptr) pastNodes.push(tmp->izq);
		if (tmp->drch != nullptr) pastNodes.push(tmp->drch);

	}
	return nodes;
}

void binaryTree::PreOrderPriv(node* actnode)
{
	std::cout << actnode->data << std::endl;
	if (actnode->izq != nullptr) PreOrderPriv(actnode->izq);
	if (actnode->drch != nullptr) PreOrderPriv(actnode->drch);
	if (actnode->izq == nullptr && actnode->drch == nullptr) return;
}

int binaryTree::heigthPriv(node* actnode)
{
	int maxlvl = 0;
	
	if (actnode->izq != nullptr || actnode->drch != nullptr) {
		maxlvl++;
		if (actnode->izq != nullptr) maxlvl =+ heigthPriv(actnode->izq);
		if (actnode->drch != nullptr) maxlvl =+ heigthPriv(actnode->drch);
	}
	if (actnode->izq == nullptr && actnode->drch == nullptr)
		return maxlvl;
}

void binaryTree::newTree()
{
	//Arbol a mano 
	root = new node(41);
	root->izq = new node(69);
	root->drch = new node(40);
	root->drch->izq = new node(49);
	root->drch->drch = new node(33);

}

int binaryTree::heigth()
{
	heigthPriv(root);
	return 0;
}

int binaryTree::getNumberNodesRec()
{	
	if (root == nullptr)
		return 0;

	return getNumberNodesRecPriv(root);
}

int binaryTree::getNumverNodesIt()
{
	return getNumberNodesItPriv(root);
}

void binaryTree::PreOrder()
{
	PreOrderPriv(root);
}



