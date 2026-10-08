// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E5A24@@QAE@XZ @0x004E5A24 84B: ctor via baseConstruct + vector BfmeE16 + floats.
// Calls row baseConstruct 0x001B4E63 then zeroes +0xC then constructs vector at +0x10 via row 0x00211E58 then zeroes +0x1C/+0x20 then three floats. Vtable 0x00C623CC. Caller 0x002A64C2.
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeE16 { float x, y, z, w; };

class __declspec(novtable) BFME2NativeNetwork
{
public:
	__forceinline BFME2NativeNetwork() { baseConstruct(); }
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
	void baseConstruct();
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

extern float g_00DD00A8;
extern float g_00DD00AC;
extern float g_00C623C8;

class Rva004E5A24 : public BFME2NativeNetwork
{
public:
	Rva004E5A24();
private:
	int m_0C;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec10;
	int m_1C;
	int m_20;
	char m_pad24[4];
	float m_28;
	float m_2C;
	float m_30;
};

Rva004E5A24::Rva004E5A24()
	: m_0C(0),
	  m_vec10(_STL::allocator<BfmeE16>()),
	  m_1C(0),
	  m_20(0),
	  m_28(g_00DD00A8),
	  m_2C(g_00DD00AC),
	  m_30(g_00C623C8)
{
}
// ?g_00DD00AC@@3MA: the global at VA 0xdd00ac is ?g_00DD00AC@@3HA.
#pragma comment(linker, "/alternatename:?g_00DD00AC@@3MA=?g_00DD00AC@@3HA")
// ?g_00DD00A8@@3MA: the global at VA 0xdd00a8 is ?g_00DD00A8@@3HA.
#pragma comment(linker, "/alternatename:?g_00DD00A8@@3MA=?g_00DD00A8@@3HA")
