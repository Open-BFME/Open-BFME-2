// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004D759C@@QAE@PAVObject@@VAsciiString@@_N@Z, retail 0x004D79E1, 120 bytes.
// Base ctor for the opaque StateMachine family (vtable 0x00C60740, 16 slots).
// Stores vtable, nulls currentState at +0x04, constructs map<int,void*> at +0x08
// (rowed 0x0033C432), then owner at +0x14, goalObjectID 0 at +0x20,
// defaultStateID 999999 at +0x1C, goalPosition 0.0f at +0x24/0x28/0x2C,
// FLT_MAX range at +0x30, unk34 0 at +0x34, locked/inited false at +0x38/0x39,
// extra flag at +0x3A. SleepTill at +0x18 left uninitialized (retail hole).
// Evidence: same vtable as pinned dtor 0x004D759C, 24 callers in 0x00343xxx
// (base-then-derived-vtable pattern), xfer 0x004D7744 and StateMachineGoal
// layout (+0x18 sleepTill +0x1C default +0x20 goal +0x24 position +0x30 range).
// BFME1 donor StateMachine::StateMachine(Object*, AsciiString) verbatim minus
// debug name (second arg ignored in release, hence middle stack slot untouched)
// plus BFME2 range/unk34/extra members. Snapshot base gives the EH prolog
// (unwind calls ??1Snapshot, state 0 before map). Volatile members force the
// retail store order (goal/default before floats); without it MSVC hoists the
// movss stores early. No fallback paths.
#include <map>
#include <cfloat>

class Object;

class AsciiString
{
public:
	void *m_data;
};

class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class Rva004D759C : public Snapshot
{
public:
	void crc(Xfer *xfer) {}
	void loadPostProcess() {}
	void xfer(Xfer *xfer) {}
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	Rva004D759C(Object *owner, AsciiString name, bool flag);
	virtual ~Rva004D759C();

	void *m_currentState; // +0x04
	_STL::map<int, void *> m_stateMap; // +0x08
	Object *volatile m_owner; // +0x14
	char m_pad18[4]; // +0x18 retail hole (sleepTill, uninitialized)
	volatile int m_defaultStateID; // +0x1C
	volatile int m_goalObjectID; // +0x20
	volatile float m_goalX; // +0x24
	volatile float m_goalY; // +0x28
	volatile float m_goalZ; // +0x2C
	volatile float m_goalRange; // +0x30
	volatile int m_unk34; // +0x34
	volatile bool m_locked; // +0x38
	volatile bool m_inited; // +0x39
	volatile bool m_extra; // +0x3A
};

Rva004D759C::Rva004D759C(Object *owner, AsciiString name, bool flag)
	: m_currentState(0), m_stateMap(), m_owner(owner)
{
	m_goalObjectID = 0;
	m_defaultStateID = 999999;
	m_goalX = 0.0f;
	m_goalY = 0.0f;
	m_goalZ = 0.0f;
	m_extra = flag;
	m_unk34 = 0;
	m_locked = false;
	m_inited = false;
	m_goalRange = FLT_MAX;
}
