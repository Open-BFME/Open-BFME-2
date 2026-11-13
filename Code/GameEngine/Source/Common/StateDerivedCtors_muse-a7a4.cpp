// cl: /MD
// Six 29B State-derived ctors calling ??0State@@QAE@PAVStateMachine@@I@Z
// (0x004D73FC, ICF twin of the rowed VAsciiString overload) then installing
// their own vtable. Retail pushes a 4-byte hash (not a string address) with
// no AsciiString construction, hence the unsigned second arg. Vtables and
// hashes from retail bytes; callers are 0x004A7010 fragments.
// 0x004A6933 hash 0xAE77593F vtable 0x00852D70
// 0x004A6BCA hash 0x89496474 vtable 0x00853218
// 0x004A6C13 hash 0x5E8FE5DB vtable 0x00853260
// 0x004A6956 hash 0xC40022B2 vtable 0x00852DE0
// 0x004A6979 hash 0xCAD6313C vtable 0x00852E38
// 0x004A699C hash 0xE6B21889 vtable 0x00852E90

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva004A6933_vftable: retail table 0x00C52D70 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva004A6950Get@@YAHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
void __identifier("?update@SupplyTruckWantsToPickUpOrDeliverBoxesState@@UAE?AW4StateReturnType@@XZ")();
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
extern const void *const Rva004A6933_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva004A6950Get@@YAHXZ"), //  2 0x004A6950
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  4 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?update@SupplyTruckWantsToPickUpOrDeliverBoxesState@@UAE?AW4StateReturnType@@XZ"), //  6 0x004A7275
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
// Rva004A6BCA_vftable: retail table 0x00C53218 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?rva004A6BE7@Rva004A6BE7@@QAEHXZ")();
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
extern const void *const Rva004A6BCA_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  2 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?rva004A6BE7@Rva004A6BE7@@QAEHXZ"), //  4 0x004A6BE7
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  6 0x000D43D0
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
// Rva004A6C13_vftable: retail table 0x00C53260 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?rva004A6C30@Rva004885B8@@QAEHXZ")();
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
extern const void *const Rva004A6C13_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  2 0x000D43D0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?rva004A6C30@Rva004885B8@@QAEHXZ"), //  4 0x004A6C30
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  6 0x000D43D0
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
// Rva004A6956_vftable: retail table 0x00C52DE0 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva004A6973Get@@YAHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?onEnter@Rva004A6956@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
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
extern const void *const Rva004A6956_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva004A6973Get@@YAHXZ"), //  2 0x004A6973
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?onEnter@Rva004A6956@@UAE?AW4StateReturnType@@XZ"), //  4 0x004A732B
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  6 0x000D43D0
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
// Rva004A6979_vftable: retail table 0x00C52E38 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva004A6996Get@@YAHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?onEnter@Rva004A6979@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
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
extern const void *const Rva004A6979_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva004A6996Get@@YAHXZ"), //  2 0x004A6996
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?onEnter@Rva004A6979@@UAE?AW4StateReturnType@@XZ"), //  4 0x004A6C6A
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  6 0x000D43D0
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
// Rva004A699C_vftable: retail table 0x00C52E90 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva004A69B9Get@@YAHXZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?onEnter@Rva004A6979@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ")();
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
extern const void *const Rva004A699C_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva004A69B9Get@@YAHXZ"), //  2 0x004A69B9
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  3 0x0047A69C
	(const void *)&__identifier("?onEnter@Rva004A6979@@UAE?AW4StateReturnType@@XZ"), //  4 0x004A6C6A
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?rva000D43D0@Rva00347E4CState@@QAEHXZ"), //  6 0x000D43D0
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

class __declspec(novtable) Rva004A6933 : public State
{
public:
	Rva004A6933(StateMachine *machine);
	virtual ~Rva004A6933();
};

class __declspec(novtable) Rva004A6BCA : public State
{
public:
	Rva004A6BCA(StateMachine *machine);
	virtual ~Rva004A6BCA();
};

class __declspec(novtable) Rva004A6C13 : public State
{
public:
	Rva004A6C13(StateMachine *machine);
	virtual ~Rva004A6C13();
};

#include "../../Include/GameLogic/Module/Rva004A6956.h"

class __declspec(novtable) Rva004A6979 : public State
{
public:
	Rva004A6979(StateMachine *machine);
	virtual ~Rva004A6979();
};

class __declspec(novtable) Rva004A699C : public State
{
public:
	Rva004A699C(StateMachine *machine);
	virtual ~Rva004A699C();
};

Rva004A6933::Rva004A6933(StateMachine *machine) : State(machine, 0xAE77593Fu)
{
	*reinterpret_cast<const void *const **>(this) = Rva004A6933_vftable;
}

Rva004A6BCA::Rva004A6BCA(StateMachine *machine) : State(machine, 0x89496474u)
{
	*reinterpret_cast<const void *const **>(this) = Rva004A6BCA_vftable;
}

Rva004A6C13::Rva004A6C13(StateMachine *machine) : State(machine, 0x5E8FE5DBu)
{
	*reinterpret_cast<const void *const **>(this) = Rva004A6C13_vftable;
}

Rva004A6956::Rva004A6956(StateMachine *machine) : State(machine, 0xC40022B2u)
{
	*reinterpret_cast<const void *const **>(this) = Rva004A6956_vftable;
}

Rva004A6979::Rva004A6979(StateMachine *machine) : State(machine, 0xCAD6313Cu)
{
	*reinterpret_cast<const void *const **>(this) = Rva004A6979_vftable;
}

Rva004A699C::Rva004A699C(StateMachine *machine) : State(machine, 0xE6B21889u)
{
	*reinterpret_cast<const void *const **>(this) = Rva004A699C_vftable;
}
