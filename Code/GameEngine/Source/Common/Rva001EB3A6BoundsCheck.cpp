// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva001EB3A6@Rva001EB3A6@@QAEPAUBfmeAssignRecord36@@H@Z @0x001EB3A6 43B:
// bounds-checked accessor into vector<BfmeAssignRecord36> (36B element) at
// +0x18: if (i<0 || (unsigned)i>=size) return 0; return &vec[i]; size via
// (finish-start)/36 with cdq/idiv; index via imul 0x24 (/G7) plus base.
// Callers at 0x001EB3FE etc plus 0x001EB435/0x001EB6A5/0x001EC63D/0x001EB456.
// No donor; honest Rva outer.
#include <vector>
#include "ascii_string.h"
struct BfmeAssignRecord36
{
	AsciiString s;
	int a[8];
};
class Rva001EB3A6
{
public:
	BfmeAssignRecord36 *rva001EB3A6(int i);
private:
	char m_pad[0x18];
	_STL::vector<BfmeAssignRecord36, _STL::allocator<BfmeAssignRecord36> > m_18;
};
BfmeAssignRecord36 *Rva001EB3A6::rva001EB3A6(int i)
{
	if (i < 0 || (unsigned)i >= m_18.size())
		return 0;
	return &m_18[i];
}
