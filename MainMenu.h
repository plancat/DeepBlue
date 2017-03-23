#pragma once
#include "pch.h"
#include "Node.h"
#include "Sprite.h"
#include "Button.h"
#include "Input.h"
#include "Cheat.h"
#include "Editor.h"
#include "SceneManager.h"

class MainMenu : public Node
{
public:
	Editor* editor;
public:
	MainMenu(){
		editor = new Editor();
		this->Attach(editor);

		auto button = new Button("test.png");
		button->value = Editor::GetValue("Scene/MainMenu/start.txt");
		button->onClick = [=]()
		{
			SceneManager::LoadScene("Game");
		};
		editor->AddEditor(button, "Scene/MainMenu/start.txt");
		this->Attach(button);

		button = new Button("test.png");
		button->value = Editor::GetValue("Scene/MainMenu/tutorial.txt");
		button->onClick = [](){ cout << "A" << endl; };
		editor->AddEditor(button, "Scene/MainMenu/tutorial.txt");
		this->Attach(button);

		button = new Button("test.png");
		button->value = Editor::GetValue("Scene/MainMenu/ranking.txt");
		button->onClick = [](){ cout << "A" << endl; };
		editor->AddEditor(button, "Scene/MainMenu/ranking.txt");
		this->Attach(button);

		button = new Button("test.png");
		button->value = Editor::GetValue("Scene/MainMenu/exit.txt");
		button->onClick = [](){ cout << "A" << endl; };
		editor->AddEditor(button, "Scene/MainMenu/exit.txt");
		this->Attach(button);

		cout << "MainMenu" << endl;
	}
	
	void OnUpdate() override {
		Input::Update();
		Cheat::Update();
	}
};