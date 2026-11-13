// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0059BB50@Rva0059BB50@@QAEXHHHH@Z
// retail 0x0059BB50..0x0059BD2D (477 bytes) thiscall RET 0x10, EH frame
// (state 0: the candidate record vector, state 1: the copied link map).
//
// Target facts: the only caller, the guarded forwarder 0x004FB303, passes the
// subobject at this+0x120 and four stack words (the move vector, a player id,
// an unused word and the 0xE04508 channel table). The body looks up the player
// (0x002B51F8), gets the garrison record vector for that player (0x004FF9C9),
// and per record resolves the army (0x002E0A9F), skipping armies with no units
// (+0x40/+0x44 8-byte vector). Records with candidates from 0x00502381 go to
// sibling 0x0059B8FD; the rest take the closest hero (0x004FFB00), its region
// owner (0x002B488E then 0x00318C79), copy the link multimap of the territory
// from the 0xE04544 int map (copy ctor 0x0050055D, dtor 0x002B82D5), walk
// equal_range(1) (0x002F1C89) and append a move through rowed
// vector<BfmePod20>::push_back 0x0059B8C6 for the first owned region
// (0x002E0BC0) nearer than the hero (0x0050059A).
// WorldBuilder lead only: the WB twin 0x014FFDD0 calls the same graph under
// the names GetGarrisonArmies/findArmy/GetID/GetRegionInfo. The class and
// method identity are unproven, so the placeholder names stay; field and
// argument names are inferred.
//
// ?rva0059B8FD@Rva0059BB50@@... retail 0x0059B8FD..0x0059BB50 (595 bytes)
// thiscall RET 0x14, EH frame.
//
// Target facts: called by 0x0059BB50 with the move vector, the player
// id, the garrison record, its candidate records and the channel table. It
// takes the territory army count from 0x00500659 (the returned int vector is
// freed at once) and copies the candidates (0x00500DA0, dtor 0x005011DA) and
// the garrison's link multimap (copy ctor 0x004FFFF9, dtor 0x004FF5F3). For
// keys 0..7, while the copy still holds the key, it picks a candidate (with
// more than three armies: the one with the fewest links, ties broken by the
// fewest links on that key; otherwise the first), appends a move
// {garrison id, false, candidate id, link value, -1} through 0x0059B8C6,
// inserts (key, value) into the candidate's links (insert_equal 0x004FF876)
// and erases the key from the copy (_M_find 0x00388F63, erase 0x005530A8).
// The WB twin 0x01500100 shares the statement order. The element links are
// read through a multimap<int,int> view: its inline count/insert wrappers
// give retail's this-before-argument order. The erase goes through the
// map<int,void*> inline erase, which copies the iterator into the argument
// slot. The folded STL names are the ledger's own.
#include <map>

// Preserve STLport's inlined walk without emitting a competing size-profile
// wrapper. stlport_map_int_int.cpp owns the complete retail entry at 0x169ED0.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{
    _M_node = _Rb_global_inst::_M_increment(_M_node);
    return *this;
}
}
#include <vector>
// Retail's vector<BfmePod20>::_M_insert_overflow 0x0059B809 inlines max
// (StlportVectorInsertOverflowRva0059B809.cpp); a non-template overload
// keeps this unit from emitting or calling max<unsigned int>.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern unsigned int g_Va00E04544;

typedef _STL::map<int, int> Rva0059BB50IntMap;
typedef _STL::multimap<int, int> Rva0059B8FDLinkMap;
typedef _STL::pair<const int, int> Rva0059BB50IntValue;
typedef _STL::_Rb_tree<int, Rva0059BB50IntValue, _STL::_Select1st<Rva0059BB50IntValue>,
	_STL::less<int>, _STL::allocator<Rva0059BB50IntValue> > Rva0059BB50IntTree;
typedef _STL::pair<Rva0059BB50IntTree::iterator, Rva0059BB50IntTree::iterator> Rva0059BB50Range;

class Rva002E2903Player;
struct Rva002B488EResult;

struct BfmePod20
{
	int m_id;
	bool m_flag;
	int m_08;
	int m_0c;
	int m_step;
};


#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../../../Include/GameLogic/Rva002E0A9FElem.h"

#include "../../../../Include/GameLogic/Rva002E071E.h"

#include "../../../../Include/GameLogic/Rva00318C79Owner.h"

int __cdecl rva0050059A(int from, int to);

struct Rva00501E3FElement
{
	int id;
	char map[12];
	void *opaque;
	Rva0059B8FDLinkMap &links() { return *(Rva0059B8FDLinkMap *)map; }
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<Rva00501E3FElement>(Rva00501E3FElement *p) { typedef Rva00501E3FElement BfmeDestroyT; p->~BfmeDestroyT(); } }
// This view's element destructs trivially; retail's range copy 0x00500CB8 loops over a real dtor.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<Rva00501E3FElement *>(Rva00501E3FElement *, Rva00501E3FElement *) {} }
typedef _STL::vector<Rva00501E3FElement> Rva0059BB50Records;

namespace _STL {
template <> vector<Rva00501E3FElement>::vector(const vector<Rva00501E3FElement> &);
}

struct Rva005011DA : Rva0059BB50Records
{
	Rva005011DA() {}
	Rva005011DA(const Rva0059BB50Records &src) : Rva0059BB50Records(src) {}
	~Rva005011DA();
};

struct Rva004FFFF9Element
{
	int m_00;
};
typedef _STL::_Rb_tree<Rva004FFFF9Element, Rva004FFFF9Element, _STL::_Identity<Rva004FFFF9Element>,
	_STL::less<Rva004FFFF9Element>, _STL::allocator<Rva004FFFF9Element> > Rva004FFFF9Tree;
struct Rva00501875Count;
typedef _STL::pair<const int, Rva00501875Count> Rva0059B8FDCountValue;
typedef _STL::pair<const int, void *> Rva0059B8FDPtrValue;
typedef _STL::_Rb_tree<int, Rva0059B8FDPtrValue, _STL::_Select1st<Rva0059B8FDPtrValue>,
	_STL::less<int>, _STL::allocator<Rva0059B8FDPtrValue> > Rva0059B8FDPtrTree;
typedef _STL::map<int, void *> Rva0059B8FDPtrMap;

namespace _STL {
template <> Rva004FFFF9Tree::_Rb_tree(const Rva004FFFF9Tree &);
template <> void Rva0059B8FDPtrTree::erase(Rva0059B8FDPtrTree::iterator);
template <> class _Rb_tree<int, Rva0059B8FDCountValue, _Select1st<Rva0059B8FDCountValue>,
	less<int>, allocator<Rva0059B8FDCountValue> > : public Rva004FFFF9Tree
{
public:
	_Rb_tree(const Rva004FFFF9Tree &src) : Rva004FFFF9Tree(src) {}
	~_Rb_tree();
};
}
typedef _STL::_Rb_tree<int, Rva0059B8FDCountValue, _STL::_Select1st<Rva0059B8FDCountValue>,
	_STL::less<int>, _STL::allocator<Rva0059B8FDCountValue> > Rva0059B8FDLinks;

class Rva0050055D
{
public:
	Rva0050055D(const Rva0050055D &other);
	char m_data[24];
};

class Rva002B82D5 : public Rva0050055D
{
public:
	Rva002B82D5(const Rva0050055D &other) : Rva0050055D(other) {}
	~Rva002B82D5();
};

struct Rva004FF5B7Node
{
	char m_pad00[0x10];
	int m_10;
	int m_14;
};

#include "../../../../Include/GameLogic/Rva004FF5B7Iter.h"

#include "../../../../Include/Common/Rva004FF5B7.h"

class Rva004FF9C9
{
public:
	void *GetGarrisonArmies(int key);
};

struct Rva004FFB00Hero
{
	int m_id;
};

// The row's spelling of 0x00500659's return vector (an int-sized enum).
enum ObjectID
{
	INVALID_ID = 0
};

class Rva0059CFAACallee
{
public:
	_STL::vector<ObjectID> rva00500659(int playerId, int *territory, int *count);
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
};

class Rva00502381
{
public:
	void rva00502381(int who, int limit, const int *key, Rva0059BB50Records *out);
};

struct Rva0059BB50Pair8
{
	int m_a;
	int m_b;
};

struct Rva0059BB50Units
{
	char m_pad00[0x40];
	Rva0059BB50Pair8 *m_start;
	Rva0059BB50Pair8 *m_finish;
	unsigned int size() const { return m_finish - m_start; }
};

struct Rva0059BB50Army
{
	char m_pad00[0x20];
	int m_id;
	char m_pad24[0x54];
	Rva0059BB50Units *m_units;
};

class Rva0059BB50
{
public:
	void rva0059BB50(int moves, int playerId, int unused, int armies);
	void rva0059B8FD(_STL::vector<BfmePod20> *moves, int playerId,
		Rva00501E3FElement *garrison, Rva0059BB50Records *candidates, int armies);
	void rva0047A69C(int v);	// folded into 0x0047A69C
};

void Rva0059BB50::rva0059BB50(int moves, int playerId, int unused, int armies)
{
	Rva002E2903Player *player =
		((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	Rva0059BB50Records *garrisons =
		(Rva0059BB50Records *)((Rva004FF9C9 *)armies)->GetGarrisonArmies(playerId);
	for (unsigned int i = 0; i < garrisons->size(); ++i)
	{
		Rva0059BB50Army *army = (Rva0059BB50Army *)((Rva002E0A9FElem *)player)->rva002E0A9F((void *)(*garrisons)[i].id);
		if (army->m_units->size() == 0)
			continue;
		BfmePod20 move;
		move.m_id = army->m_id;
		move.m_flag = false;
		move.m_08 = 0;
		move.m_step = -1;
		Rva005011DA candidates;
		((Rva00502381 *)armies)->rva00502381(playerId, 1, (const int *)(*garrisons)[i].opaque, &candidates);
		if (candidates.size() > 0)
		{
			rva0059B8FD((_STL::vector<BfmePod20> *)moves, playerId, &(*garrisons)[i], &candidates, armies);
			continue;
		}
		int distance = 0;
		int *territory = (int *)(*garrisons)[i].opaque;
		int from = ((Rva00318C79Owner *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B488E(
			((Rva0059CFAACallee *)armies)->rva004FFB00(playerId, territory, &distance)->m_id))->rva00318C79();
		Rva002B82D5 links(*(const Rva0050055D *)&((Rva0059BB50IntMap *)&g_Va00E04544)->find(*territory)->second);
		Rva0059BB50Range range = ((Rva0059BB50IntTree *)&links)->equal_range(1);
		for (Rva0059BB50IntTree::iterator it = range.first; it != range.second; ++it)
		{
			Rva004FF5B7Iter region = ((Rva004FF5B7 *)armies)->GetRegionInfo((*it).second);
			if ((unsigned char)((Rva002E071E *)player)->rva002E0BC0(region.m_ptr->m_10)
				&& rva0050059A(from, region.m_ptr->m_14) < distance)
			{
				move.m_step = region.m_ptr->m_14;
				((_STL::vector<BfmePod20> *)moves)->push_back(move);
				break;
			}
		}
	}
}

void Rva0059BB50::rva0059B8FD(_STL::vector<BfmePod20> *moves, int playerId,
	Rva00501E3FElement *garrison, Rva0059BB50Records *candidates, int armies)
{
	int count = 0;
	int *territory = (int *)garrison->opaque;
	((Rva0059CFAACallee *)armies)->rva00500659(playerId, territory, &count);
	Rva005011DA records(*candidates);
	if (count > 3)
	{
		Rva0059B8FDLinks links(*(const Rva004FFFF9Tree *)garrison->map);
		for (int i = 0; i < 8; ++i)
		{
			int key = i;
			while (((Rva0059BB50IntTree *)&links)->count(key) > 0)
			{
				Rva00501E3FElement *best = &records[0];
				unsigned int bestCount = best->links().count(key);
				for (unsigned int j = 1; j < records.size(); ++j)
				{
					if (records[j].links().size() < best->links().size()
						|| (records[j].links().size() == best->links().size()
							&& records[j].links().count(key) < bestCount))
					{
						bestCount = records[j].links().count(key);
						best = &records[j];
					}
				}
				BfmePod20 move;
				move.m_id = garrison->id;
				move.m_flag = false;
				move.m_08 = best->id;
				move.m_step = -1;
				move.m_0c = (*((Rva0059BB50IntTree *)&links)->find(key)).second;
				moves->push_back(move);
				best->links().insert(Rva0059BB50IntValue(key, move.m_0c));
				((Rva0059B8FDPtrMap *)&links)->erase(Rva0059B8FDPtrTree::iterator(
					(Rva0059B8FDPtrTree::_Link_type)((Rva0059BB50IntTree *)&links)->find(key)._M_node));
			}
		}
	}
	else
	{
		Rva0059B8FDLinks links(*(const Rva004FFFF9Tree *)garrison->map);
		for (int i = 0; i < 8; ++i)
		{
			int key = i;
			while (((Rva0059BB50IntTree *)&links)->count(key) > 0)
			{
				Rva00501E3FElement *best = &records[0];
				BfmePod20 move;
				move.m_id = garrison->id;
				move.m_flag = false;
				move.m_08 = best->id;
				move.m_step = -1;
				move.m_0c = (*((Rva0059BB50IntTree *)&links)->find(key)).second;
				moves->push_back(move);
				best->links().insert(Rva0059BB50IntValue(key, move.m_0c));
				((Rva0059B8FDPtrMap *)&links)->erase(Rva0059B8FDPtrTree::iterator(
					(Rva0059B8FDPtrTree::_Link_type)((Rva0059BB50IntTree *)&links)->find(key)._M_node));
			}
		}
	}
}

// The +0x120 member call of the attach 0x004FB222, which hands the same int
// to the +0x8C/+0xEC/+0xFC subobjects: on this class it is an empty stub that
// folds into the shared 3-byte RET 4 at 0x0047A69C. Name address-derived.
void Rva0059BB50::rva0047A69C(int v)
{
}
