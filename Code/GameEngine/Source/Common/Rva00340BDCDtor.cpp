// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva00340BDC@@UAE@XZ, retail 0x00340BDC, 75 bytes.
// Derived dtor restoring vtable 0x00812150, deleting the +0x4c pointer via
// slot-0 scalarDeletingDestructor(0) plus operator delete inside an explicit
// if (vf0(0)+free with je-to-or skip, no xor path) then nulling it
// (state 0, pop-before-or), then calling the rowed base ??1Rva0033FF2B at
// 0x0033FF2B. Caller is 0x00342B6E. Sibling of landed 0x00340D1F.

#include <new>

class Rva00340BDCMember
{
public:
    virtual void *scalarDeletingDestructor(unsigned int flags);
};

class Xfer;

#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"

class AIInternalMoveToState : public State
{
public:
    virtual void xfer(Xfer *xfer);
    virtual StateReturnType onEnter();
    virtual void onExit(StateExitType status);
    virtual StateReturnType update();
};

class Rva0033FF2B : public AIInternalMoveToState
{
public:
    virtual ~Rva0033FF2B();

private:
    char m_pad20[0x40 - 0x20];
    unsigned int m_handle40;
};

class Rva00340BDC : public Rva0033FF2B
{
public:
    virtual ~Rva00340BDC();

private:
    char m_pad44[0x4C - 0x44];
    Rva00340BDCMember *m_ptr4C;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00340BDC::~Rva00340BDC()
{
    if (m_ptr4C != 0) {
        ::operator delete(m_ptr4C->scalarDeletingDestructor(0));
        m_ptr4C = 0;
    }
}

// ?bfmeAnchorRva00340BDCDtor absent-from-retail
void bfmeAnchorRva00340BDCDtor(Rva00340BDC *state)
{
	state->Rva00340BDC::~Rva00340BDC();
}
