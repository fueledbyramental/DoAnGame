#include "QBrick.h"
#include "Utils.h"
#include "Game.h"

#define OBJECT_TYPE_MUSHROOM		18
#define OBJECT_TYPE_LEAF			19
#define OBJECT_TYPE_PBUTTON			15

CQBrick::CQBrick(CGameObject*player, int setting, float y)
{
	this->player = player;
	this->setting = setting;
	ring_start = NULL;
	min = y;
	SetState(BRICK_STATE_QUES);
}

void CQBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (GetTickCount64() - ring_start > BRICK_RINGING_TIME)
	{
		ring_start = 0;
		ringing = 0;
		y = min;
	}

	if (ringing)
	{
		if (GetTickCount64() - ring_start >= BRICK_RINGING_TIME / 2)
			y += 1;
		else
			y -= 1;
	}
	//DebugOut(L"min = %f\n", min);
}

void CQBrick::Render()
{
	int ani = BRICK_ANI_QUES;
	if (state == BRICK_STATE_EMP) {
		ani = BRICK_ANI_EMP;
	}
	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox();
}

void CQBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CGameObject* CQBrick::ShowItem()
{
	CGame* game = CGame::GetInstance();
	CGameObject* obj = NULL;
	if (setting == 0)		// COIN
	{
		game->AddScore(100);
		game->AddCoin();
		int ani_set_id = 12;
		int isSparkle = 1;
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		obj = new CCoin(isSparkle);
		obj->SetPosition(this->x, this->y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	else if (setting == 1)	// MUSHROOM OR LEAF
	{
		if ( player->level == MARIO_LEVEL_SMALL)
		{
			int ani_set_id = 18;
			CAnimationSets* animation_sets = CAnimationSets::GetInstance();
			obj = new CMushRoom(player->nx, 0);
			obj->type = OBJECT_TYPE_MUSHROOM;
			obj->SetPosition(this->x, this->y);
			LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
			obj->SetAnimationSet(ani_set);
		}
		else
		{
			int ani_set_id = 19;
			CAnimationSets* animation_sets = CAnimationSets::GetInstance();
			obj = new CLeaf(this->x);
			obj->type = OBJECT_TYPE_LEAF;
			obj->SetPosition(this->x, this->y);
			LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
			obj->SetAnimationSet(ani_set);
		}
	}
	else if (setting == 2)
	{
		int ani_set_id = 18;
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		obj = new CMushRoom(player->nx, 1);
		obj->type = OBJECT_TYPE_MUSHROOM;
		obj->SetPosition(this->x, this->y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	else if (setting == 3)
	{
		int ani_set_id = 107;
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		obj = new CPButton();
		obj->type = OBJECT_TYPE_PBUTTON;
		obj->SetPosition(this->x, this->y - 15);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}
	return obj;
}

