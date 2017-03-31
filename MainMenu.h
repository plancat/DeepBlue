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
	TextString* pressButton;
public:
	Dialog* buttonsLayer;
	Dialog* rankingLayer;
	Dialog* tutorialLayer;
	Sprite* tutorialImage;
	Sprite* introImage;
	float introDelay = 0.0f;
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

		input = new Input();
		this->Attach(input);

		ismenu = false;
		isranking = false;
		istutorial = false;

		Sprite* background = new Sprite();
		background->value.position = { 640, 360 };
		background->AddAnimation(new Animation("Scenes/MainMenu", 0.1f, true));
		background->animation->Play();
		this->Attach(background);

		Sprite* title = new Sprite("Title.png");
		title->value.position = { 640, 360 };
		this->Attach(title);

		introImage = new Sprite("Scenes/intro.png");
		introImage->value.position = { 640, 360 };
		introImage->visible = false;
		this->Attach(introImage);

		MainMenuInit();
		RankingInit();
		TutorialInit();
	}

	void RankingInit(){
		rankingLayer = new Dialog();
		this->Attach(rankingLayer);

		Node* rankingListLayer = new Node();
		rankingListLayer->value = Editor::GetValue("Scene/MainMenu/rankingList");
		rankingLayer->Attach(rankingListLayer);

		auto rankings = RankingData::Load();
		for (int i = 0; i < rankings.size(); i++){
			TextString* name = new TextString();
			name->SetString(rankings[i].name);
			name->value.scale = { 0.45, 0.45 };
			name->value.position.y += i * 250;
			rankingListLayer->Attach(name);
			TextString* score = new TextString();
			score->SetString(to_string(rankings[i].score));
			score->value.scale = { 0.45, 0.45 };
			score->value.position.x = 600;
			score->value.position.y += i * 250;
			rankingListLayer->Attach(score);
		}
	}

	void TutorialInit(){
		tutorialLayer = new Dialog();
		this->Attach(tutorialLayer);

		tutorialImage = new Sprite("UI/UI_25.png");
		tutorialImage->value.position = Vector2(640, 360);
		tutorialLayer->Attach(tutorialImage);
	}

	void MainMenuInit(){
		pressButton = new TextString();
		pressButton->value = Editor::GetValue("Scene/MainMenu/pressButton");
		pressButton->SetString("Press SpaceBar");
		editor->AddEditor(pressButton, "Scene/MainMenu/pressButton");
		this->Attach(pressButton);

		buttonsLayer = new Dialog();
		buttonsLayer->visible = false;
		buttonsLayer->Hide(Vector2(1280, 0));
		this->Attach(buttonsLayer);

		// start
		auto button = new Button("UI/UI_19.png");
		button->value = Editor::GetValue("Scene/MainMenu/start");
		button->onClick = [=]()
		{
			SceneManager::LoadScene("Selection");
		};
		// editor->AddEditor(button, "Scene/MainMenu/start");
		buttonsLayer->Attach(button);

		// tutorial
		button = new Button("UI/UI_20.png");
		button->value = Editor::GetValue("Scene/MainMenu/tutorial");
		button->onClick = [=]()
		{
			if (istutorial){
				isranking = false;
				istutorial = false;
				return;
			}
			isranking = false;
			istutorial = true;
		};
		//editor->AddEditor(button, "Scene/MainMenu/tutorial");
		buttonsLayer->Attach(button);

		// ranking
		button = new Button("UI/UI_21.png");
		button->value = Editor::GetValue("Scene/MainMenu/ranking");
		button->onClick = [=]()
		{
			if (isranking){
				isranking = false;
				istutorial = false;
				return;
			}
			isranking = true;
			istutorial = false;
		};
		//editor->AddEditor(button, "Scene/MainMenu/ranking");
		buttonsLayer->Attach(button);

		// exit
		button = new Button("UI/UI_22.png");
		button->value = Editor::GetValue("Scene/MainMenu/exit");
		button->onClick = [](){ exit(0); };
		//editor->AddEditor(button, "Scene/MainMenu/exit");
		buttonsLayer->Attach(button);
	}

	void OnUpdate() override {
		if (isranking)
			rankingLayer->Show(Vector2(0, 0));
		else
			rankingLayer->Hide(Vector2(-1280, 0));

		if (istutorial)
			tutorialLayer->Show(Vector2(0, 0));
		else
			tutorialLayer->Hide(Vector2(-1280, 0));


		if (input->KeyDown(VK_ESCAPE)){
			if (isranking){
				isranking = false;
			}
			if (istutorial){
				istutorial = false;
				tutorialIdx = 1;
			}
		}

		if (input->KeyDown(VK_SPACE)){
			if (pressButton->visible){
				introImage->visible = true;
				pressButton->visible = false;
			}
			else if (introImage->visible)
			{
				ismenu = true;
				introImage->visible = false;
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

		Cheat::Update();

		if (introImage->visible){
			introDelay += dt;
			if (introDelay >= 6.0f){
				ismenu = true;
				introImage->visible = false;
				buttonsLayer->enable = true;
				buttonsLayer->visible = true;
				buttonsLayer->Show(Vector2(0, 0));
			}
		}
	}
};