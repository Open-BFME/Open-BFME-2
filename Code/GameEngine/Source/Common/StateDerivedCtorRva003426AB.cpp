// cl: /MD
//
// ??0Rva003426AB@@QAE@PAVStateMachine@@@Z, retail 0x003426AB, 29 bytes.
// State-derived ctor (machine) forwarding hash 0x9AA7C3F8 to the
// (StateMachine*, unsigned int) ICF twin at 0x004D73FC (pinned
// ??0State@@QAE@PAVStateMachine@@I@Z, same body as the rowed VAsciiString
// overload), then installing vtable 0x00812438. Same family as the landed
// 0x00342619 (hash 0x9B3AE6B6, vtable 0x008123D8) and the
// StateDerivedCtors_muse-a7a4 six (same 29B esi-homing shape, ret 4, hash
// immediate, novtable plus explicit vftable store). Sole caller is unclaimed
// site 0x00352AC8.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva003426AB_vftable: retail table 0x00C12438 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva003426C8Get@@YAHXZ")();
void __identifier("?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z")();
void __identifier("?rva003426CE@Rva003426AB@@UAEHXZ")();
void __identifier("?rva0034270C@Rva003426AB@@UAEXH@Z")();
void __identifier("?update@AIRotateFiringarc@@UAE?AW4StateReturnType@@XZ")();
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
extern const void *const Rva003426AB_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003426C8Get@@YAHXZ"), //  2 0x003426C8
	(const void *)&__identifier("?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z"), //  3 0x00306A9B
	(const void *)&__identifier("?rva003426CE@Rva003426AB@@UAEHXZ"), //  4 0x003426CE
	(const void *)&__identifier("?rva0034270C@Rva003426AB@@UAEXH@Z"), //  5 0x0034270C
	(const void *)&__identifier("?update@AIRotateFiringarc@@UAE?AW4StateReturnType@@XZ"), //  6 0x0034274A
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

class __declspec(novtable) Rva003426AB : public State
{
public:
	Rva003426AB(StateMachine *machine);
	virtual ~Rva003426AB();
};

Rva003426AB::Rva003426AB(StateMachine *machine) : State(machine, 0x9AA7C3F8u)
{
	*reinterpret_cast<const void *const **>(this) = Rva003426AB_vftable;
}
