// cl: /DNDEBUG /MD /GX
//
// Four GateOpenAndCloseBehavior overrides on the primary vtable 0x00C50178
// that its matched ctor 0x0049889C installs at +0 (the gate interface ahead of
// UpdateModule at +4). Names are by address. Slot 6 is the bool getter
// 0x004D86B1, slot 10 the byte getter 0x00498802; the matched xfer and ctor
// give the state int at +0x28 (1 or 3 from OpenByDefault), the int at +0x2C,
// the bool at +0x30, the float at +0x34 and the frame stamp at +0x3C.
//
// ?rva00498BAF@GateOpenAndCloseBehavior@@UAE_NPAVObject@@@Z, retail
// 0x00498BAF, 28 bytes: slot 1; false unless +0x2C is 1, then the rowed
// object test 0x00498B8B.
// ?open@GateOpenAndCloseBehavior@@UAEXXZ, retail 0x004991CB, 64
// bytes: slot 7; when slot 10 holds and slot 6 does not, runs the pinned
// member 0x00498FAA, sets state 0 through the pinned setter 0x00498AB2 and
// restarts the timer (+0x30 false, +0x34 zero, +0x3C the current frame).
// ?close@GateOpenAndCloseBehavior@@UAEXXZ, retail 0x0049920B, 64
// bytes: slot 8; the same when slot 6 holds, with state 2.
// ?rva00498806@GateOpenAndCloseBehavior@@UAEXXZ, retail 0x00498806, 23
// bytes: slot 9; slot 8 when slot 6 holds, else slot 7.
//
// The destructor family enters through the UpdateModule vtable 0x00C50144 at
// +4, so its slot 0 holds an adjustor thunk:
// ??1GateOpenAndCloseBehavior@@UAE@XZ, retail 0x00498798, 92 bytes: restores
// the four vptrs (0x00C50178 +0, 0x00C50144 +4, 0x00BEF248 +0x10, 0x00C50138
// +0x14), removes this from the global gate list ([0x00DFEEF8]+0x940, the
// list the ctor appends to) through the rowed 0x004E908C, then runs the
// UpdateModule base dtor 0x0024A797.
// ??_GGateOpenAndCloseBehavior@@UAEPAXI@Z, retail 0x00498964, 28 bytes.
// ??_EGateOpenAndCloseBehavior@@W3AEPAXI@Z, retail 0x0049884F, 8 bytes:
// this-4 then the deleting dtor.

#include "../../../../Include/Common/ObjectModule.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

unsigned char Rva00498B8BGet(Object *object);

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
extern Rva002A8F24 *TheSkirmishAIManager;

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

// ??1GateOpenAndCloseBehavior@@UAE@XZ @0x00498798
GateOpenAndCloseBehavior::~GateOpenAndCloseBehavior()
{
	GateOpenBehaviorList *list = TheSkirmishAIManager->m_gateList;
	list->rva004E908C(this);
}

// ?rva00498BAF@GateOpenAndCloseBehavior@@UAE_NPAVObject@@@Z @0x00498BAF
bool GateOpenAndCloseBehavior::rva00498BAF(Object *object)
{
	if (m_2C != 1)
		return false;
	return (bool)Rva00498B8BGet(object);
}

// ?open@GateOpenAndCloseBehavior@@UAEXXZ @0x004991CB
void GateOpenAndCloseBehavior::open()
{
	if (slot10() && !slot6())
	{
		rva00498FAA();
		setOpenCloseState(0);
		m_30 = false;
		m_34 = 0.0f;
		m_stateFrame = TheGameLogic->getFrame();
	}
}

// ?close@GateOpenAndCloseBehavior@@UAEXXZ @0x0049920B
void GateOpenAndCloseBehavior::close()
{
	if (slot10() && slot6())
	{
		rva00498FAA();
		setOpenCloseState(2);
		m_30 = false;
		m_34 = 0.0f;
		m_stateFrame = TheGameLogic->getFrame();
	}
}

// ?rva00498806@GateOpenAndCloseBehavior@@UAEXXZ @0x00498806
void GateOpenAndCloseBehavior::rva00498806()
{
	if (slot6())
		close();
	else
		open();
}
