#pragma once
#include "pch.h"
#include "Node.h"
#include "Sprite.h"
#include "Input.h"

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
		if (texture != nullptr){
			if (Contains(Input::GetMousePosition()))
			{
				// if (Input::KeyUp(VK_LBUTTON)){
				// 	if (click){
				// 		click = false;
				// 	}
				// }
				
				if (Input::KeyDown(VK_LBUTTON))
				{
					click = true;
					onClick();
				}

				//if (!click)
				//	D3DXVec2Lerp(&value.scale, &value.scale, &Vector2(1.5, 1.5), 0.1f);

			}
			else
			{
				// D3DXVec2Lerp(&value.scale, &value.scale, &Vector2(1.0, 1.0), 0.1f);
			}
		}
	}
};