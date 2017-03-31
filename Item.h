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

	void Init(ItemType item) {

		if (item == ItemType::HUDDLE){
			int rd = rand() % 2;
			if (rd == 0){
				this->AddAnimation(new Animation("Huddle/Rock", 0.1f, true));
				this->animation->Play();
				this->itemName = "Rock";
			}
			else if (rd == 1){
				this->AddAnimation(new Animation("Huddle/Seaweed", 0.1f, true));
				this->animation->Play();
				this->itemName = "Seaweed";
			}
		}
		else
		{
			int rd = rand() % 5;
			if (this->animation != nullptr)
				this->animation->Stop();
			switch (rd){
			case 0:
				this->texture = Texture::Load("Item/Item_0.png");
				this->itemName = "Hack";
				break;
			case 1:
				this->texture = Texture::Load("Item/Item_1.png");
				this->itemName = "Third";
				break;
			case 2:
				this->texture = Texture::Load("Item/Item_2.png");
				this->itemName = "Upgrade";
				break;
			case 3:
				this->texture = Texture::Load("Item/Item_3.png");
				this->itemName = "SpeedUp";
				break;
			case 4:
				this->texture = Texture::Load("Item/Item_4.png");
				this->itemName = "Follow";
				break;
			}
		}

		int dirrd = rand() % 2;
		if (dirrd == 0)
			dir = { -1, 1 };
		else
			dir = { 1, 1 };

		itemType = item;
		speed = rand() % 250 + 150;
	}

	void OnUpdate() override
	{
		Sprite::OnUpdate();
		if (Player::instance != nullptr){
			if (Player::instance->IntersectRect(this)){
				this->visible = false;
				this->enable = false;
				if (itemType == ItemType::ITEM){
					if (itemName.compare("Follow") == 0){
						Player::instance->followBulletCnt += 1;
						if (Player::instance->followBulletCnt > 9)
							Player::instance->followBulletCnt = 9;
					}
					else if (itemName.compare("Third") == 0){
						Player::instance->thirdBulletCnt += 1;
						if (Player::instance->thirdBulletCnt > 9)
							Player::instance->thirdBulletCnt = 9;
					}
					else if (itemName.compare("Hack") == 0){
						Player::instance->hackBulletCnt += 1;
						if (Player::instance->hackBulletCnt > 9)
							Player::instance->hackBulletCnt = 9;
					}
					else if (itemName.compare("Upgrade") == 0){
						Player::instance->weaponUpgrade += 1;
					}
				}
				else if (itemType == ItemType::HUDDLE) {
					if (itemName.compare("Rock") == 0){
						Player::instance->HuddleOn();
					}
					else if (itemName.compare("Seaweed") == 0){
						Player::instance->HuddleOn();
					}
				}
			}
		}

		if (itemType == ItemType::HUDDLE)
		{
			this->value.position.y += speed * dt;
			if (this->value.position.y > 760){
				this->visible = false;
				this->enable = false;
			}
		}
		else if (itemType == ItemType::ITEM)
		{
			this->value.position += dir * speed * dt;
			if (this->value.position.x < 0 || this->value.position.x > 1280){
				dir.x *= -1;
			}
			if (this->value.position.y < 0 || this->value.position.y > 720){
				dir.y *= -1;
			}
		}
	}
};