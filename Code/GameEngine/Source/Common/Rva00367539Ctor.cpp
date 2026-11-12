// cl: /MD
// ??0GiantBirdNormalFlightState@@QAE@PAVStateMachine@@_N1@Z @0x00367539 43B
// (was Rva00367539: vtable 0x00C17300's slots 4-6 are the rowed
// GiantBirdNormalFlightState onEnter/onExit/update bodies)
// State-derived ctor hash 0x815D9F7C vtable 0x00817300 plus bool at +0x20
// plus bool at +0x21. Evidence: callers 8 unclaimed sites; rowed State
// base 0x004D73FC via I twin ??0State@@QAE@PAVStateMachine@@I@Z; precedent
// Rva00367647Ctor.cpp (State hash plus bool) and AIGuardState hash-plus-vtable.
class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva00367539_vftable: retail table 0x00C17300 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva00367564Get@@YAHXZ")();
void __identifier("?xfer@Rva0055CA8A@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@GiantBirdNormalFlightState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@GiantBirdNormalFlightState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@GiantBirdNormalFlightState@@UAE?AW4StateReturnType@@XZ")();
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
extern const void *const Rva00367539_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva00367564Get@@YAHXZ"), //  2 0x00367564
	(const void *)&__identifier("?xfer@Rva0055CA8A@@MAEXPAVXfer@@@Z"), //  3 0x0055CA8A
	(const void *)&__identifier("?onEnter@GiantBirdNormalFlightState@@UAE?AW4StateReturnType@@XZ"), //  4 0x00369064
	(const void *)&__identifier("?onExit@GiantBirdNormalFlightState@@UAEXW4StateExitType@@@Z"), //  5 0x00369217
	(const void *)&__identifier("?update@GiantBirdNormalFlightState@@UAE?AW4StateReturnType@@XZ"), //  6 0x0036914D
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

class __declspec(novtable) GiantBirdNormalFlightState : public State
{
public:
	GiantBirdNormalFlightState(StateMachine *machine, bool b1, bool b2);
private:
	bool m_20;
	bool m_21;
};

GiantBirdNormalFlightState::GiantBirdNormalFlightState(StateMachine *machine, bool b1, bool b2) : State(machine, 0x815D9F7Cu)
{
	m_20 = b1;
	m_21 = b2;
	*reinterpret_cast<const void *const **>(this) = Rva00367539_vftable;
}
