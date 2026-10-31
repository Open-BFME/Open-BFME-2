// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
//
// ?rva00498980@GateOpenAndCloseBehavior@@QAE_NXZ @0x00498980 (87B):
// Gate open/close state test. ModuleData at +8, state at +0x28, timer at
// +0x34. Case 2: (100 - percent) >= m_34; case 1: true; case 0: m_34 >
// percent; default false. Retail lays the true block first, so the source
// cases are ordered 2, 1, 0. Evidence: rowed win/timer callers, m_28 state
// values 0/1/2 from GateOpenAndCloseBehaviorCtorShard, /arch:SSE fcomi shape.
#include <vector>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../../Include/Common/BfmeModuleData.h"

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

bool GateOpenAndCloseBehavior::rva00498980()
{
	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	switch (m_state)
	{
	case 2:
		if ((float)(100 - data->m_percentOpen) >= m_34)
			return true;
		return false;
	case 1:
		return true;
	case 0:
		if (m_34 > (float)data->m_percentOpen)
			return true;
		return false;
	default:
		return false;
	}
}
