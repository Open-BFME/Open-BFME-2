// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva0022181D@@QAE@XZ @0x0022181D 61B
// Default ctor: three AsciiStrings at +0 +4 +8 defaulted plus FontDesc at +0xC via rowed
// ctor 0x00376900 plus int at +0x18 set to -1. Member at +0xC of outer ctor
// 0x00222061 which also builds map at +0x28. Layout from retail bytes.
// Evidence: retail bytes and caller 0x00222061 plus rowed FontDesc ctor.
#include "ascii_string.h"

struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;
	FontDesc();
};

class Rva0022181D
{
public:
	Rva0022181D();
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	FontDesc m_0C;
	int m_18;
};

Rva0022181D::Rva0022181D()
	: m_00()
	, m_04()
	, m_08()
	, m_0C()
	, m_18(-1)
{
}
