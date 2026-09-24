// cl: /O1 /MD /DNDEBUG /EHsc /arch:SSE
//
// ??0SiegeEngineContainModuleData@@QAE@XZ, retail 0x0047C927 (136 bytes).
// EH derived ctor over the pinned TransportContainModuleData base
// (0x00468301, real size 0x18C): the base call builds the base, the +0x18C
// member constructs through the pinned Rva003623E5Member ctor, and a
// 128-bit mask at +0x1A4 resets through the rowed bitset<128>::reset at
// 0x0024CA24 amid int zeros plus a 1.0 float slot. The +0x194/+0x198 pair
// is nulled together by the SiegeStringIntPair default ctor (two stores
// through edi, before the mask lea); the pair carries a dtor so the second
// EH unwind state (state 2) matches retail. The string is cleared through
// the pinned AsciiString::clear at 0x00036410 (fold-shared with the string
// teardown there); the neighbour int re-stores after the call behind the
// compiler's aliasing barrier, plus the trailing flag at +0x1B4. Size 0x1B8
// matches the RiderChangeContain derivation (8 RiderInfo slots open at
// +0x1B8). Identity is the ModuleFactory registration under
// "SiegeEngineContain" (sole-caller data factory per the ctor pin).
// Row supersedes the ctor pin.

namespace _STL
{

template <unsigned _Bits>
class bitset
{
public:
	unsigned long m_words[(_Bits + 31) / 32];
	bitset<_Bits> &reset();
};

}

class AsciiString
{
public:
	void clear();
	~AsciiString();

private:
	void *m_data;
};

struct SiegeStringIntPair
{
	SiegeStringIntPair() : m_stringData(0), m_int198(0) {}
	~SiegeStringIntPair();

	void *m_stringData;	// +0x194
	int m_int198;	// +0x198
};

class TransportContainModuleData
{
public:
	TransportContainModuleData();
	virtual ~TransportContainModuleData();

private:
	unsigned char m_opaque[0x18C - 4];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
};

class SiegeEngineContainModuleData : public TransportContainModuleData
{
public:
	SiegeEngineContainModuleData();

private:
	Rva003623E5Member m_member18C;	// +0x18C
	int m_int190;	// +0x190
	SiegeStringIntPair m_pair194;	// +0x194/+0x198
	float m_float19C;	// +0x19C
	bool m_flag1A0;	// +0x1A0
	unsigned char m_pad1A1[3];
	_STL::bitset<128> m_mask1A4;	// +0x1A4
	bool m_flag1B4;	// +0x1B4
	unsigned char m_pad1B5[3];
};

SiegeEngineContainModuleData::SiegeEngineContainModuleData()
	: TransportContainModuleData()
{
	m_mask1A4.reset();
	m_int190 = 0;
	m_float19C = 1.0f;
	m_flag1A0 = false;
	reinterpret_cast<AsciiString *>(&m_pair194)->clear();
	m_pair194.m_int198 = 0;
	m_flag1B4 = false;
}
