#pragma once
#include "pch.h"
#include "Sprite.h"
#include "Input.h"

class FillSprite : public Node
{
public:
	int maxValue;
	int maxScale;
	Sprite* fillSprite;
public:
	FillSprite(const string& path, int maxScale, int maxValue) : maxScale(maxScale), maxValue(maxValue) {
		fillSprite = new Sprite(path);
		fillSprite->value.scale.x = maxScale;
		fillSprite->value.anchor = { 0, 0.5 };
		fillSprite->value.position.x -= (maxScale / 2);
		this->Attach(fillSprite);
	}

	void SetValue(int value){
		if (value >= maxValue)
			value = maxValue;
		else if (value < 0)
			value = 0;

		fillSprite->value.scale.x = (float)maxScale * ((float)value / (float)maxValue);
	}
};

class Dialog : public Node
{
public:
	Vector2 dest = { 0, 720 };

	void OnUpdate() override {
		value.position *= 4;
		value.position += dest;
		value.position /= 5;
		Node::OnUpdate();
	}

	void Show(Vector2 pos){
		dest = pos;
	}

	void Hide(Vector2 pos){
		dest = pos;
	}
};

class Button : public Sprite
{
public:
	function<void()> onClick;
private:
	bool click = false;
public:
	Button(const string& path) : Sprite(path) {
		onClick = [this](){};
	}

	void OnUpdate(){
		Node::OnUpdate();
		if (texture != nullptr)
		{
			if (input->KeyUp(VK_LBUTTON)){
				if (click){
					click = false;
				}
			}

			if (Contains(Input::GetMousePosition()))
			{
				if (input->KeyDown(VK_LBUTTON)){
					click = true;
					onClick();
				}

				D3DXVec2Lerp(&value.scale, &value.scale, &Vector2(1.2, 1.2), 0.1f);
			}
			else
			{
				D3DXVec2Lerp(&value.scale, &value.scale, &Vector2(1.0, 1.0), 0.1f);
			}
		}
	}
};

class Text : public Node
{
private:
	char str;
	Sprite* text_sprite = nullptr;
public:
	Text(){
		text_sprite = new Sprite();
		this->Attach(text_sprite);
	}
	void SetString(const string& text){
		if (text.compare("") != 0)
		{
			if (text_sprite != nullptr)
				text_sprite->texture = Texture::Load("Font/" + text + ".png");
		}
	}

	void SetString(const char& text){
		if (text_sprite != nullptr)
		{
			string temp = "";
			temp.push_back(text);
			text_sprite->texture = Texture::Load("Font/" + temp + ".png");
		}
	}
};

class TextString : public Node
{
public:
	string str;
	vector<Text*> texts;

	void SetString(const string& text){
		if (texts.size() > 0)
			for (auto it : texts)
				it->Destroy();

		texts.clear();
		for (int i = 0; i < text.size(); i++){
			if (text[i] != 32 && text[i] != '-'){
				Text* tmp = new Text();
				tmp->SetString(text[i]);
				tmp->value.position.x = 170 * i;
				this->Attach(tmp);
				texts.push_back(tmp);
			}
		}
	}
};