// cl: /MD
// ??0Rva003678F7@@QAE@PAVStateMachine@@@Z @0x003678F7 29B
// State-derived ctor hash 0xA36413A3 vtable 0x008175A8. Evidence: caller
// 0x00367DDF unclaimed; rowed State base 0x004D73FC via I twin
// ??0State@@QAE@PAVStateMachine@@I@Z; precedent AIGuardState hash-plus-vtable.
class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva003678F7_vftable: retail table 0x00C175A8 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?name@Rva00367929Named@@QBEPBDXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?onEnter@GiantBirdDieState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?slot10@GroupOrder@@UAEHXZ")();
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
extern const void *const Rva003678F7_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?name@Rva00367929Named@@QBEPBDXZ"), //  2 0x00367929
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?onEnter@GiantBirdDieState@@UAE?AW4StateReturnType@@XZ"), //  4 0x00367914
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?slot10@GroupOrder@@UAEHXZ"), //  6 0x0036CC7A
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

class __declspec(novtable) Rva003678F7 : public State
{
public:
	Rva003678F7(StateMachine *machine);
};

Rva003678F7::Rva003678F7(StateMachine *machine) : State(machine, 0xA36413A3u)
{
	*reinterpret_cast<const void *const **>(this) = Rva003678F7_vftable;
}
