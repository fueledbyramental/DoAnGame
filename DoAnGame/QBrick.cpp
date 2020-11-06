#include "QBrick.h"

CQBrick::CQBrick()
{
	SetState(BRICK_STATE_QUES);
}

void CQBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (GetTickCount() - ring_start > BRICK_RINGING_TIME)
	{
		ring_start = 0;
		ringing = 0;
	}

	float ace = 0;

	if (ringing)
	{
		if (GetTickCount() - ring_start >= BRICK_RINGING_TIME / 2)
			y += 1.4;
		else
			y -= 1;
	}
	//else
		//y += ace;

}

void CQBrick::Render()
{
	int ani = BRICK_ANI_QUES;
	if (state == BRICK_STATE_EMP) {
		ani = BRICK_ANI_EMP;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CQBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}