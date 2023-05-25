#pragma once
#include "CObject.h"



class CTexture;


class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
 

public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    void SetState(PLAYER_STATE _state)
    {
        m_state = _state;
        UpdateAnimation();
    }

private:
    void CreateMissile();
    void UpdateAnimation();


private:

    CLONE(CPlayer);

  
private:
   
    PLAYER_STATE m_state;

    PLAYER_STATE m_FinalState;

    Vec2 finalDir;
   
};

