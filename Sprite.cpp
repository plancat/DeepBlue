#include "Sprite.h"

LPD3DXSPRITE Sprite::sprite;
vector<Sprite*> Sprite::sprites;
map<string, Texture*> Texture::textures;

void Animation::Update(Sprite* sprite){
	if (animationEnable){
		sprite->visible = true;
		currenDelaytTime += dt;
		if (delayTime <= currenDelaytTime){
			if (curIdx < animations.size()){
				sprite->texture = Texture::Load(animations[curIdx]);
				curIdx += 1;
				currenDelaytTime = 0.0f;
			}
			else
			{
				sprite->visible = visible;
				sprite->enable = visible;

				if (loop)
					curIdx = 0;
				else
					animationEnable = false;
			}
		}
	}
}