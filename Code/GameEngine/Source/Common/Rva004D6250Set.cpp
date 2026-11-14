// cl: /Oy- /MD /EHsc
// Rva004D632D::rva004D6250, retail 0x004D6250 (89B):
// AsciiString setter on Rva004D632D: converts the by-value argument via
// GameState::realMapPathToPortableMapPath then assigns into the +0x1c member
// via the rowed StringBase<char>::set 0x000366F0 (AsciiString::operator= is
// inline here, which also gives retail's member-address-first order); temp
// and parameter destroyed via rowed
// releaseBuffer 0x00036410. Reverse of the 0x004D632D getter.
// Evidence: callers 0x004D19D4 0x004D2E21 plus TheGameState 0x009FF08C.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// The narrow teardown is rowed at 0x00036410 (StringBaseWideReleaseBuffer.cpp).
template <> StringBase<char>::~StringBase();

#include "../../Include/Common/GameState.h"
extern GameState *TheGameState;
#include "../../Include/GameNetwork/Rva004D632D.h"
void Rva004D632D::rva004D6250(AsciiString s)
{
	m_str1c = TheGameState->realMapPathToPortableMapPath(s);
}
