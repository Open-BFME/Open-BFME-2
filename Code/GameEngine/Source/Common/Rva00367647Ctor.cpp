// cl: /MD
// ??0Rva00367647@@QAE@PAVStateMachine@@_N@Z @0x00367647 40B
// State-derived ctor hash 0xA3ED2B68 vtable 0x00817478 plus int 0 at +0x20
// plus bool at +0x24. Evidence: callers 0x00367CA4 0x00367CD8; rowed State
// base 0x004D73FC via I twin; precedent StateDerivedCtors_muse-a7a4.cpp.
class StateMachine;
#include "../../Include/Common/StateMachine.h"
// Rva00367647_vftable: retail table 0x00C17478 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva0036766FGet@@YAHXZ")();
void __identifier("?xfer@Rva00367647@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@GiantBirdFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@GiantBirdFollowWaypointPathState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@GiantBirdFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?_bfme_state_slot7@State@@EAEXXZ")();
void __identifier("?isAttack@State@@UBE_NXZ")();
void __identifier("?_bfme_state_slot9@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot10@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot11@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot12@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot13@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot14@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot15@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot16@State@@EAEXXZ")();
extern const void *const Rva00367647_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva0036766FGet@@YAHXZ"), //  2 0x0036766F
	(const void *)&__identifier("?xfer@Rva00367647@@MAEXPAVXfer@@@Z"), //  3 0x00367675
	(const void *)&__identifier("?onEnter@GiantBirdFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ"), //  4 0x00368798
	(const void *)&__identifier("?onExit@GiantBirdFollowWaypointPathState@@UAEXW4StateExitType@@@Z"), //  5 0x00369590
	(const void *)&__identifier("?update@GiantBirdFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ"), //  6 0x003694B2
	(const void *)&__identifier("?_bfme_state_slot7@State@@EAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?isAttack@State@@UBE_NXZ"), //  8 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot9@State@@EBE_NXZ"), //  9 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot10@State@@EBE_NXZ"), // 10 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot11@State@@EBE_NXZ"), // 11 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot12@State@@EBE_NXZ"), // 12 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot13@State@@EBE_NXZ"), // 13 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot14@State@@EBE_NXZ"), // 14 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot15@State@@EBE_NXZ"), // 15 0x0047A699
	(const void *)&__identifier("?_bfme_state_slot16@State@@EAEXXZ")  // 16 0x000B3FD0
};
}
class __declspec(novtable) Rva00367647 : public State
{
public:
	Rva00367647(StateMachine *machine, bool flag);
	virtual ~Rva00367647();
private:
	int m_20;
	bool m_24;
};
Rva00367647::Rva00367647(StateMachine *machine, bool flag) : State(machine, 0xA3ED2B68u)
{
	m_20 = 0;
	m_24 = flag;
	*reinterpret_cast<const void *const **>(this) = Rva00367647_vftable;
}
