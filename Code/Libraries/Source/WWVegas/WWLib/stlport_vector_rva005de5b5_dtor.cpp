// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

// ??1?$vector@VRva005DE5B5@@V?$allocator@VRva005DE5B5@@@_STL@@@_STL@@QAE@XZ, RVA 0x005DE985, 63B.
// Chain lane: every callee resolved (Destroy range 0x005DE952, _free
// 0x00030830, __EH_prolog). Same 63B EH shape as the sibling
// vector<BfmeStringRecord005DDD40> dtor at 0x005DE47B (same funclet
// 0x007A2E5B); caller is the vtable-setting dtor at 0x005DE9E3 which
// tail-jmps here after add ecx,4. Models are the neighbour TU's
// (stlport_vector_stringrecord_5de5b5_dtor.cpp) verbatim so the Destroy
// call lands on the rowed 0x005DE952 body.

#include "unicode_string.h"
#include <vector>
struct BfmeStringRecord005DDD40 {
    UnicodeString text;
    unsigned int word;
    BfmeStringRecord005DDD40();
    BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &);
    BfmeStringRecord005DDD40 &operator=(const BfmeStringRecord005DDD40 &);
};
namespace _STL {
template <> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
}

class Rva005DE5B5
{
public:
	~Rva005DE5B5();
	void *rva005DE782(unsigned int flags);

private:
	UnicodeString m_00;
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > m_04;
};

// Retail 0x005DE985 (63B): _STL::vector<Rva005DE5B5> dtor, Destroy range
// 0x005DE952 plus _free.
template _STL::vector<Rva005DE5B5, _STL::allocator<Rva005DE5B5> >::~vector();

// Retail 0x005DE9E3 (18B): Rva005DE9E3::~Rva005DE9E3. Chain lane: stores
// vtable 0x00876AFC, zeroes +0x10, tail-jmps the vector base dtor at +4.
// Caller is the deleting dtor at 0x005DF144; vtable proves virtual dtor.
class Rva005DE9E3 : public _STL::vector<Rva005DE5B5, _STL::allocator<Rva005DE5B5> >
{
public:
	virtual ~Rva005DE9E3();
private:
	int m_10;
};

Rva005DE9E3::~Rva005DE9E3()
{
	m_10 = 0;
}
