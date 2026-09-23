// cl: /O1 /DNDEBUG /MD
//
// ??0ScaleWallSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00494DB1,
// 25 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54):
// clears the +0xC8 word (and-RMW) and installs vtable 0x00C5F778
// explicitly (novtable; shares the ToggleHidden vtable). Class size 0xCC
// proven by the ScaleWallSpecialAbilityUpdate data factory (news 0xCC, sole
// caller at 0x24DDEC); base size 0xC8 inferred from the +0xC8 position. Row
// supersedes the ctor pin.

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

class __declspec(novtable) ScaleWallSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ScaleWallSpecialAbilityUpdateModuleData();

private:
	// +0xC8 cleared word (ends at the rowed 0xCC instance size).
	unsigned int m_wordC8;
};

// ??0ScaleWallSpecialAbilityUpdateModuleData@@QAE@XZ @0x00494DB1
ScaleWallSpecialAbilityUpdateModuleData::ScaleWallSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_wordC8 &= 0;
	*(unsigned int *)this = 0x00C5F778;
}
