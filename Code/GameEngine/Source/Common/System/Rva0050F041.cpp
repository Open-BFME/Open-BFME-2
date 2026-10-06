// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0050F041@Rva0050F041@@QAEXHABVUnicodeString@@@Z, retail 0x0050F041, 106 bytes.
// If m_60 null use empty at 0x007BAC1C else +8 name; format m_5c plus mid plus
// field via AsciiString::format APT:_level%u.%s_field%d into local key and
// bfmeSetText(key text false) on global 0x009FE4CC. Evidence: format 0x00038150
// bfmeSetText pin 0x00225301 releaseBuffer 0x00036410; callers 0x0050F37E
// 0x0050FCC1; precedent Rva005FDF1CApt donor same callees globals.
// Sibling of 0x0050F0AB chain.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


#include "unicode_string.h"

struct Rva0050F041Inner
{
	char m_pad8[8];
	char m_name[1];
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva0050F041
{
public:
	void rva0050F041(int field, const UnicodeString &text);
private:
	char m_pad00[0x5c];
	int m_5c;
	Rva0050F041Inner *m_60;
};

void Rva0050F041::rva0050F041(int field, const UnicodeString &text)
{
	AsciiString key;
	const char *mid = m_60 ? m_60->m_name : "";
	key.format("APT:_level%u.%s_field%d", m_5c, mid, field);
	g_bfmeAptWindowManager->bfmeSetText(key, text, false);
}
