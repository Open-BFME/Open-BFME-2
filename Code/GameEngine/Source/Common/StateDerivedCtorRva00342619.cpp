// cl: /MD
//
// ??0Rva00342619@@QAE@PAVStateMachine@@@Z, retail 0x00342619, 29 bytes.
// State-derived ctor (machine) forwarding hash 0x9B3AE6B6 to the
// (StateMachine*, unsigned int) ICF twin at 0x004D73FC (pinned
// ??0State@@QAE@PAVStateMachine@@I@Z, same body as the rowed VAsciiString
// overload), then installing vtable 0x008123D8. Seventh member of the
// StateDerivedCtors_muse-a7a4 six-ctor family (same 29B esi-homing shape,
// ret 4, hash immediate, novtable plus explicit vftable store). Sole caller
// is unclaimed site 0x00352A67.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva00342619_vftable: retail table 0x00C123D8 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva00342636Get@@YAHXZ")();
void __identifier("?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z")();
void __identifier("?onEnter@AIPrepareForBoarding@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?update@AIPrepareForBoarding@@UAE?AW4StateReturnType@@XZ")();
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
extern const void *const Rva00342619_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva00342636Get@@YAHXZ"), //  2 0x00342636
	(const void *)&__identifier("?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z"), //  3 0x00306A9B
	(const void *)&__identifier("?onEnter@AIPrepareForBoarding@@UAE?AW4StateReturnType@@XZ"), //  4 0x0034263C
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?update@AIPrepareForBoarding@@UAE?AW4StateReturnType@@XZ"), //  6 0x00354C6B
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

class __declspec(novtable) Rva00342619 : public State
{
public:
	Rva00342619(StateMachine *machine);
	virtual ~Rva00342619();
};

Rva00342619::Rva00342619(StateMachine *machine) : State(machine, 0x9B3AE6B6u)
{
	*reinterpret_cast<const void *const **>(this) = Rva00342619_vftable;
}
