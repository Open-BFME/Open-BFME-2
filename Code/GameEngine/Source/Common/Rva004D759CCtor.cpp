// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??0StateMachine@@QAE@PAVObject@@I_N@Z, retail 0x004D79E1, 120 bytes.
// StateMachine base ctor (vtable 0x00C60740, 16 slots; the dtor
// ??1StateMachine 0x004D759C and ??_GStateMachine 0x004D7A59 own it).
// Stores vtable, nulls currentState at +0x04, constructs map<int,void*> at +0x08
// (rowed 0x0033C432), then owner at +0x14, goalObjectID 0 at +0x20,
// defaultStateID 999999 at +0x1C, goalPosition 0.0f at +0x24/0x28/0x2C,
// FLT_MAX range at +0x30, unk34 0 at +0x34, locked/inited false at +0x38/0x39,
// extra flag at +0x3A. SleepTill at +0x18 left uninitialized (retail hole).
// Signature (target evidence): ret 0xC (three dword arguments); the second
// is never read and never destroyed (no AsciiString destructor call, while
// BFME 2's AsciiString is a refcounted handle), and the 24 retail callers
// push it as one dword (forwarded [ebp+0x10] or an immediate key such as
// 0x3EA7DE5F in DozerPrimaryStateMachine 0x00488DAB). So it is a 32-bit
// scalar name key, not ZH's AsciiString name; unsigned int as in the 18
// existing callers' spelling (inference: the exact key typedef is unknown).
// Evidence: same vtable as the rowed dtor 0x004D759C, 24 callers in
// 0x00343xxx (base-then-derived-vtable pattern), xfer 0x004D7744 and
// StateMachineGoal layout (+0x18 sleepTill +0x1C default +0x20 goal +0x24
// position +0x30 range). BFME1 donor StateMachine::StateMachine(Object*,
// AsciiString) minus debug name plus BFME2 range/unk34/extra members.
// Snapshot base gives the EH prolog (unwind calls ??1Snapshot, state 0
// before map). The virtual surface is StateMachineDtor.cpp's (canonical
// Snapshot plus the dtor and crc/xfer/loadPostProcess overrides) so both
// units emit the same ??_7StateMachine/??_GStateMachine. Volatile members
// force the retail store order (goal/default before floats); without it
// MSVC hoists the movss stores early. No fallback paths.
#include <map>
#include <cfloat>
#include "Common/Snapshot.h"

class Object;

class Xfer;

class StateMachine : public Snapshot
{
public:
	StateMachine(Object *owner, unsigned int name, bool flag);
	virtual ~StateMachine();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

public:
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

StateMachine::StateMachine(Object *owner, unsigned int name, bool flag)
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
