#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
    CScene_Start();
    ~CScene_Start();

public:
    //virtual �Ⱥٿ��� ������ ��������� �ٿ���
   virtual void update();
   virtual void Enter();
   virtual void Exit();
    
};

