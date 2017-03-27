#pragma once
#include "pch.h"
#include "Node.h"
#include "Sprite.h"
#include "UI.h"
#include "Input.h"
#include "Cheat.h"
#include "Editor.h"
#include "SceneManager.h"

class MainMenu : public Node
{
public:
	Editor* editor;
	Sprite* pressButton;
public:
	Dialog* buttonsLayer;
	Dialog* rankingLayer;
	Dialog* tutorialLayer;
	Sprite* tutorialImage;
public:
	bool ismenu;
	bool isranking;
	bool istutorial;
	int tutorialIdx;
public:
	MainMenu()
	{
		editor = new Editor();
		this->Attach(editor);
		ismenu = false;
		isranking = false;
		istutorial = false;

		MainMenuInit();
		RankingInit();
		TutorialInit();

		cout << "MainMenu" << endl;
	}

	void RankingInit(){
		rankingLayer = new Dialog();
		this->Attach(rankingLayer);

		Sprite* background = new Sprite("Scenes/Tutorial/tu1.png");
		background->value.position = Vector2(1280 / 2, 720 / 2);
		rankingLayer->Attach(background);
	}

	void TutorialInit(){
		tutorialLayer = new Dialog();
		this->Attach(tutorialLayer);

		tutorialImage = new Sprite("Scenes/Tutorial/tu1.png");
		tutorialImage->value.position = Vector2(640, 360);
		tutorialLayer->Attach(tutorialImage);
	}

	void MainMenuInit(){
		pressButton = new Sprite("Scenes/press button.png");
		pressButton->value.position = Vector2(640, 360);
		this->Attach(pressButton);

		buttonsLayer = new Dialog();
		buttonsLayer->visible = false;
		buttonsLayer->Hide(Vector2(1280, 0));
		this->Attach(buttonsLayer);

		// start
		auto button = new Button("Scenes/IntroButton/Button_3.png");
		button->value = Editor::GetValue("Scene/MainMenu/start");
		button->onClick = [=]()
		{
			SceneManager::LoadScene("Game");
		};
		// editor->AddEditor(button, "Scene/MainMenu/start");
		buttonsLayer->Attach(button);

		// tutorial
		button = new Button("Scenes/IntroButton/Button_5.png");
		button->value = Editor::GetValue("Scene/MainMenu/tutorial");
		button->onClick = [=]()
		{
			isranking = false; istutorial = true;
			tutorialIdx = 1;
			tutorialImage->texture = Texture::Load("Scenes/Tutorial/tu" + to_string(tutorialIdx) + ".png");
		};
		//editor->AddEditor(button, "Scene/MainMenu/tutorial");
		buttonsLayer->Attach(button);

		// ranking
		button = new Button("Scenes/IntroButton/Button_7.png");
		button->value = Editor::GetValue("Scene/MainMenu/ranking");
		button->onClick = [=](){ isranking = true; istutorial = false; };
		//editor->AddEditor(button, "Scene/MainMenu/ranking");
		buttonsLayer->Attach(button);

		// exit
		button = new Button("Scenes/IntroButton/Button_9.png");
		button->value = Editor::GetValue("Scene/MainMenu/exit");
		button->onClick = [](){ exit(0); };
		//editor->AddEditor(button, "Scene/MainMenu/exit");
		buttonsLayer->Attach(button);
	}

	void OnUpdate() override {
		Input::Update();
		Cheat::Update();

		if (isranking)
			rankingLayer->Show(Vector2(0, 0));
		else
			rankingLayer->Hide(Vector2(-1280, 0));

		if (istutorial)
			tutorialLayer->Show(Vector2(0, 0));
		else
			tutorialLayer->Hide(Vector2(-1280, 0));

		if (Input::KeyDown(VK_ESCAPE)){
			if (isranking){
				isranking = false;
			}
			if (istutorial){
				istutorial = false;
				tutorialIdx = 1;
			}
		}

		if (Input::KeyDown(VK_SPACE)){
			if (!ismenu){
				ismenu = true;
				pressButton->visible = false;
				buttonsLayer->enable = true;
				buttonsLayer->visible = true;
				buttonsLayer->Show(Vector2(0, 0));
			}
			else
			{
				if (istutorial){
					tutorialIdx += 1;
					if (tutorialIdx > 3){
						tutorialIdx = 3;
						istutorial = false;
						return;
					}
					tutorialImage->texture = Texture::Load("Scenes/Tutorial/tu" + to_string(tutorialIdx) + ".png");
				}
			}
		}
	}
};