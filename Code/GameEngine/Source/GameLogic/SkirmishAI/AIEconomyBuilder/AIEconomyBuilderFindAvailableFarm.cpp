// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
//
// AIEconomyBuilder::findAvailableFarm, retail 0x004EA4E5 (790 bytes), called
// from 0x004EA89B; WorldBuilder twin 0x01381E70 (AIEconomyBuilder.cpp
// asserts "stats"/"structureStats" at lines 216/217).  Sorts the unclaimed
// farms of the shared farm list by distance to the owner's base (plus 200
// per +0x6C) into a multimap, finds the primary enemy's first living kind-194
// structure, then returns the first farm not within 1200 of it whose
// surroundings (radius from the AI data's +0x868) hold no living enemy of
// kinds 3/7/90 that is not kind 205; NULL when none qualifies.  The filter
// chain and query follow AIUpgradeScienceBuilder.cpp; the multimap is
// handled through its rowed members (the folded map ctor 0x0033C432,
// insert_equal 0x004EA301, _Rb_global<bool>::_M_increment 0x00024250 and
// the dtor 0x004EA28D).
#include <string.h>
#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include "PartitionRangeQueryCallView.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;

class Player;

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class T1, class T2> struct pair
{
	pair(const T1 &a, const T2 &b) : first(a), second(b) {}
	T1 first;
	T2 second;
};
template <class P> struct _Select1st {};
template <class T> struct _Nonconst_traits {};
template <class V, class Tr> struct _Rb_tree_iterator
{
	_Rb_tree_iterator() {}
	void *_M_node;
};
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);	// 0x00024250
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	_Rb_tree_iterator<V, _Nonconst_traits<V> > insert_equal(const V &v);	// 0x004EA301
};
template <class K, class T, class C, class A> class map
{
public:
	map();	// 0x0033C432 (multimap<Real, farm> ctor folds onto it)
	_Rb_tree_node_base *m_header;
	UnsignedInt m_nodeCount;
	Int m_compare;
};
}

class Rva004EA4E5Farm;

// The multimap's mapped value: the farm.
struct TreeOpaqueMapped00372FF4
{
	TreeOpaqueMapped00372FF4(Rva004EA4E5Farm *farm) : m_farm(farm) {}
	Rva004EA4E5Farm *m_farm;
};

typedef _STL::pair<const Real, TreeOpaqueMapped00372FF4> FarmEntry;
typedef _STL::_Rb_tree<Real, FarmEntry, _STL::_Select1st<FarmEntry>, _STL::less<Real>, _STL::allocator<FarmEntry> > FarmTree;

struct FarmNode : public _STL::_Rb_tree_node_base
{
	Real m_key;	// +0x10
	TreeOpaqueMapped00372FF4 m_value;	// +0x14
};

// multimap<Real, farm>: built through the folded map<int, void*> ctor,
// torn down by its own rowed dtor.
class Rva004EA149 : public _STL::map<Int, void *, _STL::less<Int>, _STL::allocator<_STL::pair<const Int, void *> > >
{
public:
	~Rva004EA149();	// 0x004EA28D
	FarmTree *tree() { return (FarmTree *)this; }
};

class Rva004EA4E5Farm
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12();
	virtual Coord3D getPosition();	// slot 13
	char m_pad04[0x64 - 0x04];
	bool m_claimed;	// +0x64
	char m_pad65[0x6C - 0x65];
	Int m_workers;	// +0x6C
	Int getWorkers() const { return m_workers; }
};

struct AIEconomyFarmLibraryStorage
{
	Rva004EA4E5Farm **m_begin;
	Rva004EA4E5Farm **m_end;
	Rva004EA4E5Farm **m_endOfStorage;
};

class AIBaseBuilder
{
public:
	bool rva00506B74(Coord3D *out);	// 0x00506B74 base position
};

struct Rva002A8AB1Record
{
	void *rva002C6ACB();	// 0x002C6ACB primary enemy target
	char m_pad00[4];
	AIBaseBuilder m_baseBuilder;	// +0x04
};

struct Rva004EA4E5Settings
{
	char m_pad000[0x868];
	Real m_farmDangerRadius;	// +0x868
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);	// 0x002A8AB1
	void *rva002A8F24(Player *player);	// 0x002A8F24
	const Rva004EA4E5Settings &getSettings() const { return m_settings; }
private:
	char m_pad00[0x10];
	Rva004EA4E5Settings m_settings;	// +0x10
};
extern Rva002A8F24 *g_00DFEEF8;

struct Rva004EA4E5IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;	// 0x005C4AD1
};

struct Rva004EA4E5Stats
{
	char m_pad00[8];
	Rva005C4AD1LeaField *m_structureStats;	// +0x08
};

class Rva004EA4E5Template
{
public:
	__forceinline UnsignedInt isKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 0x1f)); }
	char m_pad000[0x108];
	UnsignedInt m_kindOf[7];	// +0x108
};

struct Rva004EA4E5Object
{
	void *m_vtable;
	const Rva004EA4E5Template *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_position;	// +0x38
	char m_pad044[0x438 - 0x44];
	unsigned char m_status;	// +0x438
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship flags.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BFAF94: rejects the mask's kinds.
class Rva0027231F : public Rva000421C8
{
public:
	Rva0027231F(const BfmeFixedStorage0004543D &mask) throw();	// 0x0027231F
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask) throw();	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva004EA4E5Mask
{
	Rva004EA4E5Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

static __forceinline Real rva004EA4E5LengthSqr(const Coord3D &c)
{
	return c.x * c.x + c.y * c.y + c.z * c.z;
}

class AIEconomyBuilder
{
public:
	Rva004EA4E5Farm *findAvailableFarm();
	static AIEconomyFarmLibraryStorage m_farmList;
private:
	char m_pad00[0x14];
	Player *m_player;	// +0x14
};

Rva004EA4E5Farm *AIEconomyBuilder::findAvailableFarm()
{
	Rva004EA4E5Farm **it = m_farmList.m_begin;
	Rva004EA4E5Farm **end = m_farmList.m_end;
	Rva004EA149 farms;
	for (; it != end; ++it)
	{
		Rva004EA4E5Farm *farm = *it;
		if (farm->m_claimed)
			continue;
		Coord3D pos = farm->getPosition();
		Coord3D base;
		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_player);
		if (record->m_baseBuilder.rva00506B74(&base))
		{
			pos.x -= base.x;
			pos.y -= base.y;
			pos.z -= base.z;
			Real dist = pos.GetLength();
			dist += farm->getWorkers() * 200.0f;
			farms.tree()->insert_equal(FarmEntry(dist, farm));
		}
	}

	if (farms.m_nodeCount != 0)
	{

		Rva004EA4E5Object *depot = 0;
		void *target = g_00DFEEF8->rva002A8AB1(m_player)->rva002C6ACB();
		if (target)
		{
			Rva004EA4E5Stats *stats = (Rva004EA4E5Stats *)g_00DFEEF8->rva002A8F24((Player *)target);
			Rva004EA4E5IDs *ids = (Rva004EA4E5IDs *)stats->m_structureStats->get();
			ObjectID *idEnd = ids->m_end;
			for (ObjectID *id = ids->m_begin; id != idEnd && !depot; ++id)
			{
				Rva004EA4E5Object *obj = (Rva004EA4E5Object *)TheGameLogic->findObjectByID(*id);
				if (obj && !(obj->m_status & 1) && obj->m_template->isKindOf(194))
					depot = obj;
			}
		}

		_STL::_Rb_tree_node_base *endNode = farms.m_header;
		for (_STL::_Rb_tree_node_base *node = endNode->_M_left; node != endNode;
			node = _STL::_Rb_global<bool>::_M_increment(node))
		{
			Rva004EA4E5Farm *farm = ((FarmNode *)node)->m_value.m_farm;
			bool ok = false;
			if (depot)
			{
				Coord3D pos = farm->getPosition();
				pos.x -= depot->m_position.x;
				pos.y -= depot->m_position.y;
				pos.z -= depot->m_position.z;
				Real len2 = rva004EA4E5LengthSqr(pos);
				if (len2 > 1440000.0f)
					ok = true;
			}
			else
			{
				ok = true;
			}
			if (!ok)
				continue;

			Rva004EA4E5Mask kinds;
			kinds.set(3);
			kinds.set(90);
			kinds.set(7);
			Rva004EA4E5Mask rejectKinds;
			rejectKinds.set(205);
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&farm->getPosition(),
				g_00DFEEF8->getSettings().m_farmDangerRadius, 0,
				Rva0026119DFilter().link(&Rva00261409Filter(m_player, true, 4))->link(
					Rva003959FA(*(BfmeFixedStorage0004543D *)&kinds).link(&Rva0027231F(*(BfmeFixedStorage0004543D *)&rejectKinds))),
				0);
			if (!hits.next())
				return farm;
		}
	}
	return 0;
}
