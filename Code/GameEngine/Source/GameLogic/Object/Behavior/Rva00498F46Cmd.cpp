// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
//
// ?rva00498DF3@GateOpenAndCloseBehavior@@QAEXPAURva00498DF3Arg@@M@Z, retail 0x00498DF3, 59 bytes.
// Evidence: calls rowed 0x00262DD3 AIUpdateInterface::rva00262DD3 and rowed 0x0026C411 AICommandInterface::aiMoveAwayFromUnit; Object+0x38 Coord3D and CMD_FROM_AI=2 match donors; caller at 0x00498F9E pushes ebp plus float and tests nothing; this+0xC Object pattern matches caller 0x00498F46.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <vector>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/Common/BfmeModuleData.h"
#include "../../../Common/Thing/thing.h"

enum NameKeyType { NK_UNKNOWN = 0 };

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum ObjectID;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum UpdateSleepTime;

class GateOpenAndCloseBehaviorModuleData;
struct Rva00498DF3Arg;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_bfmeReserved; // +0x1C
};

// 4-byte polymorphic primary at +0. Inline ctor installs the first vtable
// ahead of the UpdateModule call; the implicit trivial dtor arms nothing
// (the single EH state completes with the UpdateModule construction, whose
// mirror carries the declared-only dtor).
class GatePrimary
{
public:
	GatePrimary() {}
	virtual void gap0() = 0;
	virtual bool rva00498BAF(Object *object) = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual bool slot6() const = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void rva00498806() = 0;
	virtual unsigned char slot10() const = 0;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GateOpenAndCloseBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual UpdateSleepTime update();
	virtual bool rva00498BAF(Object *object);
	virtual void open();
	virtual void close();
	virtual void rva00498806();
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Player *p) const;
	void changeWantOpenCount(int delta);
	bool rva00498980();
	void rva00498DF3(Rva00498DF3Arg *unit, float flt);
	void rva00498F46(Rva00498DF3Arg *unit, int u1, int u2);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void rva004989F5();
	void setOpenCloseState(int state);
	void rva00498FAA();
	void rva0049924B(bool flag);
	void rva004992D5(bool a, bool b);

	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return (const GateOpenAndCloseBehaviorModuleData *)m_moduleData;
	}
	Object *getObject() const { return m_object; }

	ObjectID m_linkedObjectId; // +0x24
	int m_state; // +0x28
	int m_2C; // +0x2C
	bool m_30; // +0x30
	float m_34; // +0x34
	float m_38; // +0x38
	unsigned int m_stateFrame; // +0x3C
	int m_request; // +0x40
	unsigned int m_soundHandle; // +0x44
	bool m_soundPlayed; // +0x48
};

enum ArmorSetType { ARMORSET_NONE = 0 };

enum ObjectID;

// How the rowed setFlag 0x006BF3C0 names its argument, one of the module
// data's geometry-name AsciiStrings.
class BfmeStrF9
{
public:
	unsigned char m_pad[4];
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

// The object's template as this unit reads it: +0xB0 the gate's cylinder
// radius, +0x108 the flag byte the rowed test 0x00498B8B masks with 4.
class ThingTemplate
{
public:
	char m_pad00[0xB0];
	float m_B0; // +0xB0
	char m_padB4[0x108 - 0xB4];
	unsigned char m_flag108; // +0x108
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Player *getControllingPlayer() const;
	int rva0028B511() const;
	void clearArmorSetFlag(ArmorSetType v);
	void setArmorSetFlag(ArmorSetType v);
	void rva0028AB75(bool v);

protected:
	friend class GateOpenAndCloseBehavior;
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x88 - 0x78];
	AsciiString m_name; // +0x88
	Object *m_next; // +0x8C
	unsigned char m_pad090[0xA8 - 0x90];
public:
	BfmeObjF9 m_objA8; // +0xA8
private:
	unsigned char m_pad0A9[0x438 - 0xA9];
	unsigned char m_438; // +0x438
};

class GateRefHolder : public OpaqueRefElement4
{
public:
	GateRefHolder() { referent = 0; }
	~GateRefHolder() { if (referent) referent->Release_Ref(); }
};

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
	GateOpenAndCloseBehaviorModuleData();
	virtual ~GateOpenAndCloseBehaviorModuleData();

	int m_unused04; // +4 untouched padding
	bool m_openByDefault; // +8
	unsigned char m_pad09[3];
	unsigned int m_resetTime; // +0xC ResetTimeInMilliseconds
	unsigned int m_percentOpen; // +0x10 PercentOpen
	AsciiString m_proxy; // +0x14 Proxy, the partner gate's name
	bool m_repel; // +0x18
	unsigned char m_pad19[3];
	GateRefHolder m_openingSound; // +0x1C
	GateRefHolder m_openSound; // +0x20
	GateRefHolder m_closingSound; // +0x24
	GateRefHolder m_closeSound; // +0x28
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_geometryForOpen; // +0x2C
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_geometryForClosed; // +0x38
	int m_snap44; // +0x44
	int m_snap48; // +0x48
};

class AIUpdateInterface
{
public:
	bool rva00262DD3(const Object *obj) const;
	Object *getCurrentVictim() const;
};

class AICommandInterface
{
public:
	void aiMoveAwayFromUnit(Object *victim, const Coord3D *pos, CommandSourceType cmdSource);
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

unsigned char __cdecl Rva00498B8BGet(Object *p);

extern float g_00C50244;
// g_00C50244: matched references place it at VA 0xc50244 (retail .rdata value 16.67f).
float g_00C50244 = 16.67f;

struct Rva00498DF3Mid
{
	char m_pad[0x20];
	char m_cmd20[0x10];
	TurretStateMachine *m_turretStateMachine;
};

struct Rva00498DF3Arg
{
	char m_pad[0x258];
	Rva00498DF3Mid *m_ai;
};

void GateOpenAndCloseBehavior::rva00498DF3(Rva00498DF3Arg *unit, float flt)
{
	Object *obj = m_object;
	if (!obj)
		return;
	if (!unit)
		return;
	Rva00498DF3Mid *mid = unit->m_ai;
	if (!mid)
		return;
	if (((AIUpdateInterface *)mid)->rva00262DD3(obj))
		return;
	((AICommandInterface *)((char *)mid + 0x20))->aiMoveAwayFromUnit(obj, obj->getPosition(), CMD_FROM_AI);
}

void GateOpenAndCloseBehavior::rva00498F46(Rva00498DF3Arg *unit, int u1, int u2)
{
	if (!getGateModuleData()->m_repel)
		return;
	if (m_2C != 1)
		return;
	if (!Rva00498B8BGet((Object *)unit))
		return;
	Rva00498DF3Mid *mid = unit->m_ai;
	if (mid != 0)
	{
		Object *object = m_object;
		if (mid->m_turretStateMachine->getGoalObject() == object)
			return;
		Object *gateObject = m_object;
		if (((AIUpdateInterface *)mid)->getCurrentVictim() == gateObject)
			return;
	}
	rva00498DF3(unit, g_00C50244);
}
