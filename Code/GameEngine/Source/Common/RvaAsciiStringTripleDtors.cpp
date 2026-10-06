// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Destructors of three-AsciiString records with the shape of the rowed
// GenericObjectCreationNugget::AnimSet destructor (0x001F0495, 68 bytes: release
// the strings at +8, +4 and +0 under an EH frame). The copies differ from it only
// in the EH handler record. Which records they destroy is not recovered, so
// each keeps its address.

#include "ascii_string.h"

// ??1Rva001EF50E@@QAE@XZ, retail 0x001EF50E, 68 bytes.
struct Rva001EF50E
{
	~Rva001EF50E();
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
};

Rva001EF50E::~Rva001EF50E()
{
}

// ??1Rva005FEBC8@@QAE@XZ, retail 0x005FEBC8, 68 bytes.
struct Rva005FEBC8
{
	~Rva005FEBC8();
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
};

Rva005FEBC8::~Rva005FEBC8()
{
}
