#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  14
#define COIN_BBOX_HEIGHT 16

#define COIN_SPARKLING_TIME 400

#define COIN_ANI_COIN 0
#define COIN_ANI_SPARKLE 1

class CCoin : public CGameObject
{
	DWORD sparkle_start;
	int sparkling = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	int isFinish = 0;
	int isSparkle = 0;
	CCoin();
	CCoin(int isSparkle);
	void StartSparkling() { sparkling = 1; sparkle_start = DWORD(GetTickCount64()); }
};