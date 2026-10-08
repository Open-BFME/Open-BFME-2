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

class Object;
class Thing;
class ModuleData;

unsigned char Rva00498B8BGet(Object *object);

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class GateOpenBehaviorList
{
public:
	void rva004E908C(void *item);
};

class Rva002A8F24
{
public:
	unsigned char m_pad[0x940];
	GateOpenBehaviorList *m_gateList; // +0x940
};
extern Rva002A8F24 *g_00DFEEF8;

class GatePrimary
{
public:
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

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
struct BehaviorModuleInterface { virtual void f0C() {} };
struct UpdateModuleInterface { virtual void f10() {} };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	virtual ~GateOpenAndCloseBehavior();
	virtual bool rva00498BAF(Object *object);
	virtual void open();
	virtual void close();
	virtual void rva00498806();
private:
	void rva00498FAA();
	void setOpenCloseState(int state);
	int m_24;
	int m_28; // +0x28
	int m_2C; // +0x2C
	bool m_30; // +0x30
	float m_34; // +0x34
	float m_38;
	unsigned int m_3C; // +0x3C
};

// ??1GateOpenAndCloseBehavior@@UAE@XZ @0x00498798
GateOpenAndCloseBehavior::~GateOpenAndCloseBehavior()
{
	GateOpenBehaviorList *list = g_00DFEEF8->m_gateList;
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
		m_3C = TheGameLogic->getFrame();
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
		m_3C = TheGameLogic->getFrame();
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
