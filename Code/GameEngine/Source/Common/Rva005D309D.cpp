// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva005D309D@@QAE@XZ @0x005D309D 81B
// Dtor with AsciiString at +4 and three Rva005D2EA8 members at +0x20 +0x38 +0x50.
// Evidence: three calls to pinned ??1Rva005D2EA8@@UAE@XZ plus releaseBuffer
// 0x00036410 for AsciiString; callers at 0x005D3291 0x005D32B6 unblock
// 0x005D32AA; layout from idei offsets and Rva005D3731 AsciiString precedent.
#include "ascii_string.h"

class Rva005D2EA8
{
public:
	virtual ~Rva005D2EA8();
private:
	char m_pad[0x14];
};

class Rva005D309D
{
public:
	~Rva005D309D();
private:
	int m_00;
	AsciiString m_04;
	char m_pad08[0x20 - 0x08];
	Rva005D2EA8 m_20;
	Rva005D2EA8 m_38;
	Rva005D2EA8 m_50;
};

Rva005D309D::~Rva005D309D()
{
}
