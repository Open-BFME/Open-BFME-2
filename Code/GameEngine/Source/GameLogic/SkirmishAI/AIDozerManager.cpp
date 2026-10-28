// Identity: WB twin 0x01530980 (AIDozerManager.cpp asserts 247/273); siblings
// buildDozer 0x00599564, rva00599AE3 0x00599AE3, rva00599EDC 0x00599EDC.
// The lookup chain (ObjectIdMap::find 0x002888D4 and GameLogic::findObjectByID
// 0x00049DC5, both rowed COMDAT copies as in ProjectileNuggetObjectEffect.cpp)
// is visible in this unit; with it cl gives the outer and inner iterators EBX
// and the factory EDI, as retail does. The 8-byte keyframe vector's push_back
// is the ICF-folded body at 0x00539A2E (fold-proof pin from this unit).
// cl: /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /O1 /G7 /arch:SSE /MD /EHsc
// stlport
// Retail frees vector storage through the C++-linkage free (0x00030830),
// which keeps the unwind-state store before the call.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <list>
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper
// (retail keeps one _List_iterator_base::operator!=; BfmeAptScreenLanLobbyOnInitGadget.cpp pattern).
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#include <algorithm>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end

extern GameLogic *TheGameLogic;
struct AIDozerLookupNode { AIDozerLookupNode *next; ObjectID key; Object *object; };
struct AIDozerLookupBuckets {
 AIDozerLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 AIDozerLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct AIDozerLookupMap { unsigned char hashEqual[4]; AIDozerLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 AIDozerLookupMap *map=(AIDozerLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 AIDozerLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	__declspec(dllimport) bool isDestroyed() const { return (m_status438 & 1) != 0; }
private:
	char m_pad000[0x38];
	Coord3D m_pos;
	char m_pad044[0x438 - 0x44];
	unsigned char m_status438;
};

struct Rva00599435Keyframe
{
	float m_value;
	unsigned int m_frame;
};

struct Rva00599435Compare
{
	bool operator()(const Rva00599435Keyframe &a, const Rva00599435Keyframe &b) const { return a.m_value > b.m_value; }
};
// The sort chain is rowed in stlport_rva00599435keyframe_linear_insert.cpp;
// call that copy rather than emitting this unit's own.
namespace _STL { template <> void sort<Rva00599435Keyframe *, Rva00599435Compare>(Rva00599435Keyframe *, Rva00599435Keyframe *, Rva00599435Compare); }

// Coord3D::sub and Coord3D::GetLengthSqrd2D as the WB twin calls them;
// retail inlines both.
static inline void subCoord3D(Coord3D *dst, const Coord3D *source)
{
	dst->x -= source->x;
	dst->y -= source->y;
	dst->z -= source->z;
}
static inline float lengthSqrd2D(const Coord3D *coord)
{
	float x_value = coord->x;
	float y_value = coord->y;
	return x_value * x_value + y_value * y_value;
}

class AIDozerManager
{
public:
	void buildDozer(Object *factory);
	bool rva00599AE3(Object *factory);
	void preEmptivelyBuildDozers();
private:
	_STL::list<ObjectID> m_dozers;
	_STL::list<ObjectID> m_factories;
};

void AIDozerManager::preEmptivelyBuildDozers()
{
	if (m_dozers.size() >= m_factories.size())
		return;
	_STL::vector<Rva00599435Keyframe> candidates;
	_STL::list<ObjectID>::iterator end = m_factories.end();
	for (_STL::list<ObjectID>::iterator it = m_factories.begin(); it != end; ++it) {
		Object *factory = TheGameLogic->findObjectByID(*it);
		if (factory == 0 || factory->isDestroyed() || !rva00599AE3(factory))
			continue;
		Rva00599435Keyframe candidate;
		candidate.m_value = 0.0f;
		candidate.m_frame = (unsigned int)factory;
		for (_STL::list<ObjectID>::iterator d = m_dozers.begin(); d != m_dozers.end(); ++d) {
			Object *dozer = TheGameLogic->findObjectByID(*d);
			Coord3D delta;
			delta.x = dozer->getPosition()->x;
			delta.y = dozer->getPosition()->y;
			delta.z = dozer->getPosition()->z;
			subCoord3D(&delta, factory->getPosition());
			float dist = lengthSqrd2D(&delta);
			if (dist > candidate.m_value)
				candidate.m_value = dist;
		}
		candidates.push_back(candidate);
	}
	if (!candidates.empty()) {
		_STL::sort(candidates.begin(), candidates.end(), Rva00599435Compare());
		unsigned int count = m_factories.size() - m_dozers.size();
		if (count != 0)
			for (Rva00599435Keyframe *candidateIter = candidates.begin(); candidateIter != candidates.end() && count > 0; ++candidateIter, --count)
				buildDozer((Object *)candidateIter->m_frame);
	}
}
