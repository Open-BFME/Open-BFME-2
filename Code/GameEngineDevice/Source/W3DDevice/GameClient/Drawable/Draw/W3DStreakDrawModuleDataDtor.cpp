// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??1W3DStreakDrawModuleData@@UAE@XZ, retail 0x000D057C, 69 bytes.
// W3DStreakDraw ModuleData dtor: reinstalls the vtable 0x00BCDAB0, tears
// down the WeatherTexture vector at +0x28 through the 0xD04E1 body (pinned
// below as W3DStreakWeatherVec; the rowed _Destroy at 0x48CE25 proves
// 8-byte elements and the dup_ vector-dtor row lives at this address, plus
// the +8 stride in the 0xD068F insert), tears down the Texture AsciiString
// at +0x24 through the folded AsciiString dtor at 0x36410, then restores
// the Snapshot base vtable 0x00BBB554 through the TU-local inline base
// dtor. Two EH states for the two members, frameless companion ctor at
// 0xD0520 proves the layout (vptr +0, pad +0x04, Length +0x08, Width +0x0C,
// Additive +0x10, Color +0x14/+0x18/+0x1C, NumSegments +0x20, Texture +0x24,
// WeatherTexture +0x28, size 0x34 per the factory at 0x64F47). Table
// 0x00BCDB60 names all members; the ??_G caller at 0xD0676 is the slot-0
// deleting dtor. Shape follows the landed W3DLightDrawModuleDataDtor and
// FlammableUpdateModuleDataDtor TUs.

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

struct W3DStreakWeatherVec
{
	~W3DStreakWeatherVec();

	void *m_start;
	void *m_finish;
	void *m_end;
};

class W3DStreakDrawModuleData : public Snapshot
{
public:
	virtual ~W3DStreakDrawModuleData();

private:
	unsigned char m_pad04[4];	// +0x04 untouched
	float m_length;		// +0x08 Length
	float m_width;		// +0x0C Width
	bool m_additive;		// +0x10 Additive
	unsigned char m_pad11[3];
	float m_color00;		// +0x14 Color
	float m_color01;		// +0x18
	float m_color02;		// +0x1C
	int m_numSegments;	// +0x20 NumSegments
	AsciiString m_texture;	// +0x24 Texture
	W3DStreakWeatherVec m_weatherTexture;	// +0x28 WeatherTexture
};

W3DStreakDrawModuleData::~W3DStreakDrawModuleData()
{
}
