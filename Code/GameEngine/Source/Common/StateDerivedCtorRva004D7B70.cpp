// cl: /MD
// ??0Rva004D7B70@@QAE@PAVStateMachine@@I@Z at retail 0x004D7B70 (28B).
// State-derived ctor forwarding (machine, hash) to ??0State@@QAE@PAVStateMachine@@I@Z
// 0x004D73FC then installing vtable 0x00860790. Same esi-homing recipe as
// StateDerivedCtors_muse-a7a4.cpp six (29B) but passing its own second
// argument through (ret 8) instead of a hash immediate. The State ctor's
// second parameter is a destructor-less 4-byte value (StateCtor.cpp), so the
// pass-through is spelled `unsigned int` too. Callers in BoxEmissionVolumeInfo dtors.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva004D7B70_vftable: retail table 0x00C60790 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
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
extern const void *const Rva004D7B70_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&_purecall, //  2 0x0003B810
	(const void *)&_purecall, //  3 0x0003B810
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  4 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&_purecall, //  6 0x0003B810
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

class __declspec(novtable) Rva004D7B70 : public State
{
public:
	Rva004D7B70(StateMachine *machine, unsigned int hash);
	virtual ~Rva004D7B70();
};

Rva004D7B70::Rva004D7B70(StateMachine *machine, unsigned int hash) : State(machine, hash)
{
	*reinterpret_cast<const void *const **>(this) = Rva004D7B70_vftable;
}
