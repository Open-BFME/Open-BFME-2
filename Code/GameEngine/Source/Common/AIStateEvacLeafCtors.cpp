// cl: /O1 /DNDEBUG /MD /EHsc
//
// AIInternalMoveToState-derived state leaf ctors, retail 0x00342C47 (28B)
// and 0x00342D19 (34B), both over the 0x00342BAE mid pin.
//
// 0x00342C47 forwards (machine, flag) with no new members; 0x00342D19
// passes a false flag and zeroes ints at +0x68/+0x6C after its own
// vtable in the normal order. Hierarchy and base views mirror the
// family-1 TU (AIStateMoveTightenCtors.cpp); the mid ctor itself stays
// undefined here (its body is still byte-open in AIStateEvacCtors.cpp)
// so this TU defines only the two rowed leaves.

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
protected:
	float m_4c;
	float m_50;
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

Rva00342C47::Rva00342C47(StateMachine *machine, bool flag)
	: Rva00342BAE(machine, flag)
{
}

Rva00342D19::Rva00342D19(StateMachine *machine)
	: Rva00342BAE(machine, false), m_68(0), m_6c(0)
{
}
