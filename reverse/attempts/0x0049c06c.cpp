// ??0RadiateFearUpdateModuleData@@QAE@XZ
// partial score=0.975 date=2026-09-23
// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RadiateFearUpdateModuleData@@QAE@XZ, retail 0x0049C06C, 120 bytes.
// Radiate-fear behavior module data: the rowed chained buildFieldParse at
// 0x49C0E4 double-adds on the rowed getter 0x4CE29D plus the own table at
// 0x00C510B8 (InitiallyActive at +8, WhichSpecialPower at +0xC,
// GenerateTerror at +0x10, GenerateFear at +0x11,
// GenerateUncontrollableFear at +0x12, EmotionPulseRadius at +0x14,
// EmotionPulseInterval at +0x18, VictimFilter at +0x1C) matching every
// store below; the rowed ModuleData factory at 0x24E6E8 news 0x130 and
// sole-calls this ctor; the rowed RadiateFearUpdate pool key at 0x49BFDD
// is in the same cluster. Shape follows AttributeModifierAura (filter
// member with dtor plus Rva0025342CMember construct member) with the
// MobNexus single-temp applyFilter tail through the rowed 0x362120 pin:
// the victim filter builds through the pinned 0x3623E5 spelling and the
// 28-byte temp copies out of the 0x00DFEFA4 global through the rowed
// 0x4543D spelling. The WhichSpecialPower or-first comes from the
// novtable base's inline ctor (base completion brackets state 0 before
// the derived vtable install, Topple empty-base pattern). Sole wall:
// the +8 byte store sits in base-init (pre-state0) where retail sinks it
// below the vtable install (post-state0); some 10 source shapes refuted.

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
	Rva003623E5Member();
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

private:
	unsigned char m_pad[0x110];
};

class __declspec(novtable) RadiateFearModuleDataBase
{
public:
	RadiateFearModuleDataBase()
	{
		m_whichSpecialPower |= -1;
		m_initiallyActive = false;
	}
	virtual ~RadiateFearModuleDataBase();

protected:
	int m_pad04; // +4
	bool m_initiallyActive; // +8
	int m_whichSpecialPower; // +0xC
};

class RadiateFearUpdateModuleData : public RadiateFearModuleDataBase
{
public:
	RadiateFearUpdateModuleData();
	virtual ~RadiateFearUpdateModuleData();

private:
	bool m_generateTerror; // +0x10
	bool m_generateFear; // +0x11
	bool m_generateUncontrollableFear; // +0x12
	float m_emotionPulseRadius; // +0x14
	int m_emotionPulseInterval; // +0x18
	Rva003623E5Member m_victimFilter; // +0x1C
	Rva0025342CMember m_block20; // +0x20
};

// ??0RadiateFearUpdateModuleData@@QAE@XZ @0x49C06C
RadiateFearUpdateModuleData::RadiateFearUpdateModuleData()
	: m_generateTerror(false)
	, m_generateFear(false)
	, m_generateUncontrollableFear(false)
	, m_emotionPulseRadius(0.0f)
	, m_emotionPulseInterval(0)
	, m_victimFilter()
{
	m_block20.construct();
	reinterpret_cast<Rva003623E5Filter *>(&m_victimFilter)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
