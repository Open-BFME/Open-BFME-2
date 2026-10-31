// cl: /DNDEBUG /MD /EHsc
// ?changeWantOpenCount@GateOpenAndCloseBehavior@@QAEXH@Z @0x00498831 30B
// GateOpenAndCloseBehavior delta clamp-add at +0x40. Evidence: gap between
// Disp8ByteFieldGetters and GateOpenAndCloseBehaviorPoolKey; offset 0x40
// matches m_40 in GateOpenAndCloseBehaviorCtorShard; caller 0x003A23A5.
#include "../../../../Include/Common/ObjectModule.h"

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

void GateOpenAndCloseBehavior::changeWantOpenCount(int delta)
{
	if (delta == -1 || delta == 1) {
		if (m_request < 0)
			m_request = 0;
		m_request += delta;
	}
}
