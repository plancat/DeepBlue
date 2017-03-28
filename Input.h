#pragma once
#include "pch.h"
#include "Node.h"

class Input : public Node
{
public:
	map<int, bool> keyDown;
	map<int, bool> keyStay;
	map<int, bool> keyUp;
public:
	void UpdateKey(int key) {
		int state = GetAsyncKeyState(key);
		if (state & 0x8001)
		{
			if (state & 0x8001)
				keyDown[key] = true;
			else
				keyDown[key] = false;
		
			keyStay[key] = true;
		}
		else
		{
			if (keyStay[key]){
				keyDown[key] = false;
				keyStay[key] = false;
				keyUp[key] = true;
			}
			else
			{
				keyDown[key] = false;
				keyStay[key] = false;
				keyUp[key] = false;
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