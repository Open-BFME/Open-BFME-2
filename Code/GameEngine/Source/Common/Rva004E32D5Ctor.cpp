// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E32F2@@QAE@XZ @ 0x004E32D5 (29B). Default ctor: zero +4, bool +8=0,
// int-keyed map at +0x0C via rowed 0x005011C1, vtable 0x00861F68. Same class as
// copy ctor 0x0052D477 (int+byte+tree) and dtor 0x004E32F2. Caller 0x004E331C.
#include <map>
#include <new>
#include "../../Include/Common/RvaVec002B80CE.h"

struct BfmePod24 { int a[6]; };
template<> _STL::map<int, BfmePod24, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >::map() throw();

class Rva004E32F2
{
public:
	Rva004E32F2();
	virtual ~Rva004E32F2();

private:
	int m_04;
	bool m_08;
	RvaVec002B80CE m_vector0C;
};

Rva004E32F2::Rva004E32F2() : m_04(0), m_08(false)
{
	void *p = &m_vector0C;
	__assume(p != 0);
	new (p) _STL::map<int, BfmePod24>();
}
