// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0032A438@Rva0032A438@@QAEXVAsciiString@@@Z @0x0032A438 52B.
// AsciiString by-value setter: copies the by-value AsciiString at [ebp+8]
// into the AsciiString at +0x04 through pin-only ??4AsciiString 0x000366F0,
// then destroys the by-value copy via rowed releaseBuffer 0x00036410.
// EH prolog via rowed __EH_prolog 0x00629188 with state 0 around the assign.
// Evidence: add ecx,4 fixes the member at +4; callers at 0x0032CF16,
// 0x0032F22D, 0x0032F6BC; recipe twin is Rva0050BFFDSet.cpp (49B at +0x00,
// +3B add here = 52B); lea/add/push order via AsciiString &slot.
class AsciiString;
#include "ascii_string.h"
class Rva0032A438
{
public:
	void rva0032A438(AsciiString s);
private:
	int m_00;
	AsciiString m_04;
};
void Rva0032A438::rva0032A438(AsciiString s)
{
	AsciiString &slot = m_04;
	slot = s;
}
