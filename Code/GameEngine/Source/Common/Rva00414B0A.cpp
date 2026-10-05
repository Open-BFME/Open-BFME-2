// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?rva00414B0A@Rva00414B0A@@QAEXXZ retail 0x00414B0A 26B. Vector erase plus two int clears.
// Evidence: rowed erase 0x00414760 vector<BfmeAssignRecord44>; caller 0x00414B89 iterates 0x30 entries; layout matches Rva00414932Dtor vector at +0x1C.
#include <vector>

#include "ascii_string.h"

struct BfmeAssignRecord44
{
	AsciiString s;
	int a[10];
};

class Rva00414B0A
{
public:
	void rva00414B0A();
private:
	char m_pad00[0x1C];
	_STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> > m_vec1C;
	int m_28;
	int m_2C;
};

void Rva00414B0A::rva00414B0A()
{
	_STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> > &v = m_vec1C;
	v.erase(v.begin(), v.end());
	m_28 = 0;
	m_2C = 0;
}
