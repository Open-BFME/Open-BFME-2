// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva004D6187@Rva004D60CA@@QAEXVUnicodeString@@@Z @0x004D6187 (52B):
// Wide-string setter on Rva004D60CA (ZH's NetChatCommandMsg::setText): copies
// the by-value argument into the +0x1c UnicodeString member via pin-only set
// 0x00037150, then destroys the parameter via rowed releaseBuffer 0x00036E70
// (inlined dtor, EH state).
// Evidence: caller 0x004D187B builds esi with Rva004D60CA ctor 0x004D60CA
// then calls this with a wide-string temp; callers 0x004D17C5 etc. Its two
// source callers (NetPacket.cpp, ConnectionManager_sendChat.cpp) declare the
// UnicodeString parameter, so the definition uses the shared UnicodeString and
// the link resolves both.
#include "unicode_string.h"

class Rva004D60CA
{
public:
	void rva004D6187(UnicodeString text);
private:
	char m_pad00[0x1c];
	UnicodeString m_str1c;
};

void Rva004D60CA::rva004D6187(UnicodeString text)
{
	// set() through the base: UnicodeString::operator= would leave an out-of-line
	// COMDAT copy in this object that is not retail's body.
	StringBase<unsigned short> &slot = m_str1c;
	slot.set(text);
}
