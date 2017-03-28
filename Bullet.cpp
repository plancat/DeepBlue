#include "Bullet.h"
#include "UnitBase.h"

void Bullet::OnUpdate(){
	speed += dt * 700;
	value.position += dir * speed * dt;
	for (auto it : UnitBase::units){
		if (it->IntersectRect(this))
		{
			if (it->tag.compare("Player") == 0 && bulletType == BulletType::MONSTER ||
				it->tag.compare("Player") != 0 && bulletType == BulletType::PLAYER){
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
}