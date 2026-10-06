// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001F88B4@Rva001F88B4@@QAEXABVRvaSmartPtr12@@@Z @0x001F88B4 (22B): list push_back plus count.
// Pushes arg onto list at +0x4c via rowed push_back at 0x001F81D2 then inc at
// +0x58. Caller at 0x001FCBB1. Prev Rva001F8810Put next StlportListInsertFootprints.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class RvaSmartPtr12
{
	char m_pad[12];
public:
	RvaSmartPtr12(const RvaSmartPtr12 &);
	~RvaSmartPtr12();
};

namespace _STL {
template<> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *dest, const RvaSmartPtr12 &source) throw();
}

class Rva001F88B4
{
public:
	void rva001F88B4(const RvaSmartPtr12 &v);
private:
	char m_pad[0x4c];
	_STL::list<RvaSmartPtr12> m_list;
	char m_pad2[8];
	int m_count;
};

void Rva001F88B4::rva001F88B4(const RvaSmartPtr12 &v)
{
	m_list.push_back(v);
	++m_count;
}
