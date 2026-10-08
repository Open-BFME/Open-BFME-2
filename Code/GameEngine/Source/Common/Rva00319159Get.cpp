// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00319159@Rva00319159@@QAEPAXXZ @0x00319159 33B via AsciiString empty check plus global lookup
// ?rva0031964D@Rva00319159@@QAE?AVUnicodeString@@XZ @0x0031964D 61B via empty AsciiString returns TheEmptyString else record+0x30 copy
// Evidence: unlock lane callers 0x002B3A71 0x00319666; rowed isEmpty StringBase and rowed rva002D06CA via g_009FF000; AsciiString at +0x18
#include "ascii_string.h"
#include "unicode_string.h"
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;
class Rva00319159
{
public:
	void *rva00319159();
	UnicodeString rva0031964D();
private:
	char m_pad[24];
	AsciiString m_str;
};

void *Rva00319159::rva00319159()
{
	if (m_str.isEmpty())
		return 0;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&m_str);
}

UnicodeString Rva00319159::rva0031964D()
{
	if (m_str.isEmpty())
		return UnicodeString::TheEmptyString;
	void *p = rva00319159();
	if (!p)
		return UnicodeString::TheEmptyString;
	return *(const UnicodeString *)((const char *)p + 0x30);
}
