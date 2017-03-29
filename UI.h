#pragma once
#include "pch.h"
#include "Sprite.h"
#include "Input.h"

class FillSprite : public Node
{
private:
	Sprite* fillSprite;
public:
	FillSprite(const string& path) {
		fillSprite = new Sprite(path);
		fillSprite->value.scale.x = 200;
		this->Attach(fillSprite);
	}

	void SetValue(int value){
		if (value > 100)
			value = 100;
		else if (value < 0)
			value = 0;

		fillSprite->value.scale.x = value * 2;
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
