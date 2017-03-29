#include "Bullet.h"
#include "UnitBase.h"

void Bullet::FindTarget(){
	for (auto it : UnitBase::units){
		if (it->tag.compare("Player") != 0 && !it->lockOn){
			it->lockOn = true;
			target = it;
			return;
		}
	}
}

void Bullet::OnUpdate(){
	speed += dt * 700;
	value.position += dir * speed * dt;

	for (auto it : UnitBase::units){
		if (it->IntersectRect(this))
		{
			if (it->tag.compare("Player") == 0 && bulletType == BulletType::MONSTER ||
				it->tag.compare("Player") != 0 && bulletType == BulletType::PLAYER){
				effect->AddAnimation(new Animation("Effect", 0.1, false, false));
				effect->animation->Play();
				effect->value.position = this->value.position;
				it->OnCollision(this);
				this->collision(this, it);
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
}