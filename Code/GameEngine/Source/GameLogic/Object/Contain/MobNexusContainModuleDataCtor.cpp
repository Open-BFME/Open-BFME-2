// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0MobNexusContainModuleData@@QAE@XZ, retail 0x004C244D, 118 bytes.
// Mob-nexus contain data: the own table at 0x00C5C468 carries
// InvisibilityNugget at +0x7C, BroadcastRadius at +0x134, ObjectFilter at
// +0x138 and Duration at +0x13C, matching every store below; the ModuleData
// factory at 0x2518CB pushes this ctor's proc VA and the proc at 0x4C2389
// is rowed. Shape follows RousingSpeechUpdateModuleDataCtor (opaque
// virtual base through the 0x4930A0 pin, derived virtuals, mid-init vtable
// through the ??_7 pin) with the single-temp applyFilter tail through the
// 0x362120 pin: the InvisibilityNugget member builds through the fresh
// 0x2542F3 pin (119B frameless body, identity unproven) and the
// BroadcastRadius/Duration stores are init-listed so they bracket the
// filter construction exactly as retail.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva002542F3Member
{
public:
	Rva002542F3Member();

private:
	unsigned char m_data[0x9C];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	int m_x;
};

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);
};

class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

protected:
	unsigned char m_pad[0x7C - 4];
};

Rva004930A0::~Rva004930A0()
{
}

class MobNexusContainModuleData : public Rva004930A0
{
public:
	MobNexusContainModuleData();
	virtual ~MobNexusContainModuleData();

private:
	Rva002542F3Member m_invisibilityNugget; // +0x7C
	unsigned char m_pad118[0x134 - 0x118]; // +0x118
	float m_broadcastRadius; // +0x134
	Rva003623E5Member m_objectFilter; // +0x138
	int m_duration; // +0x13C
};

MobNexusContainModuleData::~MobNexusContainModuleData()
{
}

// ??0MobNexusContainModuleData@@QAE@XZ @0x4C244D
MobNexusContainModuleData::MobNexusContainModuleData()
	: Rva004930A0()
	, m_broadcastRadius(0.0f)
	, m_duration(0)
{
	reinterpret_cast<Rva003623E5Filter *>(&m_objectFilter)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
