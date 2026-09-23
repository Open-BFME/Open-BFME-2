// cl: /O1 /DNDEBUG /MD
//
// ??0ToggleDeploySpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE547,
// 32 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54):
// installs vtable 0x00C553D8 explicitly (novtable) and clears the +0xC8 and
// +0xCC words (and-RMW, barrier-pinned below the vtable install per the
// BuffDraw precedent). Class size 0xD0 proven by the
// ToggleDeploySpecialAbilityUpdate data factory (news 0xD0, sole caller at
// 0x24F83D); base size 0xC8 inferred from the +0xC8 position. Row supersedes
// the ctor pin.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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

class __declspec(novtable) ToggleDeploySpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ToggleDeploySpecialAbilityUpdateModuleData();

private:
	// +0xC8/+0xCC cleared words (end at the rowed 0xD0 instance size).
	unsigned int m_wordC8;
	unsigned int m_wordCC;
};

// ??0ToggleDeploySpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE547
ToggleDeploySpecialAbilityUpdateModuleData::ToggleDeploySpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	*(unsigned int *)this = 0x00C553D8;
	_ReadWriteBarrier();
	m_wordC8 &= 0;
	m_wordCC &= 0;
}
