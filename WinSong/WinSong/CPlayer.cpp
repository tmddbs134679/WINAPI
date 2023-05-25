#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"



CPlayer::CPlayer()
{
	//Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\magic1.bmp");

	

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f,0.f));
	GetCollider()->setScale(Vec2(40.f, 35.f));
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\animator.bmp");
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 100.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 200.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 300.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);

	GetAnimator()->CreateAnimation(L"IWALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IWALK_UP", pTex, Vec2(0.f, 100.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IWALK_LEFT", pTex, Vec2(0.f, 200.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);
	GetAnimator()->CreateAnimation(L"IWALK_RIGHT", pTex, Vec2(66.75f, 300.f), Vec2(66.75f, 100.f), Vec2(66.75f, 0.f), 0.3f, 1);




	CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE");
	
	

	for(UINT i=0; i < pAnim->GetMaxFrame(); ++i)
	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);

	m_FinalState = PLAYER_STATE::IDLE;
	finalDir = Vec2(Vec2(0.f, -1.f));
	 
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	//비록 상속받은 변수지만 디버깅할 때 쉽게 찾기 위해, 안전성을 높히기 위해 직접 사용하지 않고
	//Get으로 가져와서 구현한다
	Vec2 vPos = GetPos();
	bool bIsMoving = false;
	SetState(PLAYER_STATE::IDLE);
	

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
		SetState(PLAYER_STATE::WALK_UP);
		m_FinalState = PLAYER_STATE::IWALK_UP;
		bIsMoving = true;
		finalDir = Vec2(Vec2(0.f, -1.f));

	}
	else if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
		SetState(PLAYER_STATE::WALK_DOWN);
		m_FinalState = PLAYER_STATE::IWALK_DOWN;
		bIsMoving = true;
		finalDir = (Vec2(0.f, 1.f));
	}
	else if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
		SetState(PLAYER_STATE::WALK_LEFT);
		m_FinalState = PLAYER_STATE::IWALK_LEFT;
		finalDir = (Vec2(-1.f, 0.f));
		bIsMoving = true;
	}
	else if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
		SetState(PLAYER_STATE::WALK_RIGHT);
		m_FinalState = PLAYER_STATE::IWALK_RIGHT;
		bIsMoving = true;
		finalDir = (Vec2(1.f, 0.f));
	}
	if (!bIsMoving)
	{
		SetState(m_FinalState);

	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();

	}

	SetPos(vPos);

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	 //컴포넌트 (충돌체, etc...)가 있는 경우 렌더
	 component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	//vMissilePos.y -= GetScale().y / 4.f;
	 

	CMissile* pMissile2 = new CMissile;
	pMissile2->SetName(L"Missile_Player2");
	pMissile2->SetPos(vMissilePos);
	pMissile2->SetScale(Vec2(20.f, 20.f));
	pMissile2->SetDir(finalDir);
	

	if (KEY_HOLD(KEY::W))
	{
		pMissile2->SetDir(finalDir);
	}
	else if (KEY_HOLD(KEY::S))
	{
		pMissile2->SetDir(finalDir);
	}
	else if (KEY_HOLD(KEY::D))
	{
		pMissile2->SetDir(finalDir);
	}
	else if (KEY_HOLD(KEY::A))
	{
		pMissile2->SetDir(finalDir);
	}
	
 
 	CreateObject(pMissile2, GROUP_TYPE::PROJ_PLAYER);

}

void CPlayer::UpdateAnimation()
{
	switch (m_state)
	{
	case PLAYER_STATE::IDLE:
		GetAnimator()->Play(L"IDLE", true);
		break;

	case PLAYER_STATE::WALK_UP:
		GetAnimator()->Play(L"WALK_UP", true);

		break;

	case PLAYER_STATE::WALK_DOWN:
		GetAnimator()->Play(L"WALK_DOWN", true);
		break;

	case PLAYER_STATE::WALK_LEFT:
		GetAnimator()->Play(L"WALK_LEFT", true);
		break;

	case PLAYER_STATE::WALK_RIGHT:
		GetAnimator()->Play(L"WALK_RIGHT", true);
		break;

	case PLAYER_STATE::IWALK_UP:
		GetAnimator()->Play(L"IWALK_UP", true);

		break;

	case PLAYER_STATE::IWALK_DOWN:
		GetAnimator()->Play(L"IWALK_DOWN", true);
		break;

	case PLAYER_STATE::IWALK_LEFT:
		GetAnimator()->Play(L"IWALK_LEFT", true);
		break;

	case PLAYER_STATE::IWALK_RIGHT:
		GetAnimator()->Play(L"IWALK_RIGHT", true);
		break;

	}
}