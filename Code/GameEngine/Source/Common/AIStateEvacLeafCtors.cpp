// cl: /DNDEBUG /MD /EHsc
//
// AIInternalMoveToState-derived state leaf ctors, retail 0x00342C47 (28B)
// and 0x00342D19 (34B), both over the 0x00342BAE mid pin.
//
// 0x00342C47 forwards (machine, flag) with no new members; 0x00342D19
// passes a false flag and zeroes ints at +0x68/+0x6C after its own
// vtable in the normal order. Hierarchy and base views mirror the
// family-1 TU (AIStateMoveTightenCtors.cpp). The two mid ctors
// 0x00342BAE and 0x00342BFC are defined at the end of this file.

class StateMachine;
#include "../../../Libraries/Include/Lib/Coord3D.h"
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination;
};
class Rva00342BAE : public AIInternalMoveToState
{
public:
	Rva00342BAE(StateMachine *machine, bool flag);
	Rva00342BAE(StateMachine *machine, bool flag, bool flag2);
protected:
	struct Offset2D
	{
		float x, y;
		void zero()
		{
			x = 0.0f;
			y = 0.0f;
		}
	};
	Offset2D m_4c;
	float m_54;
	int m_58;
	int m_5c;
	int m_60;
	bool m_64;
	bool m_65;
	bool m_66;
};
class Rva00342C47 : public Rva00342BAE
{
public:
	Rva00342C47(StateMachine *machine, bool flag);
};
class Rva00342D19 : public Rva00342BAE
{
public:
	Rva00342D19(StateMachine *machine);
private:
	int m_68;
	int m_6c;
};
class Rva00342C97 : public Rva00342BAE
{
public:
	Rva00342C97(StateMachine *machine);
private:
	int m_68;
	int m_6c;
};

Rva00342C47::Rva00342C47(StateMachine *machine, bool flag)
	: Rva00342BAE(machine, flag)
{
}

Rva00342D19::Rva00342D19(StateMachine *machine)
	: Rva00342BAE(machine, false), m_68(0), m_6c(0)
{
}

// ??0Rva00342C97@@QAE@PAVStateMachine@@@Z @0x00342C97 34B evidence: gap between ConstIntGetters3 rows; same shape as Rva00342D19 false-flag plus-0x68 0x6c; base row 0x00342BAE; vtable 0x00812A70 store; caller 0x00352308
Rva00342C97::Rva00342C97(StateMachine *machine)
	: Rva00342BAE(machine, false), m_68(0), m_6c(0)
{
}

// ??0Rva00342BAE@@QAE@PAVStateMachine@@_N@Z @ 0x00342BAE (72B) and
// ??0Rva00342BAE@@QAE@PAVStateMachine@@_N1@Z @ 0x00342BFC (75B): the two
// constructors of the mid class, vtable 0x00C12930 (name getter
// "AIFollowWaypointPathState"), hash 0x6ce5ef54. The one-flag form sets +0x66,
// the two-flag form stores its second flag there. The +0x4C/+0x50 pair is
// cleared through an inline member call (Zero Hour's AIFollowWaypointPathState
// keeps a Coord2D m_groupOffset there): VC7.1 keeps those stores after the
// vtable store, where plain float assignments are scheduled ahead of it.
Rva00342BAE::Rva00342BAE(StateMachine *machine, bool flag)
	: AIInternalMoveToState(machine, 0x6ce5ef54u)
{
	m_4c.zero();
	m_58 = 0;
	m_5c = 0;
	m_60 = 0;
	m_64 = false;
	m_65 = flag;
	m_54 = 0.0f;
	m_66 = true;
}

Rva00342BAE::Rva00342BAE(StateMachine *machine, bool flag, bool flag2)
	: AIInternalMoveToState(machine, 0x6ce5ef54u)
{
	m_4c.zero();
	m_58 = 0;
	m_5c = 0;
	m_60 = 0;
	m_64 = false;
	m_65 = flag;
	m_66 = flag2;
	m_54 = 0.0f;
}
