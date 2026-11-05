// cl: /DNDEBUG /MD
//
// ?xfer@MonsterDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A14C2, 85 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00851D74 (class of rowed ctor
// ??0MonsterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004A139A in
// MonsterDockUpdateCtor.cpp): base DockUpdate xfer via rowed 0x0058A410
// then IsLightCRC early-out via Xfer slot 0x10 then bool at +0x88 via Xfer
// slot 0x90 then int at +0x8C via Xfer slot 0x7C then bool at +0x89 via Xfer
// slot 0x90 then Version1 via rowed 0x000053EE last. Layout is DockUpdate
// base 0x88 plus two bools plus int (BFME1 donor
// MonsterDockUpdateConstructor.cpp: bool m_dockOpen plus bool m_actionStarted plus
// int m_value8c; ctor sets 1/0/0). Donor is BFME1 plus ZH.

#include <string.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Matrix3D;
enum PathfindLayerEnum { LAYER_GROUND=0 };
class Drawable;
class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[20];
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_03 = 3,
	OBJECT_STATUS_3C = 0x3c
};
enum DisabledType
{
	DISABLED_03 = 3
};
enum DamageType
{
	DAMAGE_08 = 8
};
enum DeathType
{
	DEATH_09 = 9
};
#include "../../../../Include/GameClient/Drawable.h"
class Object : public Thing
{
public:
	void rva0028AE6D();
 void teleportTo(const Coord3D *, bool);
 int rva0028B511() const;
 __forceinline void clearCondition(int b) { if(m_conditionBits.test(b)) {m_conditionBits.clear(b);rva0028AE6D();} }
 __forceinline void replaceCondition(int off,int on) { if(m_conditionBits.test(off) || !m_conditionBits.test(on)) {m_conditionBits.clear(off);m_conditionBits.set(on);rva0028AE6D();} }
	void setStatus(ObjectStatusTypes status, bool set);
	void setDisabled(DisabledType type);
	bool clearDisabled(DisabledType type);
	void kill(DamageType damageType, DeathType deathType);
	unsigned char m_pad60[0x10C - 0x60];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class ModuleData;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};



class DockUpdateInterface
{
public:
	virtual bool isClearToApproach(const Object *docker) const = 0;
	virtual bool reserveApproachPosition(Object *docker, Coord3D *position, int *index) = 0;
	virtual bool advanceApproachPosition(Object *docker, Coord3D *position, int *index) = 0;
	virtual bool isClearToEnter(const Object *docker) const = 0;
	virtual bool isClearToAdvance(const Object *docker, int dockerIndex) const = 0;
	virtual void getEnterPosition(Object *docker, Coord3D *position) = 0;
	virtual void getDockPosition(Object *docker, Coord3D *position) = 0;
	virtual void getExitPosition(Object *docker, Coord3D *position) = 0;
	virtual void onApproachReached(Object *docker) = 0;
	virtual void onEnterReached(Object *docker) = 0;
	virtual void rva004A1610(Object *docker) = 0;
	virtual void onExitReached(Object *docker) = 0;
	virtual bool action(Object *docker, Object *drone) = 0;
	virtual void cancelDock(Object *docker) = 0;
	virtual bool isDockOpen() = 0;
	virtual void setDockOpen(bool open) = 0;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
protected:
	virtual void loadPostProcess();
public:
	virtual void onApproachReached(Object *docker);
	virtual void onEnterReached(Object *docker);
	virtual void cancelDock(Object *docker);
protected:
	virtual void xfer(Xfer *xfer);
	unsigned char m_pad24[0x88 - 0x24];
};

class MonsterDockUpdate : public DockUpdate
{
protected:
	virtual void loadPostProcess();
public:
	virtual void onApproachReached(Object *docker);
	virtual void onEnterReached(Object *docker);
	virtual void onExitReached(Object *docker);
	virtual void setDockOpen(bool open);
 virtual bool action(Object *, Object *);
	virtual void rva004A1610(Object *docker);
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_dockOpen; // +0x88
 bool m_actionStarted; // +0x89
 int m_actionEnd; // +0x8C
};

// The ZH DockUpdateInterface::action contract and repair/delivery actions are
// semantic ancestors. The Monster implementation is BFME-specific: native
// 4A1659..4A17C1, its ctor-installed C51D18 slot12, and xfer of 89/8C prove
// the wait state. Target bits clear305 and replace82->83 before the wait;
// completion teleports through the dock bone, resets bits81..84 and unhides.
class MonsterDockUpdateModuleData { public: char m_pad00[0x14]; unsigned int m_actionFrames; };

#include "../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

class Rva001E42F2 {public: void rva001E42F2(const int *);};

void MonsterDockUpdate::xfer(Xfer *xfer)
{
	DockUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_dockOpen;
	*xfer == m_actionEnd;
	*xfer == m_actionStarted;
	xfer->Version1();
}
