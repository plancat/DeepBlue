#pragma once
#include "pch.h"
#include "Sprite.h"

enum class BulletType{
	PLAYER, MONSTER
};

class UnitBase;
class Bullet : public Sprite
{
public:
	Node* target = nullptr;
public:
	Vector2 dir;
	float speed;
	BulletType bulletType;
	function<void(Sprite*, UnitBase*)> collision;

	Bullet(BulletType bulletType, Vector2 dir) : bulletType(bulletType), dir(dir) {
		collision = [=](Sprite* temp, UnitBase* target){};
		this->texture = Texture::Load("bullet.png");
		sprites.push_back(this);
	}

	void Init(){
		target = nullptr;
		dir = { 0, -1 };
		value.angle = 0.0f;
	}

	void FindTarget();
	void OnUpdate() override;
};