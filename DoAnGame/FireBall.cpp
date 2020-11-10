#include "FireBall.h"

CFireBall::CFireBall(int nx)
{
	//SetState(FIREBALL_STATE_SPIN);
	vx = FIREBALL_SPIN_SPEED * nx;
	this->nx = nx;
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)	//turn of boundingbox
	{
		l = NULL;
		t = NULL;
		r = NULL;
		b = NULL;
	}
	else
	{

		l = x;
		t = y;
		r = x + FIREBALL_BBOX_WIDTH;
		b = y + FIREBALL_BBOX_HEIGHT;
	}
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float scrw = game->GetScreenWidth();
	float scrh = game->GetScreenHeight();
	game->GetCamPos(camx, camy);

	if (x < camx || x > camx + scrw)						// delete fireball if out map
		isFinish = 1;
	if (y < camy || y > camy + scrh)
		isFinish = 1;

	if (isFinish)
		return;

	CGameObject::Update(dt);
	x += dx;
	y += dy;
	vy += FIREBALL_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	if (nx != 0)				// reflect 
		vx = -vx;
	if (ny != 0)
		vy = -FIREBALL_DEFLECT_SPEED;

	for (int i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (e->nx != 0 && e->ny == 0)
		{
			isFinish = 1;			//delete fireball when collide with wall
		}
		if (dynamic_cast<CGoomba*>(e->obj))			// object is goomba
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			goomba->SetState(GOOMBA_STATE_DIE_DEFLECT);
			goomba->vx = 0.05f * this->nx;
		}
		else if (dynamic_cast<CKoopas*>(e->obj))	// object is koopas
		{
			CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
			koopas->SetState(KOOPAS_STATE_DIE_DEFLECT);
			//koopas->vx = 0.05f * this->nx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CFireBall::Render()
{
	if (isFinish)
		return;
	int ani = FIREBALL_SPIN_RIGHT;
	if (vx > 0) ani = FIREBALL_SPIN_RIGHT;
	else if (vx <= 0) ani = FIREBALL_SPIN_LEFT;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}


void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_SPIN:
		vx = FIREBALL_SPIN_SPEED;
		break;
	}
}