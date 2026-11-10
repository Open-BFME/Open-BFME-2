// cl: /EHs-c-
//
// ??0Rva00563FE1@@QAE@I@Z, retail 0x00563FE1, 32 bytes.
//
// Single-argument __thiscall constructor: parks the incoming dword at +0x04,
// then writes the shared secondary vftable 0x00C1C780 at +0x08, the primary
// vftable 0x00C1D2C0 at +0x00, and the shared secondary again at +0x08.
//
// BFME1 near-miss donor is reference/open-bfme-1/.../T4VtableSetCtors.cpp,
// Rva005EE820 at 0x005EE820 (32 bytes, same store sequence through the BFME1
// tables 0x0110F978/0x01112B28/0x01112B24, but `ret 8`: its second parameter
// is never read). BFME2 dropped that unread parameter, so the callee pops
// four bytes instead of eight; the remaining stores are unchanged. Both
// +0x08 stores hold the same table here, spelled as two volatile stores so
// the compiler may neither merge nor drop them, exactly as the donor models
// the inlined-base-then-derived sequence.
//
// Tables use address-derived aliases, preserving uncertainty about the
// caller's class identity while resolving real linker definitions.
// 0x00C1C780 is independently witnessed as a shared secondary vftable: the
// Die-family intermediate base 0x45CEBD installs it alongside 0xC41E78 and
// 0xC4A650, and the FXParticleSystem velocity template row 0x3A73F8 lists it
// among its subobject vtables. No caller names this body, so the class keeps
// its address-derived name.

// Folded 0x0081C780 (one __purecall slot at RVA 0x0003B810): reference clean
// 4B COMDAT tables directly without claiming donor class identity.
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];

extern "C" const void *const __identifier("??_7Rva005EA430@@6BV3Vt01111D90@@@")[];  // vftable 0x00C1D2C0

class Rva00563FE1
{
public:
	Rva00563FE1( unsigned int a );
private:
	unsigned char m_storage[ 0x0c ];
};

// Distinct folded 0x0081C780 COMDAT spelling preserves both immediate stores
// cleanly without CSE merging or linker aliases.
extern "C" const void *const __identifier("??_7Rva003F498ACallback@@6B@")[];

Rva00563FE1::Rva00563FE1( unsigned int a )
{
	volatile unsigned int *slots = (unsigned int *)this;
	slots[ 1 ] = a;
	slots[ 2 ] = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
	slots[ 0 ] = ((unsigned int)__identifier("??_7Rva005EA430@@6BV3Vt01111D90@@@"));
	slots[ 2 ] = (unsigned int)__identifier("??_7Rva003F498ACallback@@6B@");
}
