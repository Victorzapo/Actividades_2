#pragma once
#include <stack>
#include <iostream>
#include "Nodeh.h"

class binaryTree{
private:
	node* root;
	int getNumberNodesRecPriv(node* catnode);
	int getNumberNodesItPriv(node* actnode);
	void PreOrderPriv(node* actnode);
	int heigthPriv(node* root);
	
	
public:
	int getNumberNodesRec();
	int getNumverNodesIt();
	void PreOrder();
	void newTree();
	int heigth();
};