// cl: /DNDEBUG /MD /O1 /Ireference/shims/bfme2_ascii
// ?Rva00528C30Get@@YA_NPBDAAVAsciiString@@@Z @0x00528C30 27B: GetParam wrapper with literal name plus bool normalize. Evidence: string name plus pinned GetParam 0x4128F0 row plus 3 callers 0x529698 0x5297DD 0x52991E.
#include "ascii_string.h"
bool __cdecl Rva004128F0GetParam(char const *a, char const *b, AsciiString &c);
bool __cdecl Rva00528C30Get(char const *a, AsciiString &b)
{
	unsigned char r = Rva004128F0GetParam(a, "name", b);
	return r;
}
