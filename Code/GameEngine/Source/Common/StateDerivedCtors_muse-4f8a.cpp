// cl: /MD
// ??0Rva0048896B@@QAE@PAVStateMachine@@@Z @0x0048896B 29B
// State-derived ctor calling ??0State@@QAE@PAVStateMachine@@I@Z (0x004D73FC,
// ICF twin pin of the rowed VAsciiString overload) then installing its own
// vtable. Retail pushes hash 0x69EAAB49 with no AsciiString construction,
// same 29B esi-homing shape as the six in StateDerivedCtors_muse-a7a4.cpp.
// Vtable 0x0084B620 from retail bytes; sole caller 0x00488EB5 in FUN_00888DAB.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva0048896B_vftable: retail table 0x00C4B620 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?update@AIGoingIdleState@@QAEHXZ")();
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
extern const void *const Rva0048896B_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  2 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  4 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?update@AIGoingIdleState@@QAEHXZ"), //  6 0x00488988
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

class __declspec(novtable) Rva0048896B : public State
{
public:
	Rva0048896B(StateMachine *machine);
	virtual ~Rva0048896B();
};

Rva0048896B::Rva0048896B(StateMachine *machine) : State(machine, 0x69EAAB49u)
{
	*reinterpret_cast<const void *const **>(this) = Rva0048896B_vftable;
}
