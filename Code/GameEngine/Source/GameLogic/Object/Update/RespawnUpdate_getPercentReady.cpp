// cl: /DNDEBUG /MD /GX
//
// ?getPercentReady@RespawnUpdate@@UAEMPAH@Z, retail 0x004AEFAD, 94 bytes.
// Vslot 13 (offset 0x34) of vtable 0x008556B0 (VA 0x00C556B0), class of
// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z in
// Code/GameEngine/Source/GameLogic/Object/Update/RespawnUpdateCtor.cpp.
// Layout follows that TU: UpdateModule base 0x20 (secondaries at +0x0C/+0x10),
// RespawnUpdate m_20 at +0x20, state m_2C at +0x2C, start m_34 at +0x34,
// duration m_38 at +0x38, out m_3C at +0x3C. No callers. Global
// TheGameLogic at 0x00DFE78C (+0x40 frame) via GameLogicFrame::getFrame.
// Pooled floats 0.0 at 0x007BAEAC, 1.0 at 0x007BB8D8, 2^32 at 0x007C26EC.
// Retail dec-chain (sub 0 plus four decs) proves six consecutive states
// 0..5: 0/2/4/5/default return 0.0, 1 returns 1.0, 3 computes
// (frame - m_34) / m_38 with unsigned frame conversion (fild plus 2^32
// fixup) and jle zero guard. Honest address name; identity is class plus slot.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
enum DisabledType;
enum ObjectStatusTypes;
class Player;
class ExitInterface;
class BodyModuleInterface;
class FXList;
class ThingTemplate;
class Image;
class AIUpdateInterface;
class INI;
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface {public:virtual void slot0()=0;};

class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {public:virtual ~BehaviorModule();};

class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};

class UpdateModule:public BehaviorModule,public UpdateModuleInterface {public:virtual ~UpdateModule();protected:void setWakeFrame(Object *,UpdateSleepTime);private:unsigned nextWake;int index,reserved;};


class RespawnUpdate:public UpdateModule {
public:
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;
	virtual float getPercentReady(int *out);
	virtual const Image *getDeadImage();
	void rva004AF182();
	void *rva004AF25D();
	Object *searchForSuitableSpawnAtObject();
	static void iniParseNewRuleForLevel(INI *, void *, void *, const void *);
	static void iniParseDefaultRule(INI *, void *, void *, const void *);
public:
	float health;
	const Image *deadImage;
	void *respawnTemplate;
	unsigned state;
	ObjectID spawnAt;
	int at34,at38,at3C;
	bool at40,at41;
};


float RespawnUpdate::getPercentReady(int *out)
{
	if (out)
		*out = at3C;
	switch (state)
	{
	case 0:
		return 0.0f;
	case 1:
		return 1.0f;
	case 2:
		return 0.0f;
	case 3:
		break;
	case 4:
		return 0.0f;
	case 5:
		return 0.0f;
	default:
		return 0.0f;
	}
	int total = at38;
	if (total <= 0)
		return 0.0f;
	unsigned int frame = TheGameLogic->getFrame();
	return ((float)frame - at34) / total;
}
