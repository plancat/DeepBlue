#pragma once
#include "pch.h"
#include "Node.h"

class Input : public Node
{
public:
	static vector<int> allKeys;
	static map<int, bool> down;
	static map<int, bool> up;
	static map<int, bool> press;
public:
	static void IsValid(int key){
		if (find(allKeys.begin(), allKeys.end(), key) == allKeys.end())
			allKeys.push_back(key);
		if (down.find(key) == down.end())
			down.insert({ key, false });
		if (up.find(key) == up.end())
			up.insert({ key, false });
		if (press.find(key) == press.end())
			press.insert({ key, false });
	}

	void OnUpdate() override {
		for (auto it : allKeys){
			if (GetKey(it)){
				// KeyDown(it);
				KeyPress(it);
				KeyUp(it);
			}
		}
	}

	static bool KeyDown(int key){
		if (GetKey(key)){
			IsValid(key);
			if (!down[key])
			{
				up[key] = false;
				down[key] = true;
				cout << "D" << endl;
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	static bool KeyUp(int key){
		if (!GetKey(key)){
			IsValid(key);
			if (down[key] && !up[key]){
				down[key] = false;
				press[key] = false;
				up[key] = true;
				cout << "U" << endl;
				return true;
			}
			else
				return false;
		}
		return false;
	}
	static bool KeyPress(int key){
		if (GetKey(key)){
			IsValid(key);
			if (down[key])
			{
				press[key] = true;
				cout << "P" << endl;
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	static bool GetKey(int key){
		return GetAsyncKeyState(key) & 0x8001;
	}

	static Vector2 GetMousePosition(){
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(DXUTGetHWND(), &point);
		return Vector2(point.x, point.y);
	}
};