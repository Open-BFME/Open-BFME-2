// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport

// ??1Rva005DE5B5@@QAE@XZ, RVA 0x005DE5B5, 53B.
// Unlock lane: all callees rowed (vector dtor 0x005DE47B,
// releaseBuffer 0x00036E70, __EH_prolog). Callers at 0x005DE785/
// 0x005DE8B7/0x005DE95B plus jmp at 0x005DE7CC and Unwind funclet.
// Non-virtual dtor destroying vector at +4 then UnicodeString at +0
// (reverse declaration order) under the shipped EH state.
// UnicodeString, BfmeStringRecord and vector models are the neighbour
// TU's (stlport_vector_stringrecord_5ddd40_allocate_copy.cpp) verbatim
// so the member dtor calls land on the rowed bodies.

#include <float.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
struct BfmeStringRecord005DDD40 {
    UnicodeString text;
    // Native updater5DDB66 uses MOVSS/COMISS on source+4. Low-level
    // copy/assignment providers preserve these four bits without conversion.
    float word;
    BfmeStringRecord005DDD40();
    BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &);
    BfmeStringRecord005DDD40 &operator=(const BfmeStringRecord005DDD40 &);
    // Implicit cleanup owns only text and expands to wide releaseBuffer.
    // An out-of-line record destructor would create non-retail Destroy copies.
};
namespace _STL {
template <> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
// Consume the full rowed63B destructor from the vector home. Canonical
// inline string cleanup otherwise emits a59B EH variant in this consumer.
template <> vector<BfmeStringRecord005DDD40, allocator<BfmeStringRecord005DDD40> >::~vector();
}

class Rva005DE5B5
{
public:
	~Rva005DE5B5();
	Rva005DE5B5(const Rva005DE5B5 &other);
	Rva005DE5B5();
	void setValueRva005DDB66(unsigned,const BfmeStringRecord005DDD40&,bool);
	void *rva005DE782(unsigned int flags);

private:
	UnicodeString m_00;
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > m_04;
	float m_10;
	unsigned char m_14;
};

Rva005DE5B5::~Rva005DE5B5()
{
}

// Retail 0x005DE56C (73B): Rva005DE5B5 copy ctor. Chain lane: StringBase
// copy 0x00037050 at +0, vector copy ctor 0x005DE0A3 at +4, dword at
// +0x10, byte at +0x14. Total size 0x18, matching the Destroy stride.
// Caller is 0x005DE771 in 0x005DE755.
Rva005DE5B5::Rva005DE5B5(const Rva005DE5B5 &other)
	: m_00(other.m_00), m_04(other.m_04), m_10(other.m_10), m_14(other.m_14)
{
}

// Retail 0x005DE755 (45B): _STL::_Construct<Rva005DE5B5> null-guarded
// placement copy-construct. Chain lane: callee is the just-landed copy
// ctor 0x005DE56C. Caller is 0x005DE7B6 in 0x005DE7A3.
namespace _STL {
template void _Construct<Rva005DE5B5, Rva005DE5B5>(Rva005DE5B5 *, const Rva005DE5B5 &);
}

// Retail 0x005DE952 (25B): destroy range calling the 0x005DE5B5 dtor per
// 0x18-byte element from start (inclusive) to end (exclusive). Chain lane:
// callee is the just-landed dtor; caller is 0x005DE99F in 0x005DE985.
void Rva005DE952Destroy(Rva005DE5B5 *start, Rva005DE5B5 *end)
{
	for (; start != end; start = (Rva005DE5B5 *)((char *)start + 0x18))
		start->~Rva005DE5B5();
}

void operator delete(void *ptr);

// Retail 0x005DE782 (28B): flag-guarded teardown calling the 0x005DE5B5
// dtor then operator delete, returning this. Chain lane: callees are
// the just-landed dtor plus rowed operator delete 0x0002FD60. Owner
// proven by the dtor call with this; honest address-derived method name
// (non-virtual class, so not a ??_G).
void *Rva005DE5B5::rva005DE782(unsigned int flags)
{
	this->~Rva005DE5B5();
	if (flags & 1)
		::operator delete(this);
	return this;
}

// __uninitialized_fill_n<Rva005DE5B5> (retail 0x005DE7A3, 37B): byte-identical
// fill loop through the rowed _Construct 0x005DE755.
template Rva005DE5B5 *_STL::__uninitialized_fill_n<Rva005DE5B5 *, unsigned int, Rva005DE5B5>(
	Rva005DE5B5 *, unsigned int, const Rva005DE5B5 &, const _STL::__false_type &);

// Native constructor [5DE5EA,5DE651),103B belongs to the same24B
// owner as full73B copy5DE56C and53B destructor5DE5B5. Initialize
// UnicodeString from narrow "-" via full91B conversion6CB6D0;
// construct empty vector at4 via full29B base211E58; initialize
// nativefloat10=-FLT_MAX and byte14=false. Native69B updater5DDB66
// independently proves float10 and dirty14 roles. Original owner name
// remains unknown. Shared canonical string headers reconcile the prior
// per-unit views; all existing rows must still pass after that change.
Rva005DE5B5::Rva005DE5B5() : m_00(AsciiString("-")),m_04(),m_10(-FLT_MAX),m_14(false) {}


// Native Ghidra [5DDB66,5DDBAB),69B; index bounds on vector4;
// full31B record assignment5DD6B6 followed by dirty14=true and optional
// maximum10 update. Float loads/comparison independently type source+4
// and owner+10; original method name remains unknown. Canonical vector
// access preserves the target's index register and base/index LEA ordering.
void Rva005DE5B5::setValueRva005DDB66(unsigned index,const BfmeStringRecord005DDD40&src,bool update) {
 if(index>=m_04.size())return;
 m_04[index]=src;
 m_14=true;
 if(update) {
  float value=src.word;
  if(value>m_10)m_10=value;
 }
}
