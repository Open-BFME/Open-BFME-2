// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// ??1Rva002E5711@@QAE@XZ 0x002E5711 8B
// Evidence: add ecx 4 plus jmp to rowed releaseBuffer 0x00036E70;
// callers 0x002E5D46 0x002E6551; non-virtual dtor over Unicode member at +4.
#include "unicode_string.h"

class Rva002E5711
{
public:
	~Rva002E5711();

private:
	char m_pad[4];
	UnicodeString m_text;
};

Rva002E5711::~Rva002E5711()
{
}
