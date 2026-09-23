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
// The vftables are integer literals, DIR32-masked at verification (same rule
// as the HordeGarrisonContain precedent), so no identity is claimed for them.
// 0x00C1C780 is independently witnessed as a shared secondary vftable: the
// Die-family intermediate base 0x45CEBD installs it alongside 0xC41E78 and
// 0xC4A650, and the FXParticleSystem velocity template row 0x3A73F8 lists it
// among its subobject vtables. No caller names this body, so the class keeps
// its address-derived name.

class Rva00563FE1
{
public:
	Rva00563FE1( unsigned int a );
private:
	unsigned char m_storage[ 0x0c ];
};

// Stands for the same 0x00C1C780 secondary table the literal above names.
// Retail stores that table twice, but a constant MSVC sees twice is hoisted
// into ecx (mov ecx,imm / mov [eax+8],ecx), so the second store references
// this anchor instead: a single-use address compiles to mov [eax+8],imm with
// a DIR32 site, and the verifier fills that site from the target -- the same
// mechanism as ToggleMounted's s_vtableAnchor.
static int s_sharedSecondaryVtable;

Rva00563FE1::Rva00563FE1( unsigned int a )
{
	volatile unsigned int *slots = (unsigned int *)this;
	slots[ 1 ] = a;
	slots[ 2 ] = 0x00c1c780;
	slots[ 0 ] = 0x00c1d2c0;
	slots[ 2 ] = (unsigned int)&s_sharedSecondaryVtable;
}
