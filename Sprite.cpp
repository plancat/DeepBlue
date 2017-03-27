#include "Sprite.h"

LPD3DXSPRITE Sprite::sprite;
vector<Sprite*> Sprite::sprites;
map<string, Texture*> Texture::textures;


void Animation::Update(Sprite* sprite){
	if (animationEnable){
		currenDelaytTime += dt;
		if (delayTime <= currenDelaytTime){
			if (curIdx < animations.size()){
				sprite->texture = Texture::Load(animations[curIdx]);
				curIdx += 1;
				currenDelaytTime = 0.0f;
			}
			else
			{
				if (loop)
					curIdx = 0;
			}
		}
	}
}