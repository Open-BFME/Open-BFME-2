// ?rva003A3E37@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva003A3E37@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z
// @0x003A3E37 61B: findPrototype then empty-inactive fallback. Returns the
// rowed findPrototype 0x0039FE6C hit when its +0x334 list is present or its
// +0x18 bit is set, else the pinned 0x003A3B7E fallback on the same names,
// else null. Evidence: same (a1,a2) pair to both calls, straightline guards.
#include "ascii_string.h"

class TeamPrototype
{
public:
	char m_pad00[0x18];
	unsigned char m_flag18;
	char m_pad19[0x334 - 0x19];
	void *m_list334;
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
	TeamPrototype *p;
	if ((p = findPrototype(a1, a2)) != 0) {
		if (p->m_list334 != 0)
			return p;
		if (p->m_flag18 & 1)
			return p;
		return rva003A3B7E(a1, a2);
	}
	return 0;
}
