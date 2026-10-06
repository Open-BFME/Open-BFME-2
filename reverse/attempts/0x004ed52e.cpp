// ?rva004ED52E@Rva004ECECD@@QAE_NPAVTeam@@@Z
// partial score=0.92 date=2026-10-06
// cl: /O1 /Ireference/shims/bfmevector /Ireference/shims/bfme2_ascii /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// stlport
// ?rva004ED52E@Rva004ECECD@@QAE_NPAVTeam@@@Z @ 0x004ED52E 365B.
// Rva004ECECD tactic helper taking the active Team: collects candidate Objects
// via the g_00DFEEF8 registry (rowed 0x002A8F24) plus bucket_count 0x002BEDAB
// and rowed getter 0x0025BFF8, filters template kind 0x20 at +0x115 and team
// mismatch at +0x304 vs Player+0x2EC default team, keeps the first whose
// victim 0x0028ACA0 is set, then builds an AIGroup via TheAI 0x00DFF0F8,
// Team::getTeamAsAIGroup 0x003A0F62, BitFlags count 0x0039DC9E from shared
// storage 0x009FEFA4, and BfmeC986 dispatch 0x00372C74/0x00372B09 before
// destroying the group 0x002FE712. Returns true when a group was built.
// Evidence: caller 0x004ED748 passes Team in ebx with this=Rva004ECECD;
// callees all rowed/pinned per packet; LINK BONUS via 0x004ED748.
// ?rva004ED52E@Rva004ECECD@@QAE_NPAVTeam@@@Z present-unmatched
#include <vector>

namespace _STL
{
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}
typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

#pragma comment(linker, "/alternatename:??0?$BitFlags@$0HE@@@QAE@ABV0@@Z=??0BfmeFixedStorage0004543D@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@ABV?$allocator@PAVObject@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")

class Team;
class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;
	char m_pad58[0x2EC - 0x58];
	Team *m_defaultTeam;
};

struct ThingTemplate
{
	unsigned char m_pad[0x115];
	unsigned char m_kind115;
};

class Object
{
public:
	Object *rva0028ACA0() const;
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x304 - 0x08];
	Team *m_team;
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
};

class AIGroup;
class AI
{
public:
	AIGroup *createGroup();
	void rva002FE712(AIGroup *group);
};
extern AI *g_Va009FF0F8;

class BfmeC986
{
public:
	void rva00372C74(int a, int b, int c, int d);
	void rva00372B09(int a, int b, int c);
};

template <int N>
class BitFlags
{
public:
	BitFlags(const BitFlags &other);
private:
	unsigned int m_bits[7];
};

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	int rva0039DC9E(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear) const;
};

class Rva004ECECD
{
public:
	bool rva004ED52E(Team *team);
private:
	char m_pad00[0x24];
	Player *m_player;
};

bool Rva004ECECD::rva004ED52E(Team *team)
{
	void *store = g_00DFEEF8->rva002A8F24(m_player);
	Rva0025BFF8 *holder = *(Rva0025BFF8 **)store;
	const int count = (int)((IntMap *)holder)->bucket_count();
	if (count <= 0)
		return false;
	_STL::vector<Object *> vec;
	Player *player = m_player;
	int i = 0;
	Team *targetTeam = player->m_defaultTeam;
	for (; i < count; ++i) {
		Object *obj = holder->rva0025BFF8(i);
		if ((obj->m_template->m_kind115 & 0x20) != 0 && obj->m_team != targetTeam) {
			Object *tmp = obj;
			vec.push_back(tmp);
		}
	}
	Object *found = 0;
	for (Object **it = vec.begin(); it != vec.end() && found == 0; ++it) {
		if ((*it)->rva0028ACA0() != 0)
			found = *it;
	}
	if (found == 0)
		return false;
	AIGroup *grp = g_Va009FF0F8->createGroup();
	team->getTeamAsAIGroup(grp);
	int n = team->rva0039DC9E(*(const BitFlags<116> *)&g_defaultStorage009FEFA4, *(const BitFlags<116> *)&g_defaultStorage009FEFA4);
	if (n > 1) {
		Object *v = found->rva0028ACA0();
		((BfmeC986 *)grp)->rva00372C74((int)((char *)v + 0x38), 0, 0, 1);
	} else {
		Object *v = found->rva0028ACA0();
		((BfmeC986 *)grp)->rva00372B09((int)((char *)v + 0x38), 0x7fffffff, 0);
	}
	g_Va009FF0F8->rva002FE712(grp);
	return true;
}
