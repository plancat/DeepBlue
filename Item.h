#pragma once
#include "pch.h"
#include "Sprite.h"
#include "UnitBase.h"
#include "Player.h"

enum class ItemType
{
	ITEM, HUDDLE
};

class Item : public Sprite
{
public:
	Vector2 dir;
	float speed;
	string itemName;
public:
	ItemType itemType;

	void Init(ItemType item, string itemName) {
		dir = { float(rand() % 2 + (-2)), float(rand() % 2 + (-2)) };
		itemType = item;
		this->itemName = itemName;
		speed = rand() % 250 + 150;
	}


	void OnUpdate() override
	{
		if (Player::instance != nullptr){
			if (Player::instance->IntersectRect(this)){
				this->visible = false;
				this->enable = false;
				if (itemType == ItemType::ITEM){
					if (itemName.compare("Health") == 0){
						Player::instance->health = 5;
					}
					else if (itemName.compare("Third") == 0){
						Player::instance->thirdBulletCnt += 1;
					}
					else if (itemName.compare("Hack") == 0){
						Player::instance->hackBulletCnt += 1;
					}
				}
				else if (itemType == ItemType::HUDDLE) {
					if (itemName.compare("Rock") == 0){
						Player::instance->HuddleOn();
					}
					else if (itemName.compare("Grass") == 0){
						Player::instance->HuddleOn();
					}
				}
			}
		}

		if (itemType == ItemType::HUDDLE)
		{
			this->value.position.y += speed * dt;
			if (this->value.position.y > 720){
				this->visible = false;
				this->enable = false;
			}
		}
		else if (itemType == ItemType::ITEM)
		{
			this->value.position += dir * speed * dt;
			if (this->value.position.x < 0 || this->value.position.x > 1280 || this->value.position.y > 720 || this->value.position.y < 0)
				this->dir *= -1;
		}
	}
};