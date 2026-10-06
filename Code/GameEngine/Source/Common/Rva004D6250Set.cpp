// cl: /O1 /Oy- /MD /EHsc
// Rva004D632D::rva004D6250, retail 0x004D6250 (89B):
// AsciiString setter on Rva004D632D: converts the by-value argument via
// GameState::realMapPathToPortableMapPath then assigns into the +0x1c member
// via the rowed StringBase<char>::set 0x000366F0 (AsciiString::operator= is
// inline here, which also gives retail's member-address-first order); temp
// and parameter destroyed via rowed
// releaseBuffer 0x00036410. Reverse of the 0x004D632D getter.
// Evidence: callers 0x004D19D4 0x004D2E21 plus TheGameState 0x009FF08C.
#pragma optimize("sy", on)
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

#pragma optimize("", on)
class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
};
extern GameState *TheGameState;
class Rva004D632D
{
public:
	void rva004D6250(AsciiString s);
private:
	char m_pad[0x1c];
	AsciiString m_str1c;
};
void Rva004D632D::rva004D6250(AsciiString s)
{
	m_str1c = TheGameState->realMapPathToPortableMapPath(s);
}
