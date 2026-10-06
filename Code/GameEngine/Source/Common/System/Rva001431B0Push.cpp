// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva001431B0@Rva001431B0@@QAEXVRva00142DF0String@@@Z, RVA 0x001431B0, 131B.
// Push a by-value Rva00142DF0String into the member vector at +0x13c: the
// refcounted handle Rva001431B0Pop.cpp names (held as AsciiString until
// 2026-10-02; see Rva00142DF0StringVector.cpp for why it is not).
// Evidence: fast path inlines copy as test esi/mov [eax] esi/add [esi+4] 1,
// slow path calls rowed vector<Rva00142DF0String>::_M_insert_overflow at 0x00143070,
// trailing param release is dec-to-zero plus slot-0 call; callers at 0x0007DCD4
// 0x000D7C00 0x00101386 0x001016C2 pass this from [ebp+8] with pre-inc copy;
// layout proven by lea getter 0x00142C40 pop 0x00142DF0 and vector dtor 0x00142E30.

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

#include <vector>

class Rva00142DF0String
{
	struct Rva00142DF0StringData
	{
		virtual void _M_slot_00();
		int m_refCount;
	};

	Rva00142DF0StringData *m_data;

public:
	Rva00142DF0String(const Rva00142DF0String &that)
	{
		m_data = that.m_data;
		if (m_data)
			m_data->m_refCount++;
	}
	~Rva00142DF0String()
	{
		Rva00142DF0StringData *data = m_data;
		if (data && --data->m_refCount == 0)
			data->_M_slot_00();
	}
};

namespace _STL
{

template <>
inline void _Construct<Rva00142DF0String, Rva00142DF0String>(Rva00142DF0String *dest, const Rva00142DF0String &src)
{
	if (dest)
		new (dest) Rva00142DF0String(src);
}

}

class Rva001431B0
{
	char m_pad[0x13c];
	_STL::vector<Rva00142DF0String, _STL::allocator<Rva00142DF0String> > m_vec;

public:
	void rva001431B0(Rva00142DF0String str);
};

void Rva001431B0::rva001431B0(Rva00142DF0String str)
{
	m_vec.push_back(str);
}
