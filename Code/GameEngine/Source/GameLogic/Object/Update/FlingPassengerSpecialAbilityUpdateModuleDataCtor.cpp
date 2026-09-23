// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0FlingPassengerSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00494F80,
// 48 bytes. ModuleData ctor over the pinned Rva0044EB54 base (0x44EB54,
// 0xC8 bytes per the ToggleHidden row): zeroes three floats at
// +0xC8/+0xCC/+0xD0 via an xmm0-homed fzero local through an address-taken
// float pointer (/arch:SSE emits retail lea+movss; the pointer CSEs the
// block address into eax), installs vtable 0x00C5F778 explicitly (novtable;
// shares the ToggleHidden vtable) and clears the +0xD4 word (and-RMW).
// Class size 0xD8 proven by the FlingPassengerSpecialAbilityUpdate data
// factory (news 0xD8, sole caller at 0x24DE96). Row supersedes the ctor pin.

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

class __declspec(novtable) FlingPassengerSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	FlingPassengerSpecialAbilityUpdateModuleData();

private:
	// +0xC8/+0xCC/+0xD0 float zeros.
	float m_floatC8[3];
	// +0xD4 cleared word (ends at the rowed 0xD8 instance size).
	unsigned int m_wordD4;
};

// ??0FlingPassengerSpecialAbilityUpdateModuleData@@QAE@XZ @0x00494F80
FlingPassengerSpecialAbilityUpdateModuleData::FlingPassengerSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	float fzero = 0.0f;
	float *floats = m_floatC8;
	*(unsigned int *)this = 0x00C5F778;
	floats[0] = fzero;
	floats[1] = fzero;
	floats[2] = fzero;
	m_wordD4 &= 0;
}
