#include <Map>
#include <vector>
#include <string>
#include <sstream>
#include "Enemy.h"
#include <iostream>
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"


int main() {

	//Search and read XLM doc
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);


	std::map<std::string, Enemy> Enemys;


	rapidxml::xml_node<> *pRoot = doc.first_node(); 
	

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("Enemy"); pNode; pNode = pNode->next_sibling()) {
		
		//Definition	
		Enemys[pNode->first_attribute("Name")->value()];
		//Name 
		Enemys[pNode->first_attribute("Name")->value()].name = pNode->first_attribute("Name")->value();
		//HP
		Enemys[pNode->first_attribute("Name")->value()].hp = (int)pNode->first_node("HP")->value(); 
		//atq
		Enemys[pNode->first_attribute("Name")->value()].atq = (int)pNode->first_node("Atq")->value();
		//Def
		Enemys[pNode->first_attribute("Name")->value()].def = (int)pNode->first_node("Def")->value();
		//atqSpeed
		Enemys[pNode->first_attribute("Name")->value()].atqSpeed = (int)pNode->first_node("AtqSpeed")->value();
		//Xp
		Enemys[pNode->first_attribute("Name")->value()].xp = (int)pNode->first_node("XP")->value();
		//Weapons
		/*for (rapidxml::xml_node<> *pNodeW = pNode->first_node("Arma"); pNodeW; pNodeW = pNodeW->next_sibling()) {
			
			weapon *tmp = new weapon(*pNode->first_attribute("Arma")->value(), (int)pNodeW->first_node("Type"), (int)pNodeW->first_node("Range"));
			Enemys[pNode->first_attribute("Name")->value()].weapons.push_back(*tmp);

		}*/
	}

	return 0;
}