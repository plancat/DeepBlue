#pragma once
#include "pch.h"
#include "Node.h"
#include "Sprite.h"
#include "Button.h"
#include "Input.h"

class MainMenu : public Node
{
public:
	MainMenu(){
		this->Attach(new Input);

		auto button = new Button("test.png");
		button->onClick = [](){ cout << "A" << endl; };
		this->Attach(button);
	}
	
	void OnUpdate() override {

	}
};