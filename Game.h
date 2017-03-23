#pragma once
#include "pch.h"
#include "Node.h"
#include "Cheat.h"
#include "Input.h"

class Game : public Node
{
public:
	static int stage;
public:
	Game(){
		cout << "Game" << endl;
	}

	void OnUpdate() override {
		Input::Update();
		Cheat::Update();
	}
};