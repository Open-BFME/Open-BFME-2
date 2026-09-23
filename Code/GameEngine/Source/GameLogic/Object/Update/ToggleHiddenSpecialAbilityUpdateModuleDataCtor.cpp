// cl: /O1 /DNDEBUG /MD
//
// ??0ToggleHiddenSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE155,
// 25 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54):
// installs vtable 0x00C5F778 explicitly (novtable) and zeroes the +0xC8
// flag. Class size 0xCC proven by the ToggleHiddenSpecialAbilityUpdate data
// factory (news 0xCC, sole caller at 0x24F793); base size 0xC8 inferred from
// the flag position. Row supersedes the ctor pin.

class __declspec(novtable) Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0xC4 bytes); only the 0xC8 size matters.
	unsigned char m_opaque[0xC4];
};

class __declspec(novtable) ToggleHiddenSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();

private:
	// +0xC8 flag (false).
	bool m_flagC8;
	char m_padC9[3]; // to the rowed 0xCC instance size
};

// ??0ToggleHiddenSpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE155
ToggleHiddenSpecialAbilityUpdateModuleData::ToggleHiddenSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	*(unsigned int *)this = 0x00C5F778;
	m_flagC8 = false;
}
