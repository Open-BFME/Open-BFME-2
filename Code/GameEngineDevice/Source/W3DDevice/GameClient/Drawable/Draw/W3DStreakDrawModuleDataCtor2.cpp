// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??0W3DStreakDrawModuleData@@QAE@XZ, retail 0x000D0520, 92 bytes.
// Frameless ModuleData ctor over an inline base holding Length at +0x08
// (50.0f, no base call since the base has no virtuals and its ctor inlines):
// implicit derived vtable 0x00BCDAB0 at +0x00, Width at +0x0C (0.5f),
// Additive at +0x10 (true), Color triple at +0x14/+0x18/+0x1C (1.0f each,
// body stores after the vector call), NumSegments at +0x20 (5), Texture
// AsciiString at +0x24 (inline-zero gives the `and [mem],0` idiom, no call),
// WeatherTexture vector at +0x28 through the ICF-folded BfmeE16 Vector_base
// at 0x00211E58 (explicit allocator temp gives frameless lea esp+7).
// Table 0x00BCDB60 proves the names and offsets (Length+8/Width+C/
// Additive+10/Color+14/NumSegments+20/Texture+24/WeatherTexture+28, matching
// the BFME1 W3DStreakDraw donor plus the WeatherTexture tail). Factory
// 0x00064F47 news 0x34 and calls this ctor at 0x64F68 (sole caller); the
// chained parse proc at 0xD0726 is rowed. Row supersedes the ctor pin.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	const char *m_data;
};

class W3DStreakDrawModuleDataBase
{
public:
	W3DStreakDrawModuleDataBase()
		: m_length(50.0f)
	{
	}

private:
	unsigned char m_pad04[4];	// +0x04 untouched
	float m_length;		// +0x08 Length
};

class W3DStreakDrawModuleData : public W3DStreakDrawModuleDataBase
{
public:
	W3DStreakDrawModuleData();
	virtual ~W3DStreakDrawModuleData();

private:
	float m_width;		// +0x0C Width
	bool m_additive;		// +0x10 Additive
	unsigned char m_pad11[3];
	float m_color00;		// +0x14 Color
	float m_color01;		// +0x18
	float m_color02;		// +0x1C
	int m_numSegments;	// +0x20 NumSegments
	AsciiString m_texture;	// +0x24 Texture
	_STL::vector<BfmeE16> m_weatherTexture;	// +0x28 WeatherTexture
};

W3DStreakDrawModuleData::W3DStreakDrawModuleData()
	: m_width(0.5f),
	  m_additive(true),
	  m_numSegments(5),
	  m_texture(),
	  m_weatherTexture(_STL::allocator<BfmeE16>())
{
	m_color00 = 1.0f;
	m_color01 = 1.0f;
	m_color02 = 1.0f;
}
