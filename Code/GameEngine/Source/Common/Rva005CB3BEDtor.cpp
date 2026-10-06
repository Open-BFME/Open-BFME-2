// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ??1Rva005CB3BE@@QAE@XZ, retail 0x005CB3BE, 116 bytes.
// Evidence: unwind states 5..0 tear down six strings at +0x1C down to +0x08
// through the folded string dtor 0x00036410, then state -1 destroys the
// subobject at +0 through 0x0022167C. That 14-byte dtor stores vtable
// 0x00BE6BA8 at +0 and tail-jumps to 0x0022161B for a member at +4, so the
// subobject is an 8-byte polymorphic object. This dtor stores no vtable of
// its own, so the subobject is a first member rather than a base. Names are
// generated; only the destructible members and their offsets are attested.

#include "string_base.h"

#include "ascii_string.h"

class Rva0022167C
{
public:
	~Rva0022167C();

private:
	char m_bytes[8];
};

class Rva005CB3BE
{
public:
	~Rva005CB3BE();

private:
	Rva0022167C m_at00;
	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	AsciiString m_at14;
	AsciiString m_at18;
	AsciiString m_at1c;
};

Rva005CB3BE::~Rva005CB3BE()
{
}
