// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// ??0Rva005D3731@@QAE@IABVAsciiString@@@Z @0x005D36D1 96B (ret 8). Constructor
// of the region-name tray object Rva005D2FD0Apt.cpp holds the dtor (0x005D3731)
// and cached-text compare (0x005D3846) of: level at +0, a copy of the movie
// clip name at +4, the 12-byte chain object at +8 (default ctor, folded at
// 0x001F81BF), +0x14 cleared, the cached wide text at +0x18 default, the guard
// byte at +0x1C clear, then the empty region name is pushed through
// StrategicHUD::SetRegionNameString (0x005D366A). Identity per that file.
#include "ascii_string.h"
#include "unicode_string.h"

namespace StrategicHUD
{
	void SetRegionNameString(unsigned int level, const AsciiString &clipName, const UnicodeString &text);
}

class Rva005242D7
{
public:
	Rva005242D7();
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva005D3731
{
public:
	Rva005D3731(unsigned int level, const AsciiString &clipName);
	~Rva005D3731();
private:
	unsigned int m_00;
	AsciiString m_04;
	Rva005242D7 m_08;
	int m_14;
	UnicodeString m_18;
	bool m_1C;
};

Rva005D3731::Rva005D3731(unsigned int level, const AsciiString &clipName)
	: m_00(level), m_04(clipName), m_08(), m_14(0), m_18(), m_1C(false)
{
	StrategicHUD::SetRegionNameString(m_00, m_04, m_18);
}
