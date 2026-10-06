// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva001EC311@@QAE@ABV?$StringBase@D@@@Z, retail 0x001EC311, 56 bytes.
// Ctor: StringBase at +0 via pinned 0x000365F0, ints at +4/+8/+0xC/+0x10
// zeroed, id at +0x14 from global 0x007ED97C+1, vector<BfmeE16> at +0x18
// via rowed _Vector_base 0x00211E58. Evidence: neighbours 0x001EC056 and
// 0x001EC349, caller 0x001ED2F1, same flags as pod_vector_bodies.
#include <vector>
#include <new>

template <typename T>
class StringBase
{
public:
	StringBase<T> &operator=(const StringBase<T> &o);
private:
	StringBase(const StringBase<T> &o);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
	friend struct Rva001EC311;
};

struct BfmeE16 { float x, y, z, w; };

extern int g_007ED97C;

struct Rva001EC311
{
	StringBase<char> m_str00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_id14;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_base18;
	Rva001EC311(const StringBase<char> &k);
};

Rva001EC311::Rva001EC311(const StringBase<char> &k)
	: m_str00(k)
	, m_04(0)
	, m_08(0)
	, m_0C(0)
	, m_10(0)
	, m_id14(g_007ED97C + 1)
	, m_base18(_STL::allocator<BfmeE16>())
{
}
// ?g_007ED97C@@3HA: the global at VA 0xbed97c is ?g_007ED97C@@3IA.
#pragma comment(linker, "/alternatename:?g_007ED97C@@3HA=?g_007ED97C@@3IA")
