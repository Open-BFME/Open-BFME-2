// ?initFromSides@TeamFactory@@QAEXPAVSidesList@@@Z
// partial score=0.9049009758897819 date=2026-10-10
// ?initFromSides@TeamFactory@@QAEXPAVSidesList@@@Z
// partial score=0.85 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?initTeam@TeamFactory@@QAEXABVAsciiString@@0_NPAVDict@@@Z, retail 0x003A404D
// (168 bytes).
// Identity (target): WorldBuilder's debug Team.cpp TeamFactory::initTeam
// (callgraph lead, score 2) calls, in retail's order, the prototype lookup
// findTeamPrototype (0x0039FE6C), nameToKey, PlayerList::findPlayerWithNameKey,
// operator new, the prototype constructor and
// TeamFactory::createInactiveTeam (WB-named, 0x003A3B7E).
// Donor (Zero Hour TeamFactory::initTeam): an existing prototype is left
// alone; the owner defaults to the neutral player (ThePlayerList +0x18); a
// new TeamPrototype takes ++m_uniqueTeamPrototypeID (+0xBC); singletons get
// their inactive team at once. BFME 2 deltas (target): the lookup and
// createInactiveTeam are keyed by (owner name, team name), here the
// prototype's +0x10/+0x14 strings, and the constructor takes the owner name
// before the team name. The 0x338-byte allocation matches TeamPrototype's
// size (its instance-list head is at +0x334).
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player;
class Dict {
public: AsciiString getAsciiString(int key,bool *exists=0) const; bool getBool(int key,bool *exists=0) const;
private: unsigned storage;
};
struct TeamInfoRecord { short next;char unknown02[4];unsigned short flags;unsigned unknown08;Dict dict; };
class TeamsInfoRec {public:char unknown00[12];TeamInfoRecord *records;
 int first()const{return records[0].next;}
 int getNextTeamID(int id)const{return records[id].next;}
 bool isFinal(int id)const{return records[id].flags==0;}
 Dict *getTeamInfo(int id){return &records[id].dict;}
};
class SidesList {public:char unknown00[0xf44];TeamsInfoRec teams;};
class Rva00148F5ECache {public:NameKeyType get();};
struct StaticNameKey {int key;const char *name;};
extern StaticNameKey TheKey_teamName,TheKey_teamOwner,TheKey_teamIsSingleton;
inline int teamKey(StaticNameKey &key){return ((Rva00148F5ECache*)&key)->get();}
class Rva002AA245MovzxByteChaseField {public:unsigned get()const;};
class Player {public:char unknown00[0x4c];AsciiString playerName;};
class Team;
class TeamFactory;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
 int rva002A7D30();
 Player *getEachPlayerFromMask(int &mask);
	Player *getNeutralPlayer() { return m_players[0]; }

private:
	unsigned char m_pad00[0x18];
	Player *m_players[1]; // +0x18
};

extern PlayerList *ThePlayerList;

class TeamPrototype
{
public:
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
		Player *ownerPlayer, bool isSingleton, Dict *d, int id);

	const AsciiString &getOwnerName() const { return m_owner; }
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_pad00[0x10];
	AsciiString m_owner; // +0x10
	AsciiString m_name; // +0x14
	unsigned char m_pad18[0x338 - 0x18];
};

class TeamFactory
{
public:
	void initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d);
 void initFromSides(SidesList *sides);
 void clear();
	TeamPrototype *findTeamPrototype(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);

private:
	unsigned char m_pad00[0x10];
 TeamPrototype *m_dummyTeams[40];
 unsigned char m_padB0[0xBC-0xB0];
	int m_uniqueTeamPrototypeID; // +0xBC
};

void TeamFactory::initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d)
{
	if (findTeamPrototype(owner, name) != 0)
		return;
	Player *pOwner = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(owner));
	if (!pOwner)
		pOwner = ThePlayerList->getNeutralPlayer();
	TeamPrototype *tp = new TeamPrototype(this, owner, name, pOwner, isSingleton, d, ++m_uniqueTeamPrototypeID);
	if (isSingleton)
		createInactiveTeam(tp->getOwnerName(), tp->getName());
}

// Target3A4182..3A4322416B and WB EED1D0 reproduce ZH initFromSides
// order: clear then final team dictionaries. BFME2 adds forty dummy AI
// teams owned by the first player whose target predicate2AA245 returns true.
// Target first/next signed shorts in16B records at sidesF50; flags6==0;
// DictC. Key caches independently name teamName/teamOwner/teamIsSingleton.
void TeamFactory::initFromSides(SidesList *sides)
{
 clear();
 for(short id=sides->teams.first();id;id=sides->teams.getNextTeamID(id)) {
  if(!sides->teams.isFinal(id))continue;
  Dict *d=sides->teams.getTeamInfo(id);
  AsciiString tname=d->getAsciiString(teamKey(TheKey_teamName));
  AsciiString oname=d->getAsciiString(teamKey(TheKey_teamOwner));
  bool singleton=d->getBool(teamKey(TheKey_teamIsSingleton));
  initTeam(tname,oname,singleton,d);
 }
 int mask=ThePlayerList->rva002A7D30();
 Player *player=ThePlayerList->getEachPlayerFromMask(mask);
 while(player && !(unsigned char)((Rva002AA245MovzxByteChaseField*)player)->get())
  player=ThePlayerList->getEachPlayerFromMask(mask);
 if(!player)return;
 for(unsigned i=0;i<40;++i) {
  AsciiString name;name.format("DummyAITeam%u",i);
  TeamPrototype *team=new TeamPrototype(this,player->playerName,name,player,false,0,++m_uniqueTeamPrototypeID);
  m_dummyTeams[i]=team;
 }
}
