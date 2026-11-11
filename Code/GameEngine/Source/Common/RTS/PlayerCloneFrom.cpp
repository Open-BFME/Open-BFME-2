// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Player::cloneFrom. Identity: WB 0x00C15D30 names it (Player.cpp
// 1563..1633, "you cannot clone human controlled players"); native
// 0x002B07A9..0x002B0A05 is thiscall ret 4 and PlayerList::createClonedAllyFor
// 0x002A7F2A hands it the source player. Native facts: player type +5C must
// be 1 (computer); the clone copies the source side's dict, renames itself
// "%s_%d" from the source name and a running counter, adds a side and a
// singleton team "team<name>", initializes from the dict, takes over the
// source's money, copies the relation map and allies both players. The
// field layout (name +4C, key +50, money +90, relations +330, score +3BC)
// is the one PlayerInitFromDict.cpp's verified Player::init uses. The
// sub-object at +8 is reached only through its fourth virtual slot; its
// purpose is not established. Placeholder callee names (money 0x003B0CB3 /
// 0x003B0D7C, relation setter 0x002ADF9C, relation copy 0x002ADE71) are the
// rowed owners' spellings.
#include "ascii_string.h"
#include <hash_map>
// Match RelationMapXfer.cpp's inline bucket-vector accessors.
namespace _STL { template <> __declspec(dllimport) __forceinline void *& vector<void *, allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *, allocator<void *> >::size() const { return (unsigned int)(this->_M_finish - this->_M_start); } }

typedef bool Bool;
typedef int Int;
enum NameKeyType { NAMEKEY_INVALID = 0, FORCE_NAMEKEYTYPE_LONG = 0x7fffffff };
enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };

class StaticNameKey
{
public:
	NameKeyType key() const;
private:
	NameKeyType m_key;
	const char *m_name;
};
class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamOwner;
extern Rva00148F5ECache TheKey_teamIsSingleton;

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

struct DictPairData
{
	unsigned short m_refCount;
};
class Dict
{
public:
	Dict(int numPairsToPreAllocate);
	Dict(const Dict &src) : m_data(src.m_data)
	{
		if (m_data)
			++m_data->m_refCount;
	}
	~Dict() { releaseData(); }
	void clear();
	void setAsciiString(int key, const AsciiString &value);
	void setBool(int key, bool value);
private:
	void releaseData();
	DictPairData *m_data;
};

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }
private:
	void *m_buildList;
	Dict m_dict;
};
class TeamsInfoRec
{
public:
	int addTeam(const Dict *d);
};
class SidesList
{
public:
	SidesInfo *findSideInfo(AsciiString name, Int *index = 0);
	int addSide(const Dict *d);
	void addTeam(const Dict *dict) { m_teamrec.addTeam(dict); }
private:
	char m_pad[0xF44];
	TeamsInfoRec m_teamrec;
};
extern SidesList *TheSidesList;

#include "../../../Include/Common/TeamFactory.h"
extern TeamFactory *TheTeamFactory;

class Player;
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

typedef _STL::hash_map<Int, Relationship, _STL::hash<Int>, _STL::equal_to<Int> > PlayerRelationMapType;
class PlayerRelationMap
{
public:
	virtual ~PlayerRelationMap();
	PlayerRelationMap *rva002ADE71(const PlayerRelationMap *source);
	PlayerRelationMapType m_map;
};

class Object;
#include "../../../Include/Common/Rva002ADF9C.h"

class Rva0039B795;
class Rva0039B7AD;
class Rva003B0D7C
{
public:
	virtual ~Rva003B0D7C();
	unsigned int withdraw(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
	unsigned int countMoney() const { return m_money; }
private:
	unsigned int m_money;
	int m_owner;
};

class PlayerSubobject08
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
};

struct PlayerScoreView
{
	char bytes[4];
};

class Player
{
public:
	Bool cloneFrom(Player *other);
	Int getPlayerType() const { return m_playerType; }
	void initFromDict(const Dict *d);
	void setDefaultTeam();
	void setPlayerRelationship(const Player *that, Relationship r)
	{
		((Rva002ADF9C *)this)->rva002ADF9C(that, (Object *)r);
	}
private:
	char m_pad00[8];
	PlayerSubobject08 m_08;
	char m_pad0C[0x24 - 0x0C];
	int m_24;
	char m_pad28[0x4C - 0x28];
	AsciiString m_playerName;
	NameKeyType m_playerNameKey;
	Int m_playerIndex;
	AsciiString m_side;
	Int m_playerType;
	char m_pad60[0x90 - 0x60];
	Rva003B0D7C m_money;
	char m_pad9C[0x330 - 0x9C];
	PlayerRelationMap *m_playerRelations;
	char m_pad334[0x3BC - 0x334];
	PlayerScoreView m_scoreKeeper;
};

Bool Player::cloneFrom(Player *other)
{
	if (other->getPlayerType() == 1) {
		static Int cloneCount = 0;
		SidesInfo *sideInfo = TheSidesList->findSideInfo(other->m_playerName);
		Dict d = *sideInfo->getDict();
		m_playerName.format("%s_%d", other->m_playerName.str(), cloneCount++);
		m_playerNameKey = TheNameKeyGenerator->nameToKey(m_playerName);
		d.setAsciiString(TheKey_playerName.key(), m_playerName);
		TheSidesList->addSide(&d);

		AsciiString teamName;
		teamName = "team";
		teamName.concat(m_playerName);
		Dict teamDict(0);
		teamDict.clear();
		teamDict.setAsciiString(TheKey_teamName.key(), teamName);
		teamDict.setAsciiString(TheKey_teamOwner.key(), m_playerName);
		teamDict.setBool(TheKey_teamIsSingleton.get(), true);
		TheSidesList->addTeam(&teamDict);

		initFromDict(&d);
		m_money.withdraw(m_money.countMoney(), (Rva0039B795 *)&m_scoreKeeper, false);
		m_money.rva003B0D7C(other->m_money.countMoney(), (Rva0039B7AD *)&m_scoreKeeper, false);
		m_playerRelations->rva002ADE71(other->m_playerRelations);
		setPlayerRelationship(other, ALLIES);
		other->setPlayerRelationship(this, ALLIES);
		for (PlayerRelationMapType::iterator it = m_playerRelations->m_map.begin();
			it != m_playerRelations->m_map.end(); ++it) {
			Player *anOther = ThePlayerList->getNthPlayer((*it).first);
			anOther->setPlayerRelationship(this, (*it).second);
		}
		setPlayerRelationship(this, ALLIES);
		if (this != ThePlayerList->getNeutralPlayer())
			setPlayerRelationship(ThePlayerList->getNeutralPlayer(), NEUTRAL);
		TheTeamFactory->initTeam(teamName, m_playerName, true, &teamDict);
		setDefaultTeam();
		m_08.slot03();
		m_24 = 0;
		return true;
	}
	return false;
}
