#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
    CScene_Start();
    ~CScene_Start();

public:
    //virtual 안붙여도 되지만 명시적으로 붙여줌
   virtual void update();
   virtual void Enter();
   virtual void Exit();
    
};

