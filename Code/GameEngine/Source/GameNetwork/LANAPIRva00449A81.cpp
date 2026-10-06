// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva00449A81@LANAPI@@QAEXVUnicodeString@@@Z @0x00449A81 55B evidence: unlock lane; this+0xF64 UnicodeString set from by-value param; StringBase<G>::set 0x37150 releaseBuffer 0x36E70 EH_prolog; neighbours LANAPISetIsActive LANAPIGetMyName
#include "unicode_string.h"

class LANAPI
{
public:
	void rva00449A81(UnicodeString s);
private:
	unsigned char m_pad00[0xF64];
	UnicodeString m_F64;
};

void LANAPI::rva00449A81(UnicodeString s)
{
	UnicodeString &slot = m_F64;
	slot.set(s);
}
