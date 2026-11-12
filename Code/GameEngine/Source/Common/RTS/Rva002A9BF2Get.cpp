// cl: /DNDEBUG /MD /EHsc
// ?rva002A9BF2@Rva002A9BF2@@QAEPAXXZ @ 0x002A9BF2 (27B). Unlock lane difficulty
// getter shared by 13 callers. Evidence: GameWindow at this+0x2DC tail-jmps to
// rowed winGetUserData 0x005C4ACD when present else returns TheScriptEngine
// difficulty at global 0x009FE16C plus 0x1A4C4. Callers 0x00203F0E and
// 0x0058AF47 use ecx-this with no stack args and treat eax as int index.

#include "../../../Include/GameClient/Bfme2GameWindow.h"

class ScriptEngine
{
public:
	char _pad[0x1A4C4];
	void *m_difficulty;
};

extern ScriptEngine *TheScriptEngine;

class Object;

class Rva002A9BF2
{
	char _pad[0x2DC];
	GameWindow *m_window;
public:
	void *rva002A9BF2();
	void rva002A9CCA(int val);
};

void *Rva002A9BF2::rva002A9BF2()
{
	GameWindow *gameWindow = m_window;
	if (gameWindow != 0)
		return gameWindow->winGetUserData();
	return TheScriptEngine->m_difficulty;
}

void Rva002A9BF2::rva002A9CCA(int val)
{
	GameWindow *gameWindow = m_window;
	if (gameWindow != 0)
		gameWindow->m_regionHiX = val;
}

// ?onStructureConstructionComplete@Player@@QAEXPAVObject@@0_N@Z @0x002A9D02 135B: ZH Player::onStructureConstructionComplete step for step (notify the script engine of object creation, remove then re-add the structure in the pathfind map, friend_adjustPowerForPlayer(TRUE), forward builder and structure to the player AI at +0x2DC slot 8, flag the control bar dirty); isRebuild is unread. Formerly rowed as the address-named view below. Evidence: same 0x2DC as Rva002A9BF2 siblings; callees rowed 0x002039B6 0x002E718A 0x002E7178 0x0028D99A 0x0028BD17 0x0028DA67; globals TheScriptEngine TheAI g_bfmeWorldRV; callers 0x002411DF 0x00241E17 0x003954B9 0x0048AC99.
#include "../../../Include/Common/Rva002039B6Host.h"

class Object;

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/AI.h"

extern AI *TheAI;
extern ScriptEngine *TheScriptEngine;

struct BfmeWorldRV
{
	char _pad[0x28];
	unsigned char m_28;
};

extern class ControlBar *TheControlBar;

#include "../../GameLogic/Object/object.h"

class GameWindowVirt
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8(int a1, Object *obj);
};

class SecondVirt
{
public:
	virtual void w0();
	virtual void w1();
	virtual void w2();
	virtual void w3(int a1);
};

#include "../../../Include/Common/Player.h"

void Player::onStructureConstructionComplete(Object *builder, Object *structure, bool isRebuild)
{
	int a1 = (int)builder;
	Object *obj = structure;
	((Rva002039B6Host *)TheScriptEngine)->rva002039B6();
	TheAI->m_pathfinder->RemoveObjectFromPathfindMap(obj);
	TheAI->m_pathfinder->AddObjectToPathfindMap(obj);
	obj->friend_adjustPowerForPlayer(true);
	if (m_ai)
		((GameWindowVirt *)m_ai)->v8(a1, obj);
	if ((*(BfmeWorldRV **)&TheControlBar))
		(*(BfmeWorldRV **)&TheControlBar)->m_28 = 1;
	if (obj->rva0028BD17())
		((SecondVirt *)obj->rva0028BD17())->w3(a1);
	obj->rva0028DA67();
	(void)isRebuild;
}
