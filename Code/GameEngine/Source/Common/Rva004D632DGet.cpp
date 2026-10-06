// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva004D632D@Rva004D632D@@QBE?AVAsciiString@@XZ @0x004D632D (33B):
// AsciiString value forwarder: returns TheGameState->portableMapPathToRealMapPath
// of the +0x1c member. Retail lea via add ecx,0x1c; push member; push hidden
// return; ecx is TheGameState from VA 0x009FF08C; call pin-only
// ?portableMapPathToRealMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z @0x002DC9F7.
// Callers 0x004D2B30/0x004D2B7D/0x004D2CB1. Honest-address name.

#include "ascii_string.h"

class GameState
{
public:
	AsciiString portableMapPathToRealMapPath(const AsciiString &in) const;
};

extern GameState *TheGameState;

class Rva004D632D
{
public:
	AsciiString rva004D632D() const;

private:
	char m_pad[0x1c];
	AsciiString m_str1c;
};

AsciiString Rva004D632D::rva004D632D() const
{
	return TheGameState->portableMapPathToRealMapPath(m_str1c);
}
