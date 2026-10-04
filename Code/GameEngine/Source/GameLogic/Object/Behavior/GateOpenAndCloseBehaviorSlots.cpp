// cl: /O1 /DNDEBUG /MD /arch:SSE
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
// ?rva004991CB@GateOpenAndCloseBehavior@@UAEXXZ, retail 0x004991CB, 64
// bytes: slot 7; when slot 10 holds and slot 6 does not, runs the pinned
// member 0x00498FAA, sets state 0 through the pinned setter 0x00498AB2 and
// restarts the timer (+0x30 false, +0x34 zero, +0x3C the current frame).
// ?rva0049920B@GateOpenAndCloseBehavior@@UAEXXZ, retail 0x0049920B, 64
// bytes: slot 8; the same when slot 6 holds, with state 2.
// ?rva00498806@GateOpenAndCloseBehavior@@UAEXXZ, retail 0x00498806, 23
// bytes: slot 9; slot 8 when slot 6 holds, else slot 7.

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
	virtual void rva004991CB() = 0;
	virtual void rva0049920B() = 0;
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
struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface { virtual void f10(); };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	virtual bool rva00498BAF(Object *object);
	virtual void rva004991CB();
	virtual void rva0049920B();
	virtual void rva00498806();
private:
	void rva00498FAA();
	void rva00498AB2(int state);
	int m_24;
	int m_28; // +0x28
	int m_2C; // +0x2C
	bool m_30; // +0x30
	float m_34; // +0x34
	float m_38;
	unsigned int m_3C; // +0x3C
};

// ?rva00498BAF@GateOpenAndCloseBehavior@@UAE_NPAVObject@@@Z @0x00498BAF
bool GateOpenAndCloseBehavior::rva00498BAF(Object *object)
{
	if (m_2C != 1)
		return false;
	return (bool)Rva00498B8BGet(object);
}

// ?rva004991CB@GateOpenAndCloseBehavior@@UAEXXZ @0x004991CB
void GateOpenAndCloseBehavior::rva004991CB()
{
	if (slot10() && !slot6())
	{
		rva00498FAA();
		rva00498AB2(0);
		m_30 = false;
		m_34 = 0.0f;
		m_3C = TheGameLogic->getFrame();
	}
}

// ?rva0049920B@GateOpenAndCloseBehavior@@UAEXXZ @0x0049920B
void GateOpenAndCloseBehavior::rva0049920B()
{
	if (slot10() && slot6())
	{
		rva00498FAA();
		rva00498AB2(2);
		m_30 = false;
		m_34 = 0.0f;
		m_3C = TheGameLogic->getFrame();
	}
}

// ?rva00498806@GateOpenAndCloseBehavior@@UAEXXZ @0x00498806
void GateOpenAndCloseBehavior::rva00498806()
{
	if (slot6())
		rva0049920B();
	else
		rva004991CB();
}
