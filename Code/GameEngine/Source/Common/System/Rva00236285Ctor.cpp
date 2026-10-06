// cl: /DNDEBUG /MD /GX-
// ??0Rva00236285@@QAE@XZ @0x00236285 47B leaf: __thiscall ctor zeroes 5 dwords constructs BfmeE16 Vector_base at +0x14 sets +0x20 to g_007ED97C+1
// evidence: same rowed Vector_base @0x00211E58 via one-byte stack allocator temp at esp+7 plus global g_007ED97C mangled ?g_007ED97C@@3IA plus frameless push ecx push esi shape; callers 0x00237281 0x0023728C; Rva003F1F6A precedent for declared-only base forcing CALL
struct BfmeE16
{
	float x, y, z, w;
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A = allocator<T> > struct _Vector_base
{
	_Vector_base(const A &alloc);
	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
};
}

extern unsigned int g_007ED97C;

class Rva00236285
{
public:
	Rva00236285();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_14;
	int m_20;
};

Rva00236285::Rva00236285() : m_00(0), m_04(0), m_08(0), m_0C(0), m_10(0), m_14(_STL::allocator<BfmeE16>())
{
	m_20 = g_007ED97C + 1;
}
