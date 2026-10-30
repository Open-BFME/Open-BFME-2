// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?addTeamPrototypeToList@TeamFactory@@QAEXPAVTeamPrototype@@@Z @0x003A2B78 92B: TeamFactory add prototype.
// Evidence: ret 4 one arg; TeamPrototype AsciiStrings at +0x10/+0x14 via TheNameKeyGenerator::nameToKey row; pair key via Rva0039EA4E lower_bound row 0x0039EA4E plus map operator[] row 0x003A2943 with map at +0xb0; caller 0x003A2BDF unblocks 0x003A2BD4.
#include "ascii_string.h"
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
	const AsciiString &keyToName(NameKeyType);
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
struct Rva0039D8FBKey
{
	int m_first;
	int m_second;
};
class TeamPrototype
{
public:
	void addToLists();
	void *m_vft;
	void *m_factory;
	void *m_owner;
	unsigned int m_id;
	AsciiString m_name;
	AsciiString m_ownerName;
};
struct Rva0039EA4ENode
{
public:
	int m_color00; // +0x00
	Rva0039EA4ENode *m_parent04; // +0x04
	Rva0039EA4ENode *m_left08; // +0x08
	Rva0039EA4ENode *m_right0C; // +0x0C
	Rva0039D8FBKey m_key10; // +0x10
	TeamPrototype *m_value18; // +0x18
};
struct Rva0039F5C8Iterator;
class Rva0039EA4E
{
public:
	Rva0039EA4ENode *rva0039EA4E(const Rva0039D8FBKey &key);
	Rva0039F5C8Iterator rva0039F5C8(const Rva0039D8FBKey &key);
	Rva0039EA4ENode *rva0039F597(const Rva0039D8FBKey &key);
	Rva0039F5C8Iterator rva0039FB73(const Rva0039D8FBKey &key);
	unsigned int size() const { return m_nodeCount04; }
	Rva0039EA4ENode *m_header00; // +0x00
	unsigned int m_nodeCount04; // +0x04 TeamFactory::xfer checks it against the saved count
};
typedef std::pair<int, int> BfmeTeamPrototypeKey;
// insert_unique is called out of line: bind it to StlSweepR3Rva0039F692.cpp's rowed
// retail specialization instead of emitting a competing (duplicate) copy here.
namespace _STL { template <> pair<_Rb_tree_iterator<pair<const pair<int, int>, TeamPrototype *>, _Nonconst_traits<pair<const pair<int, int>, TeamPrototype *> > >, bool> _Rb_tree<pair<int, int>, pair<const pair<int, int>, TeamPrototype *>, _Select1st<pair<const pair<int, int>, TeamPrototype *> >, less<pair<int, int> >, allocator<pair<const pair<int, int>, TeamPrototype *> > >::insert_unique(const pair<const pair<int, int>, TeamPrototype *> &); }
class TeamFactory
{
public:
	void addTeamPrototypeToList(TeamPrototype *team);
private:
	char m_pad[0xb0];
	Rva0039EA4E m_tree;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Team;
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
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *);
};
extern class Rva002A8F24 *TheSkirmishAIManager;
// The +0x90 forwarder rowed at 0x004EC072 (RvaWideAdjustFwds.cpp).
class Rva004EC072Owner
{
public:
	void fwd(void *arg);
};

void TeamFactory::addTeamPrototypeToList(TeamPrototype *team)
{
	int ownerKey = TheNameKeyGenerator->nameToKey(team->m_ownerName);
	Rva0039D8FBKey key;
	key.m_first = TheNameKeyGenerator->nameToKey(team->m_name);
	key.m_second = ownerKey;
	Rva0039EA4E *tree = (Rva0039EA4E *)((char *)this + 0xb0);
	if (tree->rva0039EA4E(key) != tree->m_header00)
		return;
	std::map<BfmeTeamPrototypeKey, TeamPrototype *> *m = (std::map<BfmeTeamPrototypeKey, TeamPrototype *> *)((char *)this + 0xb0);
	(*(TeamPrototype **)&(*m)[*(BfmeTeamPrototypeKey *)&key]) = team;
}

void TeamPrototype::addToLists()
{
	if (m_factory)
		((TeamFactory *)m_factory)->addTeamPrototypeToList(this);
	if (!m_owner)
		return;
	((Player *)m_owner)->addTeamToList(this);
	struct Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(m_owner);
	if (!rec)
		return;
	((Rva004EC072Owner *)rec)->fwd(this);
}
