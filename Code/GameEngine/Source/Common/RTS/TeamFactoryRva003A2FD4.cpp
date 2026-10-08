// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7
// ?initTeamForTacticalAI@TeamFactory@@QAEPAURva003A2FD4Proto@@ABVAsciiString@@PAXHI@Z @0x003A2FD4 116B: TeamFactory free prototype search and reinit.
// Evidence: chain from just-landed 0x003A2C0D reset; callers unclaimed plus TeamFactoryXfer; callees nameToKey 0x0009FA65 row, findPlayerWithNameKey 0x002A7A41 row, reset 0x003A2C0D row; TheNameKeyGenerator 0x009F36A4, ThePlayerList 0x009FEEE8; array +0x10 size 0x28 to map +0xB0, +0x2c4/+0x2d8 stores, +0x31e/+0x31c flags.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Player;
class Dict;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
extern PlayerList *ThePlayerList;

class TeamPrototype
{
public:
	void rva003A2C0D(Player *owner, const AsciiString &ownerName, bool singleton, Dict *dict);

public:
	char m_pad00[0x2c4];
	int m_2c4; // +0x2c4
	char m_pad2c8[0x2d8 - 0x2c8];
	int m_2d8; // +0x2d8
	char m_pad2dc[0x31c - 0x2dc];
	unsigned char m_31c; // +0x31c
	unsigned char m_31d; // +0x31d
	unsigned char m_31e; // +0x31e
};

struct Rva003A2FD4Proto;

class TeamFactory
{
public:
	Rva003A2FD4Proto *initTeamForTacticalAI(const AsciiString &a1, void *a2, int a3, unsigned int a4);

private:
	char m_pad00[0x10];
	TeamPrototype *m_slots[0x28]; // +0x10
};

Rva003A2FD4Proto *TeamFactory::initTeamForTacticalAI(const AsciiString &a1, void *a2, int a3, unsigned int a4)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)a2);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	for (unsigned int i = 0; i < 0x28; ++i)
	{
		TeamPrototype *cur = m_slots[i];
		if (cur->m_31e == 0)
		{
			cur->rva003A2C0D(player, a1, false, 0);
			cur->m_2c4 = a3;
			cur->m_2d8 = (int)a4;
			cur->m_31e = 1;
			cur->m_31c = 1;
			return (Rva003A2FD4Proto *)cur;
		}
	}
	return 0;
}
