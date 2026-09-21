// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0DamageFilteredCreateObjectDieModuleData@@QAE@XZ, retail 0x00485F42,
// 35 bytes. Frameless ctor over the pinned SEH base
// (??0Rva00253510@@QAE@XZ at 0x253510, shared with the Die family): base
// call, then the and-zeros of the CreationList word at +0x38 and the
// PostFilterTriggeredDuration word at +0x44, the DamageType trigger words
// at +0x3C/+0x40 set to 3 through the shared-constant idiom, and the
// folded-trivial vtable literal 0x00C4ED70 last. Size 0x48 matches the
// 0x24C9D3 factory news. Class identity is the rowed pool key (0x485EFD)
// ending where this ctor begins, plus the rowed
// DamageFilteredCreateObjectDieModuleData::buildFieldParse proc
// (CreationList at +0x38 plus damage-trigger fields) pushed as the
// factory immediate.

class Rva00253510
{
public:
	Rva00253510();
};

class DamageFilteredCreateObjectDieModuleData : public Rva00253510
{
public:
	DamageFilteredCreateObjectDieModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	unsigned char m_pad[0x34]; // +4..0x37 (BFME2 base runs 4 wider than BFME1's 0x34)
	int m_creationList; // +0x38
	int m_damageTypeTriggersInstantly; // +0x3C
	int m_damageTypeTriggersForDuration; // +0x40
	int m_postFilterTriggeredDuration; // +0x44
};

// ??0DamageFilteredCreateObjectDieModuleData@@QAE@XZ @0x485F42
DamageFilteredCreateObjectDieModuleData::DamageFilteredCreateObjectDieModuleData()
{
	m_creationList = 0;
	m_postFilterTriggeredDuration = 0;
	m_damageTypeTriggersInstantly = 3;
	m_damageTypeTriggersForDuration = 3;
	m_vtable = reinterpret_cast<void *>(0x00C4ED70);
}
