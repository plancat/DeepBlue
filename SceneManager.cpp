#include "SceneManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "Initial.h"
#include "Credit.h"
#include "Selection.h"

Node* SceneManager::curScene = nullptr;
Node* SceneManager::nextScene = nullptr;
Game* Game::instance = nullptr;

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
	else if (name.compare("Selection") == 0){
		nextScene = new Selection();
	}
	else if (name.compare("Game") == 0)
	{
		nextScene = new Game();
	}
	else if (name.compare("Credit") == 0){
		nextScene = new Credit();
	}
}