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
	//Object �߰�
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject�� �θ��� ������ �ؾ߸� �Ѵ�. �Ļ����� ������� �ڽ�Ŭ�����θ� ��ü�� ������ ��.
	//��ü�� �����ؼ� �������°� ��ü�� ����Ǹ� �ȵȴ�.
	//CObject* pObj = new CObject;
	//pObj->SetPos(Vec2(640.f, 384.f));
	//pObj->SetSacle(Vec2(100.f, 100.f));
	//AddObject(pObj, GROUP_TYPE::DEFAULT);

	//CObject* pOtherPlayer = pObj->Clone();
	// pObj->SetPos(Vec2(740.f, 384.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	//Vec2 ������ ���ÿ� ������ ��������ڰ� �ȴ�.
	//��ȯ�� vec2Ÿ���̾ƴ϶� ������ �ʿ��� �ذ�������Ѵ�.

	//���� ��ġ
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonster = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f,300.f));
	AddObject(pMonster, GROUP_TYPE::MONSTER);

	//�浹 ����
	//Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//Camera Look ����
	//�ػ� ������ġ
	
	CCamera::GetInst()->SetLookat(vResolution / 2.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}
