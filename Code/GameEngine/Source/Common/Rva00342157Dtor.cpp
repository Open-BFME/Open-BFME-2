// cl: /DNDEBUG /MD /EHsc
//
// ??1AIHuntState@@UAE@XZ, retail 0x00342157, 91 bytes.
// Twin of 0x0033FC42 (vtable 0x00811DB0): dtor restoring vtable 0x008118B0,
// calling member +0x20 slot 0x3C when present then deleting it via slot-0
// scalarDeletingDestructor(0) plus operator delete with null->0 ternary
// then nulling it inside the if, then calling the base State destructor (the
// rowed ??1State@@UAE@XZ, the 7-byte fold body at 0x0049B47C).
// Caller is the deleting dtor 0x00342F95. The class derives from the canonical
// State (Include/Common/StateMachine.h, 0x20 bytes) plus the pointer at
// +0x20; its retail table is the one the State-derived constructor
// 0x0033F772 installs. Uses the inside-if shape that gives pop-before-or.

#include <new>

class StateMachine;

#include "../../Include/Common/StateMachine.h"

class Rva00342157Member
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void method3C();
};

class AIHuntState : public State
{
public:
	virtual ~AIHuntState();

private:
	Rva00342157Member *m_ptr20;
};

AIHuntState::~AIHuntState()
{
	if (m_ptr20 != 0) {
		m_ptr20->method3C();
		::operator delete(m_ptr20 != 0 ? m_ptr20->scalarDeletingDestructor(0) : 0);
		m_ptr20 = 0;
	}
}
