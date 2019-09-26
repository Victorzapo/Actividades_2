#pragma once


enum Type{ MELEE, RANGED };

struct weapon {

	int id;
	int weaponType;
	int range;

	weapon(int _id, int _Type, int _range) { id = _id; weaponType = _Type, range = _range; };

};


class Enemy{
public:
	std::string name;
	int hp;
	int atq;
	int def;
	int atqSpeed;
	int xp;

	std::vector<weapon> weapons;


};