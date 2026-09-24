// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RadiateFearUpdateModuleData@@QAE@XZ, retail 0x0049C06C, 120 bytes.
// RadiateFear ModuleData: own table at 0x00C510B8 carries InitiallyActive
// at +0x08, WhichSpecialPower at +0x0C, GenerateTerror at +0x10,
// GenerateFear at +0x11, GenerateUncontrollableFear at +0x12,
// EmotionPulseRadius at +0x14, EmotionPulseInterval at +0x18 and
// VictimFilter at +0x1C, matching every store below; the ModuleData
// factory at 0x24E6E8 news 0x130 with this ctor as its sole raw caller
// and the proc at 0x49C0E4 is rowed. Shape follows
// InvisibilitySpecialPowerModuleData (single-temp applyFilter tail through
// the 0x362120 pin with the FixedStorage temp built in place from
// 0x00DFEFA4 through the rowed 0x4543D copy): the VictimFilter member
// builds through the 0x3623E5 pin and the +0x20 member through the rowed
// 0x25342C construct.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_filterData;
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();
};

class UpdateModuleData
{
public:
	UpdateModuleData();
	~UpdateModuleData();
};

inline UpdateModuleData::UpdateModuleData()
{
}

class RadiateFearUpdateModuleData : public UpdateModuleData
{
public:
	RadiateFearUpdateModuleData();

private:
	void *m_vtable; // +0x00
	int m_unused04; // +0x04
	bool m_initiallyActive; // +0x08
	char m_pad09[3];
	int m_whichSpecialPower; // +0x0C
	unsigned char m_generateTerror; // +0x10
	unsigned char m_generateFear; // +0x11
	unsigned char m_generateUncontrollableFear; // +0x12
	unsigned char m_pad13;
	float m_emotionPulseRadius; // +0x14
	int m_emotionPulseInterval; // +0x18
	Rva003623E5Filter m_victimFilter; // +0x1C
	Rva0025342CMember m_20; // +0x20
	unsigned char m_pad[0x130 - 0x20 - 4];
};

// ??0RadiateFearUpdateModuleData@@QAE@XZ @0x0049C06C
RadiateFearUpdateModuleData::RadiateFearUpdateModuleData()
	: m_vtable((void *)0x00C50FF0)
	, m_initiallyActive(false)
	, m_whichSpecialPower(-1)
	, m_generateTerror(0)
	, m_generateFear(0)
	, m_generateUncontrollableFear(0)
	, m_emotionPulseRadius(0.0f)
	, m_emotionPulseInterval(0)
	, m_victimFilter()
{
	m_20.construct();
	reinterpret_cast<Rva003623E5Filter *>(&m_victimFilter)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
