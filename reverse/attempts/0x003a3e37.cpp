// ?rva003A3E37@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
// ?rva003A3E37@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z @0x003A3E37 61B
#include "ascii_string.h"

class TeamPrototype
{
public:
	char m_pad00[0x18];
	unsigned char m_flag18;
	char m_pad19[0x334 - 0x19];
	TeamPrototype *m_inst334;
};

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
	TeamPrototype *rva003A3B7E(const AsciiString &a, const AsciiString &b);
	TeamPrototype *rva003A3E37(const AsciiString &a1, const AsciiString &a2);
};

TeamPrototype *Rva0039FE6COwner::rva003A3E37(const AsciiString &a1, const AsciiString &a2)
{
	TeamPrototype *proto = findPrototype(a1, a2);
	if (proto != 0) {
		if (proto->m_inst334 != 0)
			return proto->m_inst334;
		if (proto->m_flag18 & 1)
			return 0;
		return rva003A3B7E(a1, a2);
	}
	return 0;
}
