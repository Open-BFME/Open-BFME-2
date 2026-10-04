// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /MD
// ??1Rva005FB615@@QAE@XZ @ 0x005FB615 81B
// Non-virtual dtor with members +0x28 UnicodeString +0x18 Rva005242D7 +0x0C Rva0052413E +0x08 AsciiString in reverse. Siblings share layout and flags.
#include "ascii_string.h"
#include "unicode_string.h"
class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[16];
};
class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};
class Rva005FB615
{
public:
	~Rva005FB615();
private:
	char m_pad00[8];
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
	UnicodeString m_28;
};
Rva005FB615::~Rva005FB615()
{
}
