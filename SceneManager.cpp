#include "SceneManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "Intro.h"
#include "Initial.h"
#include "Ending.h"
#include "Credit.h"

Node* SceneManager::curScene = nullptr;
Node* SceneManager::nextScene = nullptr;

void SceneManager::LoadScene(const string& name)
{
	Sprite::Clear();
	UnitBase::units.clear();
	Bullet::bullets.clear();

	if (name.compare("MainMenu") == 0)
	{
		nextScene = new MainMenu();
	}
	else if (name.compare("Initial") == 0)
	{
		nextScene = new Initial();
	}
	else if (name.compare("Ending") == 0)
	{
		nextScene = new Ending();
	}
	else if (name.compare("Intro") == 0)
	{
		nextScene = new Intro();
	}
	else if (name.compare("Game") == 0)
	{
		nextScene = new Game();
	}
	else if (name.compare("Credit") == 0){
		nextScene = new Credit();
	}
}