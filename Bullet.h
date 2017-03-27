#pragma once
#include "pch.h"
#include "Sprite.h"
#include "UnitBase.h"

enum class BulletType{
	PLAYER, MONSTER
};

class Bullet : public Sprite
{
public:
	Vector2 dir;
	float speed;
	BulletType bulletType;
	function<void(Sprite*)> collision;

	Bullet(BulletType bulletType, Vector2 dir, float speed) : bulletType(bulletType), dir(dir), speed(speed) {
		collision = [=](Sprite* temp){};
		this->texture = Texture::Load("bullet.png");
	}

	void OnUpdate() override {
		value.position += dir * speed * dt;
		for (auto it : UnitBase::units){
			if (it->IntersectRect(this))
			{
				if (it->tag.compare("Player") == 0 && bulletType == BulletType::MONSTER ||
					it->tag.compare("Player") != 0 && bulletType == BulletType::PLAYER){
					it->OnCollision(this);
					this->collision(this);
				}
			}
		}

		if (this->value.position.x < 0 || 
			this->value.position.x > 1280 || 
			this->value.position.y < 0 || 
			this->value.position.y > 720)
		{
			this->enable = false;
			this->visible = false;
		}
	}
};