// cl: /MD /EHsc /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ??0Rva00420977@@QAE@XZ @0x00420977 (52B). Address-derived identity: called
// by 0x00420A29. Target layout inference: AsciiString at +0, four zeroed words
// at +0x24, and six words initialized to 10 at +0x34.
class Rva00420977
{
public:
	Rva00420977();
private:
	AsciiString m_name;
	unsigned char m_pad[0x24 - sizeof(AsciiString)];
	unsigned int m_zero24;
	unsigned int m_zero28;
	unsigned int m_zero2C;
	unsigned int m_zero30;
	unsigned int m_ten34;
	unsigned int m_ten38;
	unsigned int m_ten3C;
	unsigned int m_ten40;
	unsigned int m_ten44;
	unsigned int m_ten48;
};
Rva00420977::Rva00420977()
	: m_name(""), m_zero24(0), m_zero28(0), m_zero2C(0), m_zero30(0),
	  m_ten34(10), m_ten38(10), m_ten3C(10), m_ten40(10), m_ten44(10), m_ten48(10)
{
}
