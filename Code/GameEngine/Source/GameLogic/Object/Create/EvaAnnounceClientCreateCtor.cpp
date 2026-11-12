// cl: /DNDEBUG /MD
//
// ??0EvaAnnounceClientCreate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C99D4, 50 bytes.
// EvaAnnounceClientCreate behavior ctor over the rowed Rva00362EC7 base
// (0x362EC7, thing plus data): double-stores +0x0C (first volatile) around
// an and-zero at +0x10, the primary vtable slot and a trailing zero byte at
// +0x14 (address-of TU-local dummies, DIR32-masked). The rowed name getter
// at 0x4C9A0C proves the class; the rowed instance factory 0x252A50 is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7Rva004C9994@@6B@")[];
// Retail table 0x00C5ED50 (15 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva00362EE3@@UAEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva004C9A06Get@@YAHXZ")();
void __identifier("?xfer@EvaAnnounceClientCreate@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@EvaAnnounceClientCreate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?winNextTab@GameWindow@@QAEHXZ")();
void __identifier("?get@Rva000A7801CmpBoolField@@QBE_NXZ")();
void __identifier("?clientUpdate@EvaAnnounceClientCreate@@UAEXXZ")();
void __identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ")();
}
static const void *const s_vtable[15] = {
	(const void *)&__identifier("??_GRva00362EE3@@UAEPAXI@Z"), //  0 0x003630E6
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva004C9A06Get@@YAHXZ"), //  2 0x004C9A06
	(const void *)&__identifier("?xfer@EvaAnnounceClientCreate@@MAEXPAVXfer@@@Z"), //  3 0x004C9B44
	(const void *)&__identifier("?getModuleNameKey@EvaAnnounceClientCreate@@UBE?AW4NameKeyType@@XZ"), //  4 0x004C9A0C
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  5 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  6 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  7 0x000B3FD0
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  8 0x000B3FD0
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), //  9 0x000D43D0
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 10 0x000D43D0
	(const void *)&__identifier("?get@Rva000A7801CmpBoolField@@QBE_NXZ"), // 11 0x000A7801
	(const void *)&__identifier("?clientUpdate@EvaAnnounceClientCreate@@UAEXXZ"), // 12 0x004C9A82
	(const void *)&__identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ"), // 13 0x000CA841
	(const void *)&__identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ")  // 14 0x000CA841
};
// Retail table 0x00C5ED48 (2 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?rva004C9A51@EvaAnnounceClientCreate@@UAEXXZ")();
}
static const void *const s_secondary0C[2] = {
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  0 0x000B3FD0
	(const void *)&__identifier("?rva004C9A51@EvaAnnounceClientCreate@@UAEXXZ")  //  1 0x004C9A51
};

// Rowed Rva00362EC7 base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	int m_10;
};

class EvaAnnounceClientCreate : public Rva00362EC7
{
public:
	EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_14;
};

// ??0EvaAnnounceClientCreate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C99D4
EvaAnnounceClientCreate::EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	*(const void * volatile *)&m_p0C = __identifier("??_7Rva004C9994@@6B@");
	_ReadWriteBarrier();
	m_10 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_14 = 0;
}
