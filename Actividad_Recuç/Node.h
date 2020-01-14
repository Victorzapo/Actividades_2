#pragma once
struct node {

	//Hacer Templete
	int data;
	node* drch;
	node* izq;

	node(int v) { data = v; drch = nullptr; izq = nullptr; };
};
