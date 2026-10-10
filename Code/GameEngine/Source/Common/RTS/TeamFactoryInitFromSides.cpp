// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// TeamFactory::initFromSides, retail 0x003A4182..0x003A4322 (416 bytes).
// Identity: WorldBuilder EED1D0 and the retail calls agree with Zero Hour
// Team.cpp initFromSides: clear, read final team dictionaries, then initTeam.
// Donor: Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/Team.cpp.
// Target deltas: signed 16-bit links in 16-byte records at SidesList+F50,
// flags at record+6 and Dict at +C. Retail promotes the link to an int and
// retains its byte offset across the dictionary calls. The equal-value
// pointer/index conditionals preserve retail's SIB operand order.
// Forty dummy AI teams follow, selected by the owned Player predicate2AA245.
// TeamFactory dummy slots +10 and unique ID +BC are measured target accesses;
// TeamPrototype's 338-byte allocation and owner/name +10/+14 follow its ctor.
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
class Rva00148F5ECache {public:NameKeyType get();private:int value;const char *name;};
// The first two globals retain the data ledger's provisional const owner
// spelling; their mutable key and name pointer share the lazy-cache layout.
class StaticNameKey {private:mutable int value;const char *name;};
extern const StaticNameKey TheKey_teamName,TheKey_teamOwner;
extern Rva00148F5ECache TheKey_teamIsSingleton;
inline int teamKey(const StaticNameKey &key){return ((Rva00148F5ECache*)&key)->get();}
inline int teamKey(Rva00148F5ECache &key){return key.get();}

class Player {public:bool rva002AA245()const;char unknown00[0x4c];AsciiString playerName;};
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

// Target3A4182..3A4322416B and WB EED1D0 reproduce ZH initFromSides
// order: clear then final team dictionaries. BFME2 adds forty dummy AI
// teams owned by the first player whose target predicate2AA245 returns true.
// Target first/next signed shorts in16B records at sidesF50; flags6==0;
// DictC. Key caches independently name teamName/teamOwner/teamIsSingleton.
void TeamFactory::initFromSides(SidesList *sides)
{
 clear();
 int id=sides->teams.first();
 while(id) {
  id *= sizeof(TeamInfoRecord);
  if(*(unsigned short*)(((id ? id : id)+(char*)(sides ? sides->teams.records : sides->teams.records))+6)==0) {
   Dict *d=(Dict*)(((id ? id : id)+(char*)(sides ? sides->teams.records : sides->teams.records))+12);
   AsciiString tname=d->getAsciiString(teamKey(TheKey_teamName));
   AsciiString oname=d->getAsciiString(teamKey(TheKey_teamOwner));
   bool singleton=d->getBool(teamKey(TheKey_teamIsSingleton));
   initTeam(tname,oname,singleton,d);
  }
  id=*(short*)(((id ? id : id)+(char*)(sides ? sides->teams.records : sides->teams.records)));
 }

 int mask=ThePlayerList->rva002A7D30();
 Player *player=ThePlayerList->getEachPlayerFromMask(mask);
 while(player && !player->rva002AA245())
  player=ThePlayerList->getEachPlayerFromMask(mask);
 if(!player)return;
 for(unsigned i=0;i<40;++i) {
  AsciiString name;name.format("DummyAITeam%u",i);
  TeamPrototype *team=new TeamPrototype(this,player->playerName,name,player,false,0,++m_uniqueTeamPrototypeID);
  m_dummyTeams[i]=team;
 }
}
