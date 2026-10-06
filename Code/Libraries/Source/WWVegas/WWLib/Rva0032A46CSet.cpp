// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0032A46C@Rva0032A46C@@QAEXVAsciiString@@@Z @0x0032A46C 52B.
// AsciiString by-value setter: copies the by-value AsciiString at [ebp+8]
// into the AsciiString at +0x30 through pin-only ??4AsciiString 0x000366F0,
// then destroys the by-value copy via rowed releaseBuffer 0x00036410.
// EH prolog via rowed __EH_prolog 0x00629188 with state 0 around the assign.
// Evidence: add ecx,0x30 fixes the member at +0x30; callers at 0x0032CFAA,
// 0x0032F2B9; recipe twin is Rva0032A438Set.cpp (?rva0032A438, +0x04) and
// Rva0050BFFDSet.cpp (49B at +0x00); lea/add/push order via AsciiString &slot.
class AsciiString;
#include "ascii_string.h"
class Rva0032A46C
{
public:
	void rva0032A46C(AsciiString s);
private:
	char m_pad[48];
	AsciiString m_30;
};
void Rva0032A46C::rva0032A46C(AsciiString s)
{
	AsciiString &slot = m_30;
	slot = s;
}
