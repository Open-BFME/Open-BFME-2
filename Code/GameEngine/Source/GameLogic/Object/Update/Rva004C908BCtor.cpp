// cl: /MD /DNDEBUG
// ??0SwayClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x004C908B
// (79B). Dedicated TU.
//
// Identity: the vftable this ctor installs (0x00C5EA8C) carries the
// "SwayClientUpdate" pool key 0x004C90E0 (slot 4), the rowed
// SwayClientUpdate::loadPostProcess 0x004C9593 (slot 1) and
// SwayClientUpdate::clientUpdate 0x004C923B (slot 12), and the
// SwayClientUpdate factory stub (0x0025298F, a 0x2C new) is its caller. The
// member stores are Zero Hour's SwayClientUpdate ctor initializers plus the
// two BFME floats at +0x24/+0x28. It was named by address (Rva004C908B)
// after the 2026-09-20 re-home took the LaserUpdate name away from it.

class Thing;
class ModuleData;

// Rva004C908B_vftable: retail table 0x00C5EA8C (15 ClientUpdate slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva00362EE3@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@SwayClientUpdate@@MAEXXZ")();
void __identifier("?Rva004C90DAGet@@YAHXZ")();
void __identifier("?xfer@SwayClientUpdate@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@SwayClientUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?loadPostProcess@DrawModule@@MAEXXZ")();
void __identifier("?vslot51@DrawModule@@UAEPAXXZ")();
void __identifier("?vslot12@BodyModule@@UAE_NXZ")();
void __identifier("?clientUpdate@SwayClientUpdate@@UAEXXZ")();
extern const void *const Rva004C908B_vftable[15] = {
	(const void *)&__identifier("??_GRva00362EE3@@UAEPAXI@Z"), //  0 0x003630E6
	(const void *)&__identifier("?loadPostProcess@SwayClientUpdate@@MAEXXZ"), //  1 0x004C9593
	(const void *)&__identifier("?Rva004C90DAGet@@YAHXZ"), //  2 0x004C90DA
	(const void *)&__identifier("?xfer@SwayClientUpdate@@MAEXPAVXfer@@@Z"), //  3 0x004C9505
	(const void *)&__identifier("?getModuleNameKey@SwayClientUpdate@@UBE?AW4NameKeyType@@XZ"), //  4 0x004C90E0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  5 0x000B3FD0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  6 0x000B3FD0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  8 0x000B3FD0
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ"), //  9 0x000D43D0
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ"), // 10 0x000D43D0
	(const void *)&__identifier("?vslot12@BodyModule@@UAE_NXZ"), // 11 0x0050B5C6
	(const void *)&__identifier("?clientUpdate@SwayClientUpdate@@UAEXXZ"), // 12 0x004C923B
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ"), // 13 0x000D43D0
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ")  // 14 0x000D43D0
};
}

// Opaque intermediate; ctor resolves to the opaque row at 0x00362EC7.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00362EC7();

protected:
	unsigned char m_pad0[8];
	float m_f0C;
	float m_f10;
	float m_f14;
	float m_f18;
	float m_f1C;
	short m_w20;
	unsigned char m_b22;
	unsigned char m_b23;
	float m_f24;
	float m_f28;
};

class __declspec(novtable) SwayClientUpdate : public Rva00362EC7
{
public:
	SwayClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SwayClientUpdate();

};

SwayClientUpdate::SwayClientUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	m_w20 = -1;
	*reinterpret_cast<const void *const **>(this) = Rva004C908B_vftable;
	m_f0C = 0.0f;
	m_f10 = 0.0f;
	m_f14 = 0.0f;
	m_f18 = 0.0f;
	m_f1C = 0.0f;
	m_b22 = 1;
	m_b23 = 0;
	m_f24 = 0.0f;
	m_f28 = 0.0f;
}
