// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005DCDD9@@QAE@HH@Z, retail 0x005DCDD9, 47 bytes.
// Ctor: three bool members at +0..2 cleared, vector<BfmeE16> at +4 via rowed
// Vector_base 0x00211E58 with empty allocator temp ([ebp+0xb] EBP frame),
// two int args stored at +0x10/+0x14, returns this. Evidence: callees rowed,
// callers 0x005ADE1D 0x005AE0AD pass 8 bytes. Honest address name.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva005DCDD9
{
public:
	Rva005DCDD9(int a, int b);
private:
	bool m_b0; // +0x0
	bool m_b1; // +0x1
	bool m_b2; // +0x2
	_STL::vector<BfmeE16> m_vec; // +0x4
	int m_10; // +0x10
	int m_14; // +0x14
};

Rva005DCDD9::Rva005DCDD9(int a, int b)
	: m_b0(false), m_b1(false), m_b2(false), m_vec(_STL::allocator<BfmeE16>())
{
	m_10 = a;
	m_14 = b;
}
