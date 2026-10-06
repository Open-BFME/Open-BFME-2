// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
// ?rva005B947D@Rva005B922F@@QAEXHHH@Z @0x005B947D 104B
// Ticker formatted row: formats m_64's text plus two ints through rowed
// UnicodeString::format with fmt at VA 0x00C73BD0, then sets it under the
// index through rowed rva005B9378. Evidence: member +0x64 (UnicodeString
// m_64 in Rva005B922F dtor TU), TheNullChr fallback at VA 0x00BBB5C4,
// callees rowed format/rva005B9378/releaseBuffer, 6 callers in 0x005B95B8.
class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
};

extern const unsigned short g_00C73BD0[];

class Rva005B922F
{
public:
	void rva005B947D(int index, int a, int b);
private:
	char m_pad[0x64];
	UnicodeString m_64;	// +0x64
};

void Rva005B922F::rva005B947D(int index, int a, int b)
{
	UnicodeString tmp;
	tmp.format(g_00C73BD0, a, m_64.str(), b);
	((Rva005B9378 *)this)->rva005B9378(index, tmp);
}
