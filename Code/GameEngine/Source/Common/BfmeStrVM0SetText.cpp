// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0025D358@BfmeStrVM0@@QAEXVUnicodeString@@MMHHH@Z, retail 0x0025D358, 112 bytes.
// Sets the +0xB0 display block: Unicode string via set plus ints at +0xB4/+0xB8/+0xBC
// and floats at +0xC0/+0xC4; the by-value string is released at the end.
// Evidence: same +0xB0/+0xD0/+0xF0 layout as the dtor 0x0025D686 (BfmeStrVM0Dtor.cpp)
// and ctor 0x0025D489; callees rowed StringBase<G>::set 0x00037150 and
// releaseBuffer 0x00036E70. The parameter is a UnicodeString: the only caller,
// 0x00356AC1 (Rva003560EDEngineRefresh.cpp), passes a UnicodeString copy of the
// fetched "GUI:Loading" text. Moved out of BfmeStrVM0Dtor.cpp, whose private
// StringBase view cannot spell UnicodeString (the canonical header owns it).
#include "unicode_string.h"

class BfmeStrVM0
{
public:
	void rva0025D358(UnicodeString s, float fC0, float fC4, int iB4, int iB8, int iBC);
private:
	char m_pad00[0xB0];
	UnicodeString m_sB0;
	int m_iB4;
	int m_iB8;
	int m_iBC;
	float m_fC0;
	float m_fC4;
};

void BfmeStrVM0::rva0025D358(UnicodeString s, float fC0, float fC4, int iB4, int iB8, int iBC)
{
	StringBase<unsigned short> &dst = m_sB0;
	dst.set(s);
	m_iB4 = iB4;
	m_iB8 = iB8;
	m_iBC = iBC;
	m_fC0 = fC0;
	m_fC4 = fC4;
}
