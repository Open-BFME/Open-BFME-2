// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002120C2@Rva002120A4@@QAEPAURva002120C2Entry@@ABVAsciiString@@@Z, retail 0x002120C2 (86 bytes, ret 4).
// Same class as the rowed Rva002120A4 (0x002120A4, NameKey map at +0x218): the pointer vector at
// +0x24C/+0x250, first entry whose AsciiString at +0x1C equals the name, else null. WorldBuilder twin
// 0x00B60C60 is unnamed, so the method keeps its address token.
#include <vector>
#include "ascii_string.h"

struct Rva002120C2Entry
{
	char m_pad00[0x1C];
	AsciiString m_name;		// +0x1C
};

class Rva002120A4
{
public:
	Rva002120C2Entry *rva002120C2(const AsciiString &name);

private:
	unsigned char m_pad[0x24C];
	_STL::vector<Rva002120C2Entry *> m_entries;	// +0x24C
};

Rva002120C2Entry *Rva002120A4::rva002120C2(const AsciiString &name)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i) {
		if (m_entries[i]->m_name.compare(name) == 0)
			return m_entries[i];
	}
	return 0;
}
