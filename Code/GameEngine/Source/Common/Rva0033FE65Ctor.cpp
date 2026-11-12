// cl: /MD
//
// ??0Rva0033FE65@@QAE@PAVStateMachine@@H@Z, retail 0x0033FE65, 56 bytes.
// State-derived ctor forwarding (machine, 0x8821F22E) to the unsigned-hash
// twin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC then installing
// vtable 0x00811E08. Sets word at +0x20 via OR FFFF, byte at +0x24 to
// (val==0), word at +0x22 to 5, byte at +0x25 to 0. Callers pass 0 as val
// (0x00342FCD) plus machine pointers. Recipe is StateDerivedCtors_muse-a7a4
// hash-plus-vtable with the extra word/bool tail.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

// Rva0033FE65_vftable: retail table 0x00C11E08 (17 State slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GAIGuardInnerState@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@State@@MAEXXZ")();
void __identifier("?Rva0033FE9DGet@@YAHXZ")();
void __identifier("?xfer@AIIdleState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@Rva0033FE65@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?update@AIIdleState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?_bfme_state_slot7@State@@EAEXXZ")();
void __identifier("?vslot10@GameWindow@@UAE_NXZ")();
void __identifier("?_bfme_state_slot9@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot10@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot11@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot12@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot13@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot14@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot15@State@@EBE_NXZ")();
void __identifier("?_bfme_state_slot16@State@@EAEXXZ")();
extern const void *const Rva0033FE65_vftable[17] = {
	(const void *)&__identifier("??_GAIGuardInnerState@@UAEPAXI@Z"), //  0 0x004D8507
	(const void *)&__identifier("?loadPostProcess@State@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva0033FE9DGet@@YAHXZ"), //  2 0x0033FE9D
	(const void *)&__identifier("?xfer@AIIdleState@@MAEXPAVXfer@@@Z"), //  3 0x0033FEA3
	(const void *)&__identifier("?onEnter@Rva0033FE65@@UAE?AW4StateReturnType@@XZ"), //  4 0x00346FD0
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  5 0x0047A69C
	(const void *)&__identifier("?update@AIIdleState@@UAE?AW4StateReturnType@@XZ"), //  6 0x0035389E
	(const void *)&__identifier("?_bfme_state_slot7@State@@EAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?vslot10@GameWindow@@UAE_NXZ"), //  8 0x0050B5C6
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

class __declspec(novtable) Rva0033FE65 : public State
{
public:
	Rva0033FE65(StateMachine *machine, int val);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned short m_20;
	unsigned short m_22;
	bool m_24;
	bool m_25;
};

Rva0033FE65::Rva0033FE65(StateMachine *machine, int val) : State(machine, 0x8821F22Eu)
{
	m_20 |= 0xFFFF;
	*reinterpret_cast<const void *const **>(this) = Rva0033FE65_vftable;
	m_24 = (val == 0);
	m_22 = 5;
	m_25 = 0;
}
