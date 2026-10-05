// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?addTeamPrototypeToList@TeamFactory@@QAEXPAVTeamPrototype@@@Z @0x003A2B78 92B: TeamFactory add prototype.
// Evidence: ret 4 one arg; TeamPrototype AsciiStrings at +0x10/+0x14 via TheNameKeyGenerator::nameToKey row; pair key via Rva0039EA4E lower_bound row 0x0039EA4E plus map operator[] row 0x003A2943 with map at +0xb0; caller 0x003A2BDF unblocks 0x003A2BD4.
#include "ascii_string.h"
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
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
	void *m_vft;
	void *m_factory;
	void *m_owner;
	unsigned int m_id;
	AsciiString m_name;
	AsciiString m_ownerName;
};
struct Rva0039EA4ENode
{
	int m_color;
	Rva0039EA4ENode *m_parent;
	Rva0039EA4ENode *m_left;
	Rva0039EA4ENode *m_right;
	Rva0039D8FBKey m_key;
};
class Rva0039EA4E
{
public:
	Rva0039EA4ENode *rva0039EA4E(const Rva0039D8FBKey &key);
	Rva0039EA4ENode *m_header;
};
typedef std::pair<int, int> BfmeTeamPrototypeKey;
class TeamFactory
{
public:
	void addTeamPrototypeToList(TeamPrototype *team);
private:
	char m_pad[0xb0];
	Rva0039EA4E m_tree;
};

void TeamFactory::addTeamPrototypeToList(TeamPrototype *team)
{
	int ownerKey = TheNameKeyGenerator->nameToKey(team->m_ownerName);
	Rva0039D8FBKey key;
	key.m_first = TheNameKeyGenerator->nameToKey(team->m_name);
	key.m_second = ownerKey;
	Rva0039EA4E *tree = (Rva0039EA4E *)((char *)this + 0xb0);
	if (tree->rva0039EA4E(key) != tree->m_header)
		return;
	std::map<BfmeTeamPrototypeKey, TeamPrototype *> *m = (std::map<BfmeTeamPrototypeKey, TeamPrototype *> *)((char *)this + 0xb0);
	(*(TeamPrototype **)&(*m)[*(BfmeTeamPrototypeKey *)&key]) = team;
}
