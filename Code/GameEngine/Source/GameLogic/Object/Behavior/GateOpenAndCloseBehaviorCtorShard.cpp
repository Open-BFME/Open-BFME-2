// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
//
// ??0GateOpenAndCloseBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x0049889C, 200 bytes.
//
// GateOpenAndCloseBehavior behavior ctor. The class is multiple inheritance:
// a 4-byte polymorphic primary at +0 (identity open; its inline ctor installs
// the first vtable) plus UpdateModule at +4 (the rowed 0x253390 body).
// UpdateModule stores the module data at its +4 through the ObjectModule row,
// so the behavior reads its table values through [this+8]: OpenByDefault at
// module+8 picks count 1-or-3, ResetTimeInMilliseconds at module+0xC feeds the
// 100.0f divisor. The -1 at +0x40 is a member initializer: it lands ahead of
// the compiler's vptr stores (0x00C50178 +0, 0x00C50144 +4, 0x00BEF248 +0x10,
// 0x00C50138 +0x14), as in retail.
// The new behavior registers itself into the global gate list at
// [0xDFEEF8]+0x940 through the rowed appendOnce helper; the list owner itself
// is unidentified, so it is reached through its data-ledger name TheSkirmishAIManager. Row supersedes the
// same-name pin; the instance factory (0x24E28B, news 0x4C) stays green via
// the row, as does the appendOnce home TU.
//
// Schedule notes (all probe-proven): the or-minus-one stays first in source
// (Prone law); the 1-or-3 ternary reads openByDefault for the sete form; the
// quotient stays in st0 across the 100.0f store; the push-this for the tail
// call hoists on its own. /arch:SSE is load-bearing for the movss pair (the
// /O1 default emits an integer mov); the appendOnce home TU keeps its own
// flags in a separate shard (same-class-in-2-TUs precedent).

// GateOpenAndCloseModuleData layout from INI table 0xBF19F8: OpenByDefault
// at +8, ResetTimeInMilliseconds at +0xC (UpdateModuleData base runs to +8).
// unidentified, so the +0x940 list is reached by offset.
#include <vector>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/Common/BfmeModuleData.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum NameKeyType { NK_UNKNOWN = 0 };

class GateOpenBehaviorList
{
public:
	void rva004E908C(void *item);
	void appendOnce(void *item);
	void push_back(void *const &item);
private:
	void **m_begin; // +0x00
	void **m_end; // +0x04
};

class Rva002A8F24
{
public:
	unsigned char m_pad[0x940];
	GateOpenBehaviorList *m_gateList; // +0x940
};

// The list owner at 0x00DFEEF8 (data ledger name TheSkirmishAIManager); its class is
// unidentified, so its view names only the list at +0x940.
extern Rva002A8F24 *TheSkirmishAIManager;

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

// ??0GateOpenAndCloseBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x49889C
GateOpenAndCloseBehavior::GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData)
	: GatePrimary(), UpdateModule(thing, moduleData), m_request(-1)
{
	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	m_soundHandle = 1;
	m_soundPlayed = false;
	m_state = data->m_openByDefault ? 1 : 3;
	m_30 = true;
	m_38 = 100.0f / data->m_resetTime;
	m_34 = 100.0f;
	m_stateFrame = TheGameLogic->getFrame();
	m_2C = 0;
	m_linkedObjectId = INVALID_OBJECT_ID;
	TheSkirmishAIManager->m_gateList->appendOnce(this);
}
