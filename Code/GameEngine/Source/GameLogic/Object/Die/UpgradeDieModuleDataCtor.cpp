// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0UpgradeDieModuleData@@QAE@XZ, retail 0x002550ED, 22 bytes.
// Frameless ctor over the pinned SEH base (??0Rva00253510@@QAE@XZ at
// 0x253510, whose 12 ctor-position callers include this body at 0x2550F0):
// base call, then the distinctive vtable literal 0x00BF33C0, then the
// compact and-zero of the UpgradeToRemove name word at +0x38 (the rowed
// buildFieldParse table 0x00BF0958 holds UpgradeToRemove at +0x38, and
// BFME1's UpgradeDieModuleDataCtorThunk donor models the same word as the
// AsciiString m_upgradeName data with m_data(0) inline init). BFME1's base
// DieModuleData is 0x34 (Snapshot plus mux) while this body addresses the
// member at +0x38, so the BFME2 base runs 4 wider; the TU-local base stays
// empty and the derived pad covers +4..0x37. Size 0x3C matches the
// 0x255103 factory news. Class identity is the field_names vote (1/1:
// UpgradeToRemove belongs to UpgradeDieModuleData) plus the rowed
// UpgradeDie pool key (0x486B75) in this family.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00253510
{
public:
	Rva00253510();
};

class UpgradeDieModuleData : public Rva00253510
{
public:
	UpgradeDieModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	unsigned char m_pad[0x34]; // +4..0x37 (BFME2 base runs 4 wider than BFME1's 0x34)
	int m_upgradeName; // +0x38 (AsciiString data word; BFME1 m_upgradeName)
};

// ??0UpgradeDieModuleData@@QAE@XZ @0x2550ED
UpgradeDieModuleData::UpgradeDieModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF33C0);
	_ReadWriteBarrier();
	m_upgradeName = 0;
}
