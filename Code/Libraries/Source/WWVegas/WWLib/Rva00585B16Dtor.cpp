// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva00585B16@@QAE@XZ @0x00585B16 8B tail-jmp to rowed deque dtor;
// callers at 0x00585D24 0x00586B9B and Unwind funclets; unlock.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmeE12 { float x, y, z; };
class Rva00585B16
{
public:
	Rva00585B16();
	Rva00585B16(const Rva00585B16 &other);
	~Rva00585B16();
private:
	int m_0;
	float m_4;
	float m_8;
	float m_C;
	int m_10;
	int m_14;
	int m_18;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	_STL::deque<BfmeE12, _STL::allocator<BfmeE12 > > m_deque;
	int m_50;
};
Rva00585B16::~Rva00585B16()
{
}
Rva00585B16::Rva00585B16()
	: m_0(0)
	, m_1C(1)
	, m_20(0)
	, m_24(0)
	, m_deque()
	, m_50(0)
{
	m_4 = 0.0f;
	m_8 = 0.0f;
	m_C = 0.0f;
}
Rva00585B16::Rva00585B16(const Rva00585B16 &other)
	: m_0(other.m_0)
	, m_4(other.m_4)
	, m_8(other.m_8)
	, m_C(other.m_C)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1C(other.m_1C)
	, m_20(other.m_20)
	, m_24(other.m_24)
	, m_deque(other.m_deque)
	, m_50(other.m_50)
{
}
