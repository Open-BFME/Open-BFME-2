// ?rva005DE926@Rva005DE5B5@@QAEXXZ
// partial score=0.9 date=2026-10-04
// ?rva005DE926@Rva005DE5B5@@QAEXXZ
// cl: /Ireference/shims/stlport_stringrecord_5ddd40 /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Rva005DE5B5::rva005DE926, retail 0x005DE926, 44B. Erases every element of the
// vector<BfmeStringRecord005DDD40> at +0x04, resizes it back to the count it
// held (destroy-range call then the resize helper at 0x005DE84E) and clears the
// byte at +0x14. Callers are the range-apply helpers at 0x005DE96B/0x005DD6D5,
// which pass this address as a per-element function pointer.
//
// Two things the previous banked body got wrong, both load-bearing:
//  - It was pseudo-code, not compilable C++: `struct Rva005DE5B5;` was left
//    forward-declared, so m_04/m_14 had no declaration and `m_04.erase` had no
//    class type. The 44B it claimed was never emitted by any compiler.
//  - Its struct put the flag byte at +0x10; retail stores it at +0x14
//    (mov BYTE PTR [ebx+0x14],0). The 4 pad bytes at +0x10 restore that.
//
// The `// stlport` marker is required, not decorative: source_needs_stlport()
// keys the whole vendor/stlport include path off that line, and without it
// <vector> resolves to the MSVC STL where _STL does not exist.
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
	void rva005DE926();
private:
	UnicodeString m_00;
	_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > m_04;
	char m_10[4];
	unsigned char m_14;
};

void Rva005DE5B5::rva005DE926()
{
	BfmeStringRecord005DDD40 *first = m_04.begin();
	BfmeStringRecord005DDD40 *last = m_04.end();
	unsigned int count = m_04.size();
	m_04.erase(m_04.begin(), m_04.end());
	m_04.resize(count);
	m_14 = 0;
}