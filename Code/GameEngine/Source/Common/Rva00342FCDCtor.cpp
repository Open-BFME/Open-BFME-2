// cl: /MD
//
// ??0Rva00342FCD@@QAE@PAVStateMachine@@H@Z, retail 0x00342FCD, 37 bytes.
// Chain from 0x0033FE65 (Rva0033FE65 ctor). Derived ctor forwarding
// (machine, 0) to base Rva0033FE65 then storing arg2 at +0x28 then
// installing vtable 0x00812FA0 then zeroing byte at +0x2C. Callers
// 0x003527F3/0x00352823/0x00352855. Layout is base 0x28 plus int plus bool.
// Uses novtable plus explicit store to get store-before-vtable order like
// the State hash ctors.

class StateMachine;

class Rva0033FE65
{
public:
	Rva0033FE65(StateMachine *machine, int val);
	virtual ~Rva0033FE65();

private:
	char m_pad04[0x28 - 0x04];
};

// Rva00342FCD_vftable: retail table 0x00C12FA0 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva00342FF2Get@@YAHXZ")();
void __identifier("?xfer@AIFaceState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@Rva00342FCD@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@AIFaceState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@AIFaceState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?_bfme_state_slot7@State@@EAEXXZ")();
void __identifier("?get@Rva0057B94DCmpBoolField@@QBE_NXZ")();
void __identifier("?_bfme_state_slot9@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot10@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot11@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot12@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot13@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot14@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot15@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot16@State@@EAEXXZ")();
extern const void *const Rva00342FCD_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva00342FF2Get@@YAHXZ"), //  2 0x00342FF2
	(const void *)&__identifier("?xfer@AIFaceState@@MAEXPAVXfer@@@Z"), //  3 0x0034236F
	(const void *)&__identifier("?onEnter@Rva00342FCD@@UAE?AW4StateReturnType@@XZ"), //  4 0x0034BCBD
	(const void *)&__identifier("?onExit@AIFaceState@@UAEXW4StateExitType@@@Z"), //  5 0x003423A6
	(const void *)&__identifier("?update@AIFaceState@@UAE?AW4StateReturnType@@XZ"), //  6 0x0035487E
	(const void *)&__identifier("?_bfme_state_slot7@State@@EAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?get@Rva0057B94DCmpBoolField@@QBE_NXZ"), //  8 0x0057B94D
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

class __declspec(novtable) Rva00342FCD : public Rva0033FE65
{
public:
	Rva00342FCD(StateMachine *machine, int val);

private:
	int m_28;
	bool m_2C;
};

Rva00342FCD::Rva00342FCD(StateMachine *machine, int val) : Rva0033FE65(machine, 0)
{
	m_28 = val;
	*reinterpret_cast<const void *const **>(this) = Rva00342FCD_vftable;
	m_2C = false;
}
