#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CMonFactory.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

 	if (KEY_TAP(KEY::ESC))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookat(vLookAt);
		
	}

}

void CScene_Start::Enter()
{
	//Object 추가
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject는 부모의 역할을 해야만 한다. 파생으로 만들어진 자식클래스로만 객체를 만들어야 함.
	//객체를 생성해서 보여지는거 자체가 수행되면 안된다.
	//CObject* pObj = new CObject;
	//pObj->SetPos(Vec2(640.f, 384.f));
	//pObj->SetSacle(Vec2(100.f, 100.f));
	//AddObject(pObj, GROUP_TYPE::DEFAULT);

	//CObject* pOtherPlayer = pObj->Clone();
	// pObj->SetPos(Vec2(740.f, 384.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	//Vec2 생성과 동시에 대입은 복사생성자가 된다.
	//반환은 vec2타입이아니라 생성자 쪽에서 해결해줘야한다.

	//몬스터 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonster = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f,300.f));
	AddObject(pMonster, GROUP_TYPE::MONSTER);

	//충돌 지정
	//Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//Camera Look 지정
	//해상도 절반위치
	
	CCamera::GetInst()->SetLookat(vResolution / 2.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}
