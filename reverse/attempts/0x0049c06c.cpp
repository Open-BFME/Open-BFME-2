// ??0RadiateFearUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-23
// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RadiateFearUpdateModuleData@@QAE@XZ, retail 0x0049C06C, 120 bytes.
// MD ctor: WhichSpecialPower at +0x0C or-minus-one FIRST (OCLUpdate
// precedent: body `|= -1` stays above the vtable store under /O1, a plain
// `= -1` would emit a trailing mov), explicit vtable 0x00C50FF0, the
// table-backed bytes (InitiallyActive at +0x08, GenerateTerror at +0x10,
// GenerateFear at +0x11, GenerateUncontrollableFear at +0x12, all false),
// EmotionPulseRadius at +0x14 as float zero, EmotionPulseInterval at +0x18
// as zero, VictimFilter at +0x1C through the trivial Rva003623E5Member
// (body construct call through the QAEXXZ pin) plus the +0x20 member
// through Rva0025342CMember::construct (implicit trivial ctor plus
// declared-only dtor, so EH state 1 lands right before its first
// throwing call, matching retail), then the single-temp applyFilter tail
// through the 0x362120 pin (MobNexus precedent: FixedStorage temp
// copy-constructed in the call expression from 0x00DFEFA4). The empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor)
// advances EH state 0 with no emitted code. Field identity is the own
// table at 0x00C510B8. The rowed factory at 0x24E6E8 news 0x130. Row
// supersedes the ctor pin.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	void construct();
	~Rva003623E5Member();

private:
	char m_data[4];
};

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();
	~Rva0025342CMember();

private:
	unsigned char m_pad[0x110];
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class RadiateFearUpdateModuleData : public UpdateModuleData
{
public:
	RadiateFearUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	bool m_initiallyActive; // +0x08
	int m_whichSpecialPower; // +0x0C
	bool m_generateTerror; // +0x10
	bool m_generateFear; // +0x11
	bool m_generateUncontrollableFear; // +0x12
	unsigned char m_pad13;
	float m_emotionPulseRadius; // +0x14
	int m_emotionPulseInterval; // +0x18
	Rva003623E5Member m_victimFilter; // +0x1C
	Rva0025342CMember m_member20; // +0x20
};

// ??0RadiateFearUpdateModuleData@@QAE@XZ @0x0049C06C
RadiateFearUpdateModuleData::RadiateFearUpdateModuleData()
{
	m_whichSpecialPower |= -1;
	m_vtable = reinterpret_cast<const void *>(0x00C50FF0);
	m_initiallyActive = false;
	m_generateTerror = false;
	m_generateFear = false;
	m_generateUncontrollableFear = false;
	m_emotionPulseRadius = 0.0f;
	m_emotionPulseInterval = 0;
	m_victimFilter.construct();
	m_member20.construct();
	reinterpret_cast<Rva003623E5Filter *>(&m_victimFilter)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
