// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// ?rva004D05D7@Rva004D05D7@@QAEXVUnicodeString@@@Z @0x004D05D7 52B: UnicodeString assign to +0x24 via set.
// Evidence: rowed set 0x00037150 plus rowed releaseBuffer 0x00036E70 plus caller 0x005922CD; neighbours StringRecordCopy.
#include "unicode_string.h"

class __declspec(novtable) Rva004D05D7
{
public:
	void rva004D05D7(UnicodeString s);
private:
	char m_pad[0x24];
	UnicodeString m_24;
};

void Rva004D05D7::rva004D05D7(UnicodeString s)
{
	m_24 = s;
}
