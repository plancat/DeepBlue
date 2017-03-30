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
	Sprite* effect;
	Node* target = nullptr;
public:
	Vector2 dir;
	float speed;
	BulletType bulletType;
	static vector<Bullet*> bullets;
	function<void(Sprite*, UnitBase*)> collision;
	bool lockOn = false;

	float prevBubbleDelay = 0.0f;
	vector<Sprite*> bubbles;

	Bullet(BulletType bulletType, Vector2 dir) : bulletType(bulletType), dir(dir) {
		collision = [=](Sprite* temp, UnitBase* target){};
		this->texture = Texture::Load("bullet.png");
		sprites.push_back(this);
		effect = new Sprite();
		delayComment.push([=](){
			delayComment.push([=](){
				this->parent->Attach(effect);
			});
		});
		bullets.push_back(this);
		this->tag = "Bullet";
		if (bulletType == BulletType::PLAYER){
			for (int i = 0; i < 20; i++){
				Sprite* bubble = new Sprite();
				bubble->AddAnimation(new Animation("Torpedo/Bubble", 0.13f, false, false));
				bubble->visible = false;
				bubble->enable = false;
				bubble->value.scale = { 0.35, 0.35 };
				delayComment.push([=](){
					delayComment.push([=](){
						this->parent->Attach(bubble);
					});
				});
				bubbles.push_back(bubble);
			}
		}
	}

	Sprite* getBubble(){
		for (auto it : bubbles){
			if (!it->visible || !it->enable){
				it->visible = true;
				it->enable = true;
				return it;
			}
		}
		return nullptr;
	}

	void Init(){
		lockOn = false;
		target = nullptr;
		dir = { 0, -1 };
		value.angle = 0.0f;
	}

	void FindTarget();
	void OnUpdate() override;
};