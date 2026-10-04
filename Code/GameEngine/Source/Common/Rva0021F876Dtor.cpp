// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??1Rva0021F876@@QAE@XZ @0x0021F8F3 104B. Dtor of the five-AsciiString plus
// vector<BfmePod216> record proven by the copy ctor at 0x0021F876 in
// Rva0021F876Copy.cpp: vector at +0x14 via rowed 0x0021F7A7 then
// releaseBuffer at +0x10/+0x0C/+0x08/+0x04/+0x00 via rowed 0x00036410.
// Evidence: callers at 0x0021FA95 and 0x0021FDDC plus jmp at 0x0021FAEC.
// The pin names BfmeNarrowRecord000BFDC7 but that record is a 0x20B
// basic_string layout that cannot emit these calls so the owner stays
// Rva0021F876. Element stays size-free with a declared-only dtor so the
// vector call binds the rowed non-trivial Destroy shape.
#include "ascii_string.h"
#include <vector>

struct BfmePod216 { public: ~BfmePod216(); };

class Rva0021F876
{
public:
	~Rva0021F876();
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	_STL::vector<BfmePod216, _STL::allocator<BfmePod216> > m_14;
};

Rva0021F876::~Rva0021F876()
{
}
