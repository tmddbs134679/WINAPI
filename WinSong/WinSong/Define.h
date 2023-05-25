#pragma once

#define SINGLE(Type) public: \
                          static Type* GetInst() \
										{\
										static Type mgr;\
										 return &mgr;\
										}\
									private:\
										Type();\
									   ~Type();

#define fDT CTimeMgr::GetInst()->GetfDeltaTime();
#define DT CTimeMgr::GetInst()->GetDeltaTime():

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()


#define PI 3.14159263535f

#define TILE_SIZE 64

#define CLONE(type) type* Clone() {return new type(*this);}

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,

	START,

	STAGE_01,

	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	END
};

enum class PLAYER_STATE
{
	//키입력 HOLD중인 입력 상태
	IDLE,
	WALK_UP,
	WALK_DOWN,
	WALK_LEFT,
	WALK_RIGHT,
	//마지막 키 입력 상태
	IWALK_UP,
	IWALK_DOWN,
	IWALK_LEFT,
	IWALK_RIGHT

};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,
	RUN,
	DEAD,
	END
};