#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH  8
#define FIREBALL_BBOX_HEIGHT 9

#define FIREBALL_SPIN_RIGHT		0
#define FIREBALL_SPIN_LEFT		1
#define FIREBALL_SPIN_SPEED		0.10f 

#define FIREBALL_STATE_SPIN		100


class CFireBall : public CGameObject
{
public:
	CFireBall(int nx);
	virtual void Render();
	void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};