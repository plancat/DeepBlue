#pragma once
#include "pch.h"
#include "Node.h"
#include "Path.h"

class Texture
{
public:
	int width;
	int height;
	LPDIRECT3DTEXTURE9 texture;
	string name;
private:
	static map<string, Texture*> textures;
public:
	static Texture* Load(const string& name){

		if (textures.find(name) != textures.end())
			return textures[name];
		else
		{
			auto texture = new Texture();
			string filename = "Resources/" + name;
			D3DXIMAGE_INFO info;
			D3DXCreateTextureFromFileExA(
				DXUTGetD3D9Device(),
				filename.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				1, 0,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0,
				&info,
				0,
				&texture->texture);

			texture->name = name;
			texture->width = info.Width;
			texture->height = info.Height;

			cout << "Texture Load : " << name << endl;

			textures.insert({ name, texture });
			return texture;
		}
	}
};

class Sprite;
class Animation;

class Animation
{
public:
	int curIdx;
	bool animationEnable;
	bool loop;
	float currenDelaytTime;
	float delayTime;
	vector<string> animations;
public:
	Animation(const string& path = "", float delayTime = 0.1f, bool loop = false) : delayTime(delayTime), loop(loop){
		curIdx = 0;
		animations = Path::GetFiles(path);
		for (auto it : animations){
			Texture::Load(it);
		}
	}

	void Play(){
		curIdx = 0;
		currenDelaytTime = 0;
		animationEnable = true;
	}

	void Stop(){
		animationEnable = false;
		curIdx = 0;
		currenDelaytTime = 0;
	}

	void Update(Sprite* sprite);
};

class Sprite : public Node
{
private:
	static LPD3DXSPRITE sprite;
public:
	static vector<Sprite*> sprites;
	Animation* animation = nullptr;
	Texture* texture = nullptr;
	Color color = { 1, 1, 1, 1 };
	bool debug = false;
public:
	Sprite(){
		texture = nullptr;
		if (sprite == nullptr)
			D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
		sprites.push_back(this);
	}
	Sprite(const string& path){
		texture = Texture::Load(path);
		if (sprite == nullptr)
			D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
		sprites.push_back(this);
	}


	void OnUpdate() override{
		Node::OnUpdate();
		if (texture != nullptr){
			value.rect.lefttop =
				Vector2(value.position.x - texture->width / 2 * value.rectScale.x, value.position.y - (texture->height / 2 * value.rectScale.y));
			value.rect.leftbottom =
				Vector2(value.position.x - texture->width / 2 * value.rectScale.x, value.position.y + (texture->height / 2 * value.rectScale.y));
			value.rect.righttop =
				Vector2(value.position.x + texture->width / 2 * value.rectScale.x, value.position.y - (texture->height / 2 * value.rectScale.y));
			value.rect.rightbottom =
				Vector2(value.position.x + texture->width / 2 * value.rectScale.x, value.position.y + (texture->height / 2 * value.rectScale.y));
		}

		if (animation != nullptr){
			animation->Update(this);
		}
	}

	void OnDraw() override {
		if (texture != nullptr){
			Vector3 center = { texture->width * value.anchor.x, texture->height * value.anchor.y, 0 };
			sprite->SetTransform(&GetMatrix());
			sprite->Draw(texture->texture, nullptr, &center, nullptr, color);
		}
	}

	void AddAnimation(Animation* animation){
		if (this->animation != nullptr)
			delete this->animation;
		this->animation = animation;
	}

	static void DrawStart(){
		if (sprite != nullptr)
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}

	static void DrawEnd(){
		if (sprite != nullptr){
			sprite->End();
		}
	}

	static void LineDraw(){
		for (auto it : sprites){
			if (it->debug && it->texture != nullptr){
				LPD3DXLINE line;
				D3DXCreateLine(DXUTGetD3D9Device(), &line);
				D3DXVECTOR2 linepos[] = {
					it->value.rect.lefttop,
					it->value.rect.leftbottom,
					it->value.rect.rightbottom,
					it->value.rect.righttop,
					it->value.rect.lefttop,
				};
				line->Begin();
				line->Draw(linepos, 5, Color(1,0,0,1));
				line->End();
				line->Release();
			}
		}
	}

	static void Clear(){
		sprites.clear();
	}

	bool Contains(const Vector2& pos)
	{
		if (value.position.x - texture->width* value.anchor.x * value.scale.x <= pos.x &&
			value.position.x + (texture->width - texture->width * value.anchor.x) * value.scale.x >= pos.x)
			if (value.position.y - texture->height* value.anchor.y * value.scale.y <= pos.y &&
				value.position.y + (texture->height - texture->height * value.anchor.y) * value.scale.y >= pos.y)
				return true;
		return false;
	}

	bool IntersectRect(Sprite* target)
	{
		if (!visible || !target->visible)
			return false;

		if (texture == nullptr || target->texture == nullptr)
			return false;

		float width = texture->width * value.rectScale.x * value.scale.x;
		float height = texture->height * value.rectScale.y * value.scale.y;
		float targetWidth = target->texture->width * target->value.rectScale.x * target->value.scale.x;
		float targetHeight = target->texture->height * target->value.rectScale.y * target->value.scale.y;

		if (value.position.x - width <= target->value.position.x + targetWidth)
		{
			if (value.position.x + width >= target->value.position.x - targetWidth)
			{
				if (value.position.y - height <= target->value.position.y + targetHeight)
				{
					if (value.position.y + height >= target->value.position.y - targetHeight)
					{
						OnCollision(target);
						return true;
					}
				}
			}
		}

		return false;
	}

	virtual void OnCollision(Sprite*){}
};