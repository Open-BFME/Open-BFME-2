// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva0033269B@Rva0033269B@@QAEXABUBfmeStringRecord000331962@@@Z @0x0033269B 115B
// retail 0x0033269B, 115 bytes. Searches the vector<BfmeStringRecord000331962>
// at +8 for rec.word; on a hit assigns rec.text over the stored text via the
// pinned AsciiString::operator= 0x366F0, else push_backs rec via the rowed
// 0x332568 and clears the flag byte at +4. Layout matches the Rva003371B1
// 20-byte (AsciiString, flag, vector) model; owner class unproven so this TU
// uses the honest address class Rva0033269B.

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"

struct BfmeStringRecord000331962
{
	~BfmeStringRecord000331962();
	unsigned int word;
	AsciiString text;
	unsigned char flag;
};

class Rva0033269B
{
public:
	void rva0033269B(const BfmeStringRecord000331962 &rec);

private:
	AsciiString m_str;
	bool m_flag;
	unsigned char m_pad05[3];
	_STL::vector<BfmeStringRecord000331962> m_vec;
};

void Rva0033269B::rva0033269B(const BfmeStringRecord000331962 &rec)
{
	for (unsigned int i = 0; i < m_vec.size(); ++i)
	{
		if (m_vec[i].word == rec.word)
		{
			m_vec[i].text = rec.text;
			return;
		}
	}
	m_vec.push_back(rec);
	m_flag = false;
}
