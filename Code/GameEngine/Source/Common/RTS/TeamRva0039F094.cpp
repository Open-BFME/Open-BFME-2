// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0039F094@Team@@QAEXVAsciiString@@@Z @0x0039F094 62B
// Team AsciiString setter by value. Loads +0x30 inner then sets AsciiString
// at +0x318 from the by-value param at [ebp+8] via rowed StringBase set
// 0x000366F0 with EH states 0 then -1 and releaseBuffer 0x00036410.
// Caller at 0x003BEDD1 proves Team ecx with a copied AsciiString temp.
// Evidence: ret 4 thiscall; EH prolog; [ecx+0x30] null check.
#include "ascii_string.h"

struct TeamRvaInner
{
	char m_pad00[0x318];
	AsciiString m_str318;
};

class Team
{
public:
	void rva0039F094(AsciiString name);
private:
	unsigned char m_pad00[0x30];
	TeamRvaInner *m_ptr30;
};

void Team::rva0039F094(AsciiString name)
{
	TeamRvaInner *inner = m_ptr30;
	if (inner) {
		AsciiString &slot = inner->m_str318;
		((StringBase<char> *)&slot)->set(*(const StringBase<char> *)&name);
	}
}
