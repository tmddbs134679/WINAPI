#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include"CCollider.h"
#include "AI.h"



CMonster::CMonster()
	: MonsterInfo{}
{
	CreateCollider();
	GetCollider()->setScale(Vec2(60.f, 60.f));
}

CMonster::~CMonster()
{
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::update()
{
	m_pAI->update();
}



void CMonster::Attack()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	//pMissile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	


	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}


void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();


	if (pOtherObj->GetName() == L"Missile_Player" || pOtherObj->GetName() == L"Missile_Player2" || pOtherObj->GetName() == L"Missile_Player3")
	{
		
	}
}