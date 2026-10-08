// cl: /O1 /arch:SSE /G7 /MD /EHsc
// Identity: newRoad/newBridge allocate this type at 0x002DB1CA; their
// native field accesses and ZH TerrainRoadType agree on name +4, bridge +8,
// id +0xC, next +0x10, widths +0x14/+0x18 and texture +0x38. Existing
// constructor/destructor ownership and all member cleanup bytes are retained.
// Built from the banked attempt reverse/attempts/0x002db1ca.cpp; fix: the float
// read through g_Va00BBB8D8 is a compiler literals holding the retail
// values, not extern globals, which is what gives retail's operand order.
// ??1TerrainRoadType@@UAE@XZ @0x002DB311 318B
// Evidence: unlock lane; vtable g_00C03E24; callees clear 0x0048BA39 releaseBuffer 0x00036410 TailRecord dtor 0x0010F149 and ??_M CRT; 11 singles + 7 arrays to 0x144.
// ??0TerrainRoadType@@QAE@XZ @0x002DB1CA 327B
// Evidence: unlock lane ctor of same class; vtable 0x00803E24; callees UnicodeString ctor 0x00326BE6 clear TailRecord dtor and ??_L CRT; POD floats/ints incl 1.0f.
extern const void *const g_00C03E24[];

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void clear();
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class AsciiElem
{
public:
	AsciiElem() : m_data(0) {}
	~AsciiElem() { ((StringBase<char> *)this)->clear(); }
private:
	void *m_data;
};
class OpaqueRefCounted
{
public:
	void Release_Ref();
};
class BfmeStringTailRecord156
{
public:
  BfmeStringTailRecord156();
	~BfmeStringTailRecord156();
private:
	OpaqueRefCounted *m_ptr;
};
class TerrainRoadType
{
public:
	TerrainRoadType();
	virtual ~TerrainRoadType();
	StringBase<char> m_04;
	unsigned char m_08;
	char m_pad09[3];
	int m_0C;
	int m_10;
	float m_14;
	float m_18;
	float m_1C;
	StringBase<char> m_20;
	StringBase<char> m_24;
	float m_28;
	float m_2C;
	float m_30;
	StringBase<char> m_34;
	StringBase<char> m_38;
	StringBase<char> m_3C;
	StringBase<char> m_40;
	StringBase<char> m_44;
	StringBase<char> m_48;
	StringBase<char> m_4C;
	StringBase<char> m_50;
	AsciiElem m_54[4];
	BfmeStringTailRecord156 m_64[4];
	AsciiElem m_74[12];
	AsciiElem m_A4[12];
	BfmeStringTailRecord156 m_D4[4];
	AsciiElem m_E4[12];
	AsciiElem m_114[12];
	float m_144;
	int m_148;
};
// TerrainRoadType::~TerrainRoadType: defined in Rva002DB311Dtor.cpp (its row's unit).
TerrainRoadType::TerrainRoadType()
{
	float v0 = 0.0f;
	float v1C = 1.0f;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_148 = 0;
	m_14 = v0;
	m_18 = v0;
	m_1C = v1C;
	m_28 = v0;
	m_2C = v0;
	m_30 = v0;
	m_144 = v0;
}
