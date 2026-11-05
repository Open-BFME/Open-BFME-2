// cl: /DNDEBUG /MD
//
// ?onExit@AICowerState@@UAEXW4StateExitType@@@Z, retail 0x003402FC, 70 bytes.
// Slot 5 (0x14) of vtable 0x00811958 (class Rva0033F7C8): AICowerState::onExit
// that runs base State::onExit (shared empty 0x0047A69C, pinned), clears the
// machine owner's index-4 state via rowed Object 0x0028EC88, then the owner's
// contain (+0x250) slot 31 (+0x7c) target's slot 104 (+0x1a0) with 0.
// Evidence: named lane pin AICowerState::onExit, vslot slot 5, donor BFME1
// Rva001745B0AICowerState_onExit (identity only, BFME2 body differs), caller
// 0x00347F3E AIUncontrollableCower::onExit, prev/next AI state TUs.
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class StateMachine;
class Object;
class ContainInterface : public VSlots<31>
{
public:
	virtual void *slot31() = 0;
};
class Slot104Target : public VSlots<104>
{
public:
	virtual void slot104(int arg) = 0;
};

#include "../../../Include/Common/StateMachineClass.h"


class Object
{
public:
	void rva0028EC88(int index);
	ContainInterface *getContain() const { return m_contain; }
private:
	unsigned char m_pad00[0x250];
	ContainInterface *m_contain; // +0x250
};

class AICowerState : public State
{
public:
	virtual void onExit(StateExitType status);
};

void AICowerState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *owner = getMachine()->getOwner();
	if (owner == 0)
		return;
	owner->rva0028EC88(4);
	ContainInterface *contain = owner->getContain();
	void *target = contain != 0 ? contain->slot31() : (void *)0;
	if (target == 0)
		return;
	((Slot104Target *)target)->slot104(0);
}
