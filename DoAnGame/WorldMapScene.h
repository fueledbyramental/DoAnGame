#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "MiniMario.h"
#include "Object.h"
#include "Environment.h"
#include "Board.h"


class CWorldMapScene : public CScene
{
protected:
	CMiniMario* player;					// A play scene has to have player, right? 
	CBoard* board = NULL;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

public:

	CWorldMapScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMiniMario* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CWorldMapSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorldMapSceneKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

