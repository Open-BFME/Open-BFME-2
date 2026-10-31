// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
// ?rva004992D5@GateOpenAndCloseBehavior@@AAEX_N0@Z @0x004992D5 149B: private helper
// with two flags; if +0x2C==2 then first flag must hold else return; second flag
// runs pinned 0x00498FAA; removes object from pathfind shim, sets state 2 via
// Object::setArmorSetFlag(9), sets two BfmeStrF9 vectors through Object+0xA8
// setFlag(1/0), notifies via Object::rva0028AB75(true), re-adds to pathfind
// shim. Evidence: rowed callees 0x002E71AD 0x0028B78A 0x006BF3C0 0x0028AB75
// 0x002E7178 plus pin 0x00498FAA; callers 0x0049939B 0x004E8FA5 0x004E906D;
// neighbour GateOpenAndCloseBehaviorRva0049924B.
#include <vector>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/Common/BfmeModuleData.h"
#include "../../../Common/Thing/thing.h"

enum NameKeyType { NK_UNKNOWN = 0 };

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

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMapKeepingGateFlags(Object *object);
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_10; // +0x10
};

extern AI *TheAI;

void GateOpenAndCloseBehavior::rva004992D5(bool a, bool b)
{
	if (m_2C == 2)
	{
		if (!a)
			return;
	}
	if (b)
		rva00498FAA();
	Pathfinder *shim = TheAI->m_10;
	Object *obj = m_object;
	shim->RemoveObjectFromPathfindMapKeepingGateFlags(obj);
	m_2C = 2;
	obj->setArmorSetFlag((ArmorSetType)9);
	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	for (const AsciiString *p = data->m_geometryForOpen.begin(); p != data->m_geometryForOpen.end(); ++p)
		(&obj->m_objA8)->setFlag(*(const BfmeStrF9 *)p, 1);
	for (const AsciiString *p = data->m_geometryForClosed.begin(); p != data->m_geometryForClosed.end(); ++p)
		(&obj->m_objA8)->setFlag(*(const BfmeStrF9 *)p, 0);
	obj->rva0028AB75(true);
	TheAI->m_10->AddObjectToPathfindMap(obj);
}
