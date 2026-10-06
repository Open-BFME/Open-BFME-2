// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ??1Rva00574499@@QAE@XZ, retail 0x00574499, 68 bytes.
// Evidence: EH prolog unwind states 1..0 tear down two strings at +0x0C down to +0x08
// through the folded string release 0x00036410, then state -1 destroys the
// subobject at +0 through pinned 0x0022167C; deleting-dtor caller at 0x00574B4C
// proves ??1 identity; layout follows sibling Rva005CB3BE dtor precedent.

#include "string_base.h"

#include "ascii_string.h"

class Rva0022167C
{
public:
	~Rva0022167C();

private:
	char m_bytes[8];
};

class Rva00574499
{
public:
	~Rva00574499();

private:
	Rva0022167C m_at00;
	AsciiString m_at08;
	AsciiString m_at0c;
};

Rva00574499::~Rva00574499()
{
}
