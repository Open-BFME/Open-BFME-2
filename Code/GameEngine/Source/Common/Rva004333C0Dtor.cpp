// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva004333C0@@UAE@XZ retail 0x004333C0 62B: virtual dtor stores vtable 0x0083CB1C then releases AsciiString at +0xC8 then calls rowed base ??1Rva001DA2D5@@UAE@XZ; evidence vtable store plus callees rowed plus caller 0x004334BB deleting dtor
#include "ascii_string.h"

class Rva001DA2D5
{
public:
	virtual ~Rva001DA2D5();
private:
	char m_pad04[0xBC - 4];
};

class Rva004333C0 : public Rva001DA2D5
{
public:
	virtual ~Rva004333C0();
private:
	char m_gapBC[0xC8 - 0xBC];
	AsciiString m_strC8;
};

Rva004333C0::~Rva004333C0()
{
}
