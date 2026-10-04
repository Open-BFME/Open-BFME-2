// cl: /O1 /MD -D_STLP_NO_EXCEPTIONS /EHs-c-
// ??0OpenContainModuleData@@QAE@XZ @ 0x00253487 (21B): base ctor installing
// the folded vtable 0x00BF2558 (shared with derived HealContainModuleData,
// whose 36B ctor is matched in HealContainModuleDataCtorThunk.cpp) then
// constructing the member at +8.
// ?construct@Rva0025342CMember@@QAEPAV1@XZ @ 0x0025342C (73B): zeroes two
// 0x80-byte blocks through the shared clear80 helper, initializes the
// trailing state at +0x100, and returns this.
// The +8 member's semantic identity is unproven: ZH OpenContain.h says the
// first member is DieMuxData and DieModule.cpp already carries a
// ??0DieMuxData@@ present-unmatched marker for the concept, but the body at
// 0x0025342C has no independent identity yet, so the callee keeps an
// address-derived name here (pinned) instead of a guessed class name.
extern "C" const void *const vtbl_00BF2558[];  // ??_7WeaponSetUpgradeModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BF2558=??_7WeaponSetUpgradeModuleData@@6B@")

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	Rva001EAE6FHelper m_sub0; // +0x00
	Rva001EAE6FHelper m_sub1; // +0x80
	int m_tail0; // +0x100, initialized through both the tail pointer
	// below and directly (retail keeps both -1 stores; same-path
	// duplicates are folded by the compiler, mixed paths are not)
	int m_tail1; // +0x104
	int m_tail2; // +0x108
	unsigned char m_tailByte0; // +0x10C
	unsigned char m_tailByte1; // +0x10D
	unsigned char m_tailByte2; // +0x10E
};

class __declspec(novtable) OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	// +0x00 vptr (installed explicitly below; novtable suppresses the
	// compiler's own install so the folded 0x00BF2558 is the only store).
	// +0x04 UpdateModuleData tail per ZH OpenContain.h hierarchy
	// (trivially constructed — retail makes no base call).
	unsigned m_pad04;
	Rva0025342CMember m_member08;
};

// ?construct@Rva0025342CMember@@QAEPAV1@XZ, retail 0x0025342C, 73 bytes.
// Zeroes two 0x80-byte blocks through the shared helper, then initializes
// the trailing state at +0x100. Helper identity unproven (pinned opaque).

// ?construct@Rva0025342CMember@@QAEPAV1@XZ
Rva0025342CMember *Rva0025342CMember::construct()
{
	m_sub0.clear80();
	m_sub1.clear80();
	int *tail = &m_tail0;
	tail[0] = -1;
	tail[1] = 0;
	tail[2] = 0;
	m_tail0 = -1;
	m_tailByte0 = 0;
	m_tailByte1 = 0;
	m_tail1 = 0;
	m_tail2 = 0;
	m_tailByte2 = 0;
	return this;
}

// ??0OpenContainModuleData@@QAE@XZ
inline OpenContainModuleData::OpenContainModuleData()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF2558);
	m_member08.construct();
}

// OpenContainModuleData ctor is a header inline elsewhere: another unit emits
// a select-any copy, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitOpenContainModuleDataCtor@@YAXPAVOpenContainModuleData@@@Z present-unmatched
void bfmeEmitOpenContainModuleDataCtor(OpenContainModuleData *p)
{
	p->OpenContainModuleData::OpenContainModuleData();
}
#pragma inline_depth()
