// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7
// ?rva003A2C0D@TeamPrototype@@QAEXPAVPlayer@@ABVAsciiString@@_NPAVDict@@@Z @0x003A2C0D 152B: TeamPrototype pooled-slot reinit.
// Evidence: callers 0x003A2FD4 (free-slot search 0x28, +0x31e flag) and 0x003A308A (getNthPlayer +0x20/+0x24) pass (player, name, singleton, dict); callees rva003A0CD1 row, StringBase::set row 0x000366F0, loadFromDict row 0x0039FEBB, rva003A2BD4 row; TheGameLogic extern 0x009FE78C; layout +0x10/+0x14 names, +0x18 flags, +0x320/+0x324/+0x328 from Xfer precedent.
#include "ascii_string.h"

class Dict;
class TeamTemplateInfo
{
public:
	void loadFromDict(Dict *dict);
private:
	unsigned char m_body[0x1EC];
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Team;
class TeamPrototype;
class Object;
class PlayerTemplate;
struct RetailPlayerRelationMap;
class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
	const AsciiString &getPlayerNameStr() const { return m_playerName; }
	bool rva002AA245()const;
	int getPlayerIndex() const { return m_playerIndex; }
	void addTeamToList(TeamPrototype *team);
	Relationship getRelationship(const Player *that) const;
	Relationship getRelationship(const Team *that) const;
	Relationship getRelationship(const Object *that) const;
	void removeTeamFromList(TeamPrototype *team);
	__declspec(dllimport) __forceinline const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	char m_pad00[0x34];
private:
	const PlayerTemplate *m_playerTemplate; // +0x34 +0x34
	char m_pad38[0x14];
public:
	AsciiString m_playerName; // +0x4C
	char m_pad50[0x4];
	int m_playerIndex; // +0x54
	char m_pad58[0x4];
	int m_playerType; // +0x5C +0x5C
	char m_pad60[0x28C];
	Team *m_defaultTeam; // +0x2EC
	char m_pad2F0[0x40];
	RetailPlayerRelationMap *m_playerRelations; // +0x330 +0x330
	RetailPlayerRelationMap *m_teamRelations; // +0x334 +0x334
};

#include "../GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class TeamPrototype
{
public:
	void rva003A0CD1();
	void addToLists();
	void rva003A2C0D(Player *owner, const AsciiString &ownerName, bool singleton, Dict *dict);

	void *m_vft; // +0x00
	void *m_factory; // +0x04
	Player *m_owningPlayer; // +0x08
	unsigned int m_id; // +0x0c
	AsciiString m_name; // +0x10
	AsciiString m_ownerName; // +0x14
	int m_flags; // +0x18
	unsigned char m_1c; // +0x1c
	char m_pad1d[3]; // +0x1d
	AsciiString m_20; // +0x20
	void *m_productionConditionScript; // +0x24
	unsigned char m_28; // +0x28
	char m_pad29[3]; // +0x29
	char m_pad2c[0x12c - 0x2c]; // +0x2c..0x12b (generic scripts/names preserved)
	TeamTemplateInfo m_teamTemplate; // +0x12c
	AsciiString m_attackPriorityName; // +0x318
	unsigned char m_31c; // +0x31c
	unsigned char m_31d; // +0x31d
	unsigned char m_31e; // +0x31e
	char m_pad31f; // +0x31f
	unsigned int m_320; // +0x320
	unsigned char m_324; // +0x324
	char m_pad325[3]; // +0x325
	float m_328; // +0x328
	float m_32c; // +0x32c
	float m_330; // +0x330
};

void TeamPrototype::rva003A2C0D(Player *owner, const AsciiString &ownerName, bool singleton, Dict *dict)
{
	rva003A0CD1();
	m_name.setCopyInline(owner->m_playerName);
	m_ownerName.setCopyInline(ownerName);
	m_1c = 0;
	m_productionConditionScript = 0;
	m_28 = 0;
	m_31c = 0;
	m_31d = 0;
	m_31e = 0;
	m_owningPlayer = owner;
	m_flags = singleton ? 1 : 0;
	unsigned int tmp320 = TheGameLogic->getFrame();
	m_324 = 0;
	m_320 = tmp320;
	float *zeroBase = &m_328;
	zeroBase[0] = 0.0f;
	zeroBase[1] = 0.0f;
	zeroBase[2] = 0.0f;
	m_teamTemplate.loadFromDict(dict);
	addToLists();
}
