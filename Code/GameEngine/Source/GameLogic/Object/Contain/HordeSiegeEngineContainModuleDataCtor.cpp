// cl: /O1 /MD /DNDEBUG /EHsc /arch:SSE
//
// ??0HordeSiegeEngineContainModuleData@@QAE@XZ, retail 0x0047DA08 (117 bytes).
// EH derived ctor over the rowed HordeTransportContainModuleData base
// (0x00477D61, landed this session, size 0x18C): the base call builds the
// base, the +0x18C member constructs through the pinned
// Rva003623E5Member ctor, and a 128-bit mask at +0x1A4 resets through the
// rowed bitset<128>::reset at 0x0024CA24 amid int/byte zeros plus a 1.0
// float slot. One unwind state (the base) covers the throwing member calls;
// the members stay trivially destructible. Donor: BFME1 Contain files (the
// HordeSiegeEngine pair extends HordeTransportContain the same way).
// Identity is the ModuleFactory registration under "HordeSiegeEngineContain"
// (sole-caller data factory per the superseded ctor pin).

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

class HordeTransportContainModuleData
{
public:
	HordeTransportContainModuleData();
	virtual ~HordeTransportContainModuleData();

private:
	unsigned char m_opaque[0x18C - 4];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
};

class HordeSiegeEngineContainModuleData : public HordeTransportContainModuleData
{
public:
	HordeSiegeEngineContainModuleData();

private:
	Rva003623E5Member m_member18C;	// +0x18C
	int m_int190;	// +0x190
	int m_pair194[2];	// +0x194, retail zeroes the pair through eax
	float m_float19C;	// +0x19C
	bool m_flag1A0;	// +0x1A0
	bool m_flag1A1;	// +0x1A1
	_STL::bitset<128> m_mask1A4;	// +0x1A4
};

HordeSiegeEngineContainModuleData::HordeSiegeEngineContainModuleData()
	: HordeTransportContainModuleData()
{
	int *pair194 = m_pair194;
	pair194[0] = 0;
	pair194[1] = 0;
	m_mask1A4.reset();
	m_int190 = 0;
	m_float19C = 1.0f;
	m_flag1A0 = false;
	m_flag1A1 = false;
}
