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
	NameKeyType nameToKey(const AsciiString &nameString);
	const AsciiString &keyToName(NameKeyType);
	NameKeyType nameToKey(const char *name);
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

// The two tactic slots of the prototype's team template (+0x12C), as the
// Team.cpp seed's TeamTemplateInfo spells them (+0x198 and +0x1AC there).
struct TeamTemplateTacticView
{
	char m_pad000[0x198];
	int m_targetID; // prototype +0x2C4, the target id
	char m_pad19C[0x1AC - 0x19C];
	int m_tacticID; // prototype +0x2D8, the tactic id
};

class TeamPrototype
{
public:
	void rva003A2C0D(Player *owner, const AsciiString &ownerName, bool singleton, Dict *dict);

public:
	char m_pad00[0x12c];
	TeamTemplateTacticView m_teamTemplate; // +0x12c
	char m_pad2dc[0x31c - 0x2dc];
	bool m_byte31C; // +0x31c
	bool m_byte31D; // +0x31d
	bool m_byte31E; // +0x31e
};

struct Rva003A2FD4Proto;

class TeamFactory
{
public:
	Rva003A2FD4Proto *initTeamForTacticalAI(const AsciiString &a1, void *ownerName, int targetID, unsigned int tacticID);

private:
	char m_pad00[0x10];
	TeamPrototype *m_dummyTeams[0x28]; // +0x10
};

Rva003A2FD4Proto *TeamFactory::initTeamForTacticalAI(const AsciiString &asciiString, void *ownerName, int targetID, unsigned int tacticID)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)ownerName);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	for (unsigned int i = 0; i < 0x28; ++i)
	{
		TeamPrototype *cur = m_dummyTeams[i];
		if (cur->m_byte31E == 0)
		{
			cur->rva003A2C0D(player, asciiString, false, 0);
			cur->m_teamTemplate.m_targetID = targetID;
			cur->m_teamTemplate.m_tacticID = (int)tacticID;
			cur->m_byte31E = 1;
			cur->m_byte31C = 1;
			return (Rva003A2FD4Proto *)cur;
		}
	}
	return 0;
}
