// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva003A3E37@Rva0039FE6COwner@@QAEPAVTeam@@ABVAsciiString@@0@Z @0x003A3E37
// 61B: the Zero Hour TeamFactory::findTeam shape. The rowed findPrototype
// (0x0039FE6C) looks the prototype up; its first team instance (+0x334) is
// returned, and when there is none and the prototype is not a singleton
// (+0x18 bit 0) the rowed TeamFactory::createInactiveTeam (0x003A3B7E, WB
// name) makes one; no prototype gives NULL.
// Target facts: retail returns the +0x334 value itself (it stays in eax
// through the singleton test), which is why the result is a Team rather
// than the prototype the banked attempt returned. The receiver keeps its
// address-derived class name from the findPrototype row.
#include "ascii_string.h"

class Team;

class TeamPrototype
{
public:
	Team *getFirstItemIn_TeamInstanceList() const { return m_firstTeam; }
	__declspec(dllimport) __forceinline bool getIsSingleton() const { return (m_flags & 1) != 0; }

private:
	char m_pad00[0x18];
	unsigned char m_flags; // +0x18
	char m_pad19[0x334 - 0x19];
	Team *m_firstTeam; // +0x334
};

class TeamFactory
{
public:
	Team *createInactiveTeam(const AsciiString &name, const AsciiString &owner);
};

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
	Team *rva003A3E37(const AsciiString &a1, const AsciiString &a2);
};

Team *Rva0039FE6COwner::rva003A3E37(const AsciiString &a1, const AsciiString &a2)
{
	TeamPrototype *tp = findPrototype(a1, a2);
	if (tp)
	{
		Team *t = tp->getFirstItemIn_TeamInstanceList();
		if (t == 0 && !tp->getIsSingleton())
			t = ((TeamFactory *)this)->createInactiveTeam(a1, a2);
		return t;
	}
	return 0;
}
