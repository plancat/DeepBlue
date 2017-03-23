#pragma once
#include "pch.h"
#include "Node.h"
#include "Sprite.h"
#include "Button.h"
#include "Input.h"
#include "Cheat.h"

class MainMenu : public Node
{
public:
	MainMenu(){
		auto button = new Button("test.png");
		button->onClick = [](){ cout << "A" << endl; };
		this->Attach(button);

		cout << "MainMenu" << endl;
	}
	
	void OnUpdate() override {
		Input::Update();
		Cheat::Update();
	}
};