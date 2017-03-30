#include "Bullet.h"
#include "UnitBase.h"

vector<Bullet*> Bullet::bullets;

void Bullet::FindTarget(){
	Node* bulletTarget = nullptr;
	float targetDist = 99999;
	bool isBullet = false;

	if (this->bulletType == BulletType::PLAYER){
		for (auto it : bullets) {
			if (it->bulletType == BulletType::MONSTER && !it->lockOn && it->visible){
				float dist = D3DXVec2Length(&(it->value.position - this->value.position));
				if (targetDist > dist){
					targetDist = dist;
					bulletTarget = it;
					isBullet = true;
				}
			}
		}

		for (auto it : UnitBase::units){
			if (it->tag.compare("Player") != 0 && !it->lockOn && it->visible){
				float dist = D3DXVec2Length(&(it->value.position - this->value.position));
				if (targetDist > dist)
				{
					targetDist = dist;
					bulletTarget = it;
					isBullet = false;
				}
			}
		}

		if (bulletTarget != nullptr){
			if (isBullet){
				((Bullet*)bulletTarget)->lockOn = true;
				this->target = bulletTarget;
			}
			else
			{
				((UnitBase*)bulletTarget)->lockOn = true;
				this->target = bulletTarget;
			}
		}
	}
}

void Bullet::OnUpdate(){
	Sprite::OnUpdate();

	speed += dt * 700;
	value.position += dir * speed * dt;

	for (auto it : UnitBase::units){
		if (it->IntersectRect(this)){
			if (!it->isDeath){
				if (it->tag.compare("Player") == 0 && bulletType == BulletType::MONSTER ||
					it->tag.compare("Player") != 0 && bulletType == BulletType::PLAYER){
					effect->AddAnimation(new Animation("Effect", 0.1, false, false));
					effect->visible = true;
					effect->enable = true;
					effect->animation->Play();
					effect->value.position = this->value.position;
					it->OnCollision(this);
					this->collision(this, it);
				}
			}
		}
	}

	for (auto it : bullets){
		if (it->IntersectRect(this)){
			if (this->bulletType != ((Bullet*)it)->bulletType){
				((Bullet*)it)->visible = false;
				((Bullet*)it)->enable = false;
			}
		}
	}

	if (this->value.position.x < 0 || this->value.position.x > 1280 || this->value.position.y < 0)
	{
		this->enable = false;
		this->visible = false;
	}

	if (this->value.position.y > 720) {
		if (bulletType != BulletType::PLAYER) {
			this->visible = false;
			this->enable = false;
		}
	}

	if (target != nullptr){
		if (!target->visible && !target->enable){
			target = nullptr;
			return;
		}
		D3DXVec2Normalize(&dir, &(target->value.position - this->value.position));
		value.angle = atan2(dir.y, dir.x) + D3DXToRadian(90);
	}

	if (visible){
		prevBubbleDelay += dt;
		if (prevBubbleDelay >= 0.03f){
			prevBubbleDelay = 0.0f;
			auto bubble = getBubble();
			if (bubble != nullptr){
				bubble->color = Color(1, 1, 1, 1);
				bubble->animation->Play();
				bubble->value.position = this->value.position + Vector2(0, 10);
			}
		}
	}

	for (auto it : bubbles){
		if (it->visible){
			D3DXColorLerp(&it->color, &it->color, &Color(1, 1, 1, 0), 0.05f);
		}
	}
}