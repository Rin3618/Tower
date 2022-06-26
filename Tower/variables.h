#pragma once

#include<iostream>
#include<string>

using namespace std;

#define X 13
#define Y 13
#define MONSTER_NUM 5
#define TOTAL_FLOOR 10

typedef int FLOOR[X * Y];

struct MONSTER
{
	int hp;
	int atk;
	int def;
	int gold;
	string name;
};

class HERO
{
public:
	int hp;
	int atk;
	int def;
	int pos_x;
	int pos_y;
	int floor;
	int gold;
	int key;
	HERO();
};

extern HERO Hero;
extern MONSTER Monster[MONSTER_NUM];
extern FLOOR Tower[TOTAL_FLOOR];

void init_monsters();
void init_tower();

