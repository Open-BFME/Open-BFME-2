// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /G7
// ?rva00490AC5@ArrowStormUpdate@@QAEXXZ
// partial score=0.985 date=2026-10-19
// ?rva00490AC5@ArrowStormUpdate@@QAEXXZ
// partial score=0.9787234042553191 date=2026-10-19
// 0x00490AC5 bank 2026-10-19 (claude-opus-5-5): hack-free 470/470, 7 differing bytes, all frame offsets
// (module-data spill -0x20 vs retail -0x1c, ID slot -0x1c vs -0x20); the old bank had 10 bytes and six
// equal-arm ternaries. Levers: BitFlags<218> m_kindof with forceinline test/isKindOf returning unsigned
// long (a bool return breaks codegen); WB twin 0x11DD160 order (Object *obj before data) and tail shape.
// Retail uses two separate ID temporaries (WB local_64/local_68) that share one slot; ours only shares
// them in straight-line code. Lead: the two lists are different real STLport types (the +0x88 list's
// push_back is out of line at 0x2A1B6F, the local list inlines insert(end(),x) -> 0x2A1316).
// Home: new Code/GameEngine/Source/GameLogic/Object/Update/ArrowStormUpdate.cpp. Scratch: build/nbr/r4/490ac5/.
// stlport
// r34 2026-10-20 (claude-opus-5-5): EXACT 470/470, all calls resolved. Two levers together:
// (1) WB-faithful unnamed ID temporaries (WB local_64/local_68): m_88.push_back(other->getID())
//     and extra.pushBackInline(other->getID()); each temp has 2 refs, below data's weight, so the
//     temps get the lower slot (-0x20) and data -0x1c as in retail.
// (2) The callee chain that receives the second temp's address is visible in the TU as
//     retail-exact inline __declspec(noinline) copies: Rva002A1B6FNativeList::insert (0x2A1316, 37B
//     exact, its pinned name) and Rva0029FB80Store (0x29FB80, 28B exact, its row name). VC7.1 then
//     sees the temp's address does not escape, ends its lifetime at the call, and packs both ID
//     temps into one slot (in a loop of an EH function an escaping last temp stays live across the
//     back edge and conflicts with the first). Real STLport list<ObjectID>::push_back (visible
//     insert/_M_create_node) gives the same frame (scratch u3), i.e. the DamageField pooled list.
// Notes kept from the earlier banks of this body:
// W9-O3 2026-10-16: both list calls now resolve: push_back -> the pinned BridgeBehaviorObjectIDList::push_back (0x2A1B6F) view, the inline insert -> the pinned private Rva002A1B6FNativeList::insert (0x2A1316, member/aggregate-result ABI) through a friend view (no alternatename). Size exact nd 19: (1) three 4-byte frame homes rotated (retail data -0x1c, extra -0x18, id temp -0x20; ours -0x20/-0x1c/-0x18); (2) size() walks keep head in ECX/cursor EAX where retail has EAX/ECX. Inert/worse: p != m_node, first/last distance forms, iterator pair.
// ArrowStormUpdate's target gathering 0x00490AC5, tail-called by its slot-15
// override 0x00490D0A after the +0x88 list is reset (ArrowStormUpdateSlots.cpp).
// Every alive object other than this one that 0x00260EB1 accepts with flags
// 1 within the module data's +0xCC radius of the +0x44 target point (BFME2's
// partition filter chain, the view AIStructureCreepTactic.cpp documents) and
// whose template has none of the tested KindOf bits goes into the +0x88
// list, and also into a local list when its template has +0x109 bit 2. A
// non-empty +0x88 list short of the data's +0xD8 count is then topped up by
// cycling through the local list (or through itself when the local list is
// empty).
// Keep standard iterator methods inline; use the rowed external helpers.
namespace _STL { struct __declspec(dllimport) _List_iterator_base; }
#include <list>
// Compare the list nodes locally, as HordeContainXfer does, so this unit
// does not emit a losing _List_iterator_base::operator!= copy.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

class Object;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C flags,
// +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};


#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

template<int NUMBITS> class BitFlags
{
public:
	unsigned long m_words[(NUMBITS + 31) / 32];
	__forceinline unsigned long test(unsigned pos) const { return m_words[pos / 32] & (1UL << (pos % 32)); }
};

#include "../../../../Include/Common/ThingTemplate.h"

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_id;		// +0x74
};

// STLport list<ObjectID>: nodes +0 next, +4 previous, +8 the ID.
struct Rva0029FB3BNode
{
	Rva0029FB3BNode *m_next;
	Rva0029FB3BNode *m_previous;
	ObjectID m_value;
};

struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
	~Rva0029FB3BAlloc() {}
};

struct Rva0029FB3BIter
{
	Rva0029FB3BIter(Rva0029FB3BNode *node) : m_node(node) {}
	Rva0029FB3BIter(const Rva0029FB3BIter &that) : m_node(that.m_node) {}
	Rva0029FB3BNode *m_node;
};

struct Rva002A1316Iterator
{
	explicit Rva002A1316Iterator(void *p) : node(p) {}
	Rva002A1316Iterator(const Rva002A1316Iterator &other) : node(other.node) {}
	void *node;
};
class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &id);	// 0x002A1B6F
};
class Rva0029FB3BMember;
class Rva002A1B6FNativeList
{
	friend class Rva0029FB3BMember;
	Rva002A1316Iterator insert(Rva002A1316Iterator pos, void *const &value);	// 0x002A1316
};
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool;
__declspec(noinline) void *__stdcall Rva0029FB80Store(void **p)
{
	void *node = g_freelistPool.pop();
	void **q = (void **)((char *)node + 8);
	if (q)
		*q = *p;
	return node;
}
inline __declspec(noinline) Rva002A1316Iterator Rva002A1B6FNativeList::insert(Rva002A1316Iterator pos, void *const &value)
{
	void *node = Rva0029FB80Store((void **)&value);
	void *next = *(void **)((char *)pos.node + 4);
	*(void **)node = pos.node;
	*(void **)((char *)node + 4) = next;
	*(void **)next = node;
	*(void **)((char *)pos.node + 4) = node;
	return Rva002A1316Iterator(node);
}

class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc());	// 0x0029FB3B
	~Rva0029FB3BMember() throw();	// 0x00268902
	bool empty() const { return m_node->m_next == m_node; }
	unsigned size() const
	{
		return ((_STL::list<ObjectID> const *)this)->size();
	}
	Rva0029FB3BIter end() { return Rva0029FB3BIter(m_node); }
	__forceinline void push_back(const ObjectID &id) { ((BridgeBehaviorObjectIDList *)this)->push_back(id); }
	__forceinline void pushBackInline(const ObjectID &id) { ((Rva002A1B6FNativeList *)this)->insert(Rva002A1316Iterator(m_node), *(void *const *)&id); }
	void reset();	// 0x0026549E
	Rva0029FB3BNode *m_node;
};

struct ArrowStormUpdateModuleData
{
	unsigned char m_pad00[0xCC];
	float m_CC;		// +0xCC the radius
	unsigned char m_padD0[0xD8 - 0xD0];
	unsigned m_maxShots;		// +0xD8 the count
};

class ModuleData;
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
	void rva00490AC5();
private:
	Rva0029FB3BMember m_88;	// +0x88
};

void ArrowStormUpdate::rva00490AC5()
{
	Object *obj = m_object;
	const ArrowStormUpdateModuleData *data = (const ArrowStormUpdateModuleData *)m_moduleData;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_targetPos, data->m_CC, 0,
		Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 1);
	Rva0029FB3BMember extra;
	Object *other;
	while ((other = hits.next()) != 0) {
		if (((other->getTemplate()->m_kindof[3] & 0x100U) != 0) || ((other->getTemplate()->m_kindof[2] & 0x2000000U) != 0)
				|| ((other->getTemplate()->m_kindof[1] & 0x8000U) != 0) || ((other->getTemplate()->m_kindof[4] & 0x400000U) != 0)
				|| ((other->getTemplate()->m_kindof[1] & 0x400000U) != 0) || ((other->getTemplate()->m_kindof[4] & 0x40U) != 0))
			continue;
		m_88.push_back(other->getID());
		if (((other->getTemplate()->m_kindof[0] & 0x400U) != 0))
			extra.pushBackInline(other->getID());
	}
	if (m_88.size() == 0)
		return;
	if (m_88.size() < data->m_maxShots) {
		Rva0029FB3BMember *source = &m_88;
		if (!extra.empty())
			source = &extra;
		Rva0029FB3BNode *it = source->m_node->m_next;
		while (m_88.size() < data->m_maxShots) {
			m_88.push_back(it->m_value);
			it = it->m_next;
			if (it == source->m_node)
				it = source->m_node->m_next;
		}
	}
	extra.reset();
}
