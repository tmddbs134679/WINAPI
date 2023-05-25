#pragma once

#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{

	friend class CEventMgr;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

public:

	virtual void update() = 0;
	virtual void render(HDC _dc);
	//오버라이딩을 금지시킨다. 마무리 함수
	virtual void finalupdate();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	virtual CObject* Clone() = 0;
	
public:

	void component_render(HDC _dc);
	void CreateCollider();
	void CreateAnimator();

public:

	bool ISDead()
	{
		return !m_bAlive;
	}
public:

	void SetPos(Vec2 _vPos)
	{
		m_vPos = _vPos;
	}
	
	void SetScale(Vec2 _vSacle)
	{
		m_vScale = _vSacle;
	}

	void SetName(wstring _strName)
	{
		m_strName = _strName;
	}

private:

	void SetDead()
	{
		m_bAlive = false;
	}

public:

	Vec2 GetPos()
	{
		return m_vPos;
	}

	Vec2 GetScale()
	{
		return m_vScale;
	}

	CCollider* GetCollider()
	{
		return m_pCollider;
	}

	CAnimator* GetAnimator()
	{
		return m_pAnimator;
	}

	const wstring& GetName()
	{
		return m_strName;
	}
	
private:
	Vec2		m_vPos;
	Vec2		m_vScale;


	CCollider*	m_pCollider;
	CAnimator*  m_pAnimator;

	wstring		m_strName;

	bool		m_bAlive;
};

