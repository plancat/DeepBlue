#pragma once
#include "pch.h"
#include "Bullet.h"

enum class PaternType
{
	ONE_LINE, PLAYER, BUTTERFLY
};

class MonsterBase;
class Patern
{
public:
	PaternType paternType;
	Patern(){
		paternType = PaternType::ONE_LINE;
	}

	void PaternAttack(MonsterBase* monsterbase);
};