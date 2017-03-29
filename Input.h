#pragma once
#include "pch.h"
#include "Node.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class Input : public Node
{
public:
	map<int, bool> keyDown;
	map<int, bool> keyStay;
	map<int, bool> keyUp;
public:
	void UpdateKey(int key) {
		bool state = GetAsyncKeyState(key) & 0x8001;
		if (state)
		{
			if (!keyDown[key] && !keyStay[key])
			{
				keyDown[key] = true;
				keyStay[key] = true;
				keyUp[key] = false;
			}
			else
			{
				keyDown[key] = false;
				keyStay[key] = true;
				keyUp[key] = false;
			}
		}
		else
		{
			if (!keyUp[key]){
				keyUp[key] = true;
				keyStay[key] = false;
				keyDown[key] = false;
			}
		}
	}

	bool KeyDown(int key){
		return keyDown[key];
	}
	bool KeyUp(int key){
		return keyUp[key];
	}
	bool KeyStay(int key){
		return keyStay[key];
	}

	void OnUpdate() override {
		UpdateKey(VK_LBUTTON);
		UpdateKey(VK_UP);
		UpdateKey(VK_LEFT);
		UpdateKey(VK_RIGHT);
		UpdateKey(VK_DOWN);
		UpdateKey(VK_SPACE);
		UpdateKey(VK_ESCAPE);
		UpdateKey(VK_LCONTROL);
		UpdateKey(VK_BACK);
		for (int i = 'A'; i <= 'Z'; i++){
			UpdateKey(i);
		}
	}

	static Vector2 GetMousePosition(){
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(DXUTGetHWND(), &point);
		return Vector2(point.x, point.y);
	}
};