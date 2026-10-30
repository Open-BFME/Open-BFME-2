// cl: /O2 /G6 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /I.
// stlport
// Native math calls use the CRT IAT. Keep the headers' shared atof declaration
// consistent while selecting that import ABI.
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")
#pragma pop_macro("_CRTIMP")
namespace _STL { void __cdecl free(void *); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releasePartitionStorage(void *storage)
{
    _STL::free(storage);
}
// The target calls the ordinary STLport copy dispatch rather than force-inlining
// the BFME allocator shim's by-value copy dispatch into vector assignment.
#include "reference/open-bfme-1/inputs/vendor/stlport/stl/_algobase.h"
#include <vector>
struct Rva00627960Element { unsigned word0,word1; };
class Rva00627960Vector {public:Rva00627960Element*allocateCopy(unsigned,const Rva00627960Element*,const Rva00627960Element*);};
namespace _STL {
template <> template <> __declspec(dllimport) __forceinline
pair<int, int> *vector<pair<int, int> >::_M_allocate_and_copy<const pair<int, int> *>(
    unsigned int n, const pair<int, int> *first, const pair<int, int> *last)
{
    return (pair<int, int> *)((Rva00627960Vector *)this)->allocateCopy(
        n, (const Rva00627960Element *)first, (const Rva00627960Element *)last);
}
}

#include <algorithm>

// BFME1 9cbfb551 SetTreeDepth donor (reviewed at575ba2b04) supplies
// the quadtree-count algorithm and representation-compatible vector transfer.
// Target WB1681440 independently names SetTreeDepth. Native627E40..627F4A
// includes its RET4 (Ghidra omits the final3 bytes); native627AA0..627AD9
// ends in RET4 followed by padding and proves the57B zero-fill constructor.
// Retail uses the existing8B allocation and pair<int,int> assignment providers
// (6278F0/627CC0). These two-word views adapt those verified providers; they
// do not establish original tree-element typedefs or an ObjectID payload.
enum ObjectID;
typedef _STL::pair<ObjectID,unsigned int> PartitionRawPair;
typedef _STL::pair<int,int> PartitionAssignPair;

// These native vector releases call GameMemory's wrapper at 0x00030830.
// Keep that binding explicit without redirecting the CRT name in headers.
namespace _STL {
template<> inline void allocator<PartitionRawPair>::deallocate(
    PartitionRawPair *__p, size_type) const
{
    if (__p != 0) releasePartitionStorage((void *)__p);
}
template<> inline void allocator<PartitionAssignPair>::deallocate(
    PartitionAssignPair *__p, size_type) const
{
    if (__p != 0) releasePartitionStorage((void *)__p);
}
}

// PartitionManagerImpl::_ClearNumObjBelow and RemoveAllObjects.
// Target identity: WB167FEC0/WB1680940 name both methods and this source.
// Native626AA0..626AE8 and 627600..6276A3 prove their complete 72/163-byte
// boundaries. The count is quartered for each of four child quadrants.
// Native tree vectors begin at +0x18; there are 21; the master list is +0x114.
// BFME 1 9cbfb551 Rva009F40E0Recursive.cpp supplies the recovered recursion;
// its body was already byte-exact here. Target WB and native evidence supply
// the parent list reset and the 21-tree walk. Preserve existing linker names
// used by recovered providers and consumers while consolidating these bodies.
// Retail inlines the first recursion level in RemoveAllObjects; keeping the
// recursive definition in this TU also preserves its witnessed register use.
// ?_ClearNumObjBelow@PartitionManagerImpl@@QAEXPAPAXI@Z @0x00626AA0 72B:
// renamed from placeholder Rva009F40E0Owner::run — the WorldBuilder twin names
// PartitionManagerImpl::_ClearNumObjBelow at EA's own partitionmanager_impl.cpp
// line 180; the class and file are corroborated by the landed DoSmallFill
// (strings evidence, same file).
struct PartitionTreeCounter {
    int count;
    void *head;
    PartitionTreeCounter() : count(0), head(0) {}
};
struct PartitionNode {
    char pad00[0xc];
    PartitionNode *next;
    PartitionNode **prevInLeaf;
};

// WB names the owner PartitionManagerImpl; its destructor (0x00627DE0)
// runs cleanup and then destroys the 21 trees at +0x18.
struct Gen009F5040Node;
class PartitionManagerImpl {
public:
 void SetTreeDepth(unsigned);
 void linkNode(Gen009F5040Node*);
 void *GetClosestObject(int,float,int,int,int);
 void _ClearNumObjBelow(void **slot, unsigned count);
 __declspec(noinline) void cleanup();
 int prefix[6];
 _STL::vector<PartitionTreeCounter> trees[21];
 PartitionNode *head;
 float scale;
 int mask;
};
void PartitionManagerImpl::_ClearNumObjBelow(void **slot, unsigned count)
{
    if (*slot == 0) return;
    *slot = 0;
    unsigned childCount = count;
    slot += 2;
    childCount >>= 2;
    unsigned stride = count * 8;
    unsigned remaining = 4;
    while (remaining != 0) {
        _ClearNumObjBelow(slot, childCount);
        slot = (void **)((char *)slot + stride);
        --remaining;
    }
}

void PartitionManagerImpl::cleanup()
{
    for (PartitionNode *node = head; node; node = node->next) {
        *node->prevInLeaf = 0;
        node->prevInLeaf = 0;
    }
    if (trees[0].size() != 0) {
        for (int i = 0; i < 21; ++i)
            _ClearNumObjBelow((void **)trees[i].begin(), trees[0].size() / 4);
    }
}

class Rva00627AA0TreeVector : public _STL::_Vector_base<PartitionRawPair,_STL::allocator<PartitionRawPair> > {
 typedef _STL::_Vector_base<PartitionRawPair,_STL::allocator<PartitionRawPair> > Base;
public:
 Rva00627AA0TreeVector(unsigned n):Base(n,_STL::allocator<PartitionRawPair>()) {
  _M_finish=reinterpret_cast<PartitionRawPair*>(_STL::uninitialized_fill_n(reinterpret_cast<PartitionTreeCounter*>(_M_start),n,PartitionTreeCounter()));
 }
};

void PartitionManagerImpl::SetTreeDepth(unsigned depth)
{
    if (depth > 11) return;
    int value = 1 << depth;
    if (value == mask) return;
    mask = value;
    unsigned count = 1;
    while (depth != 0) {
        --depth;
        count = count * 4 + 1;
    }
    cleanup();
    for (int i = 0; i < 21; ++i) {
        Rva00627AA0TreeVector fresh(count);
        *reinterpret_cast<_STL::vector<PartitionAssignPair>*>(&trees[i]) = *reinterpret_cast<const _STL::vector<PartitionAssignPair>*>(&fresh);
    }
    for (PartitionNode *node = head; node; node = node->next)
        linkNode((Gen009F5040Node *)node);
}

// Native helper ignores receiver and allocates/copies8-byte elements. The
// application record identity and field types remain unknown; words are ABI
// carriers. STLport vector allocate/copy supplies the reference structure.
Rva00627960Element*Rva00627960Vector::allocateCopy(unsigned n,const Rva00627960Element*first,const Rva00627960Element*last){
 Rva00627960Element*result=n?(Rva00627960Element*)_STL::allocator<char>::allocate(n*sizeof(Rva00627960Element),0):0;
 for(const Rva00627960Element*p=first;p!=last;++p){Rva00627960Element*dest=(Rva00627960Element*)((char*)result+((const char*)p-(const char*)first));if(dest)*dest=*p;}
 return result;
}

// GetClosestObject: native 00628040..00628766 is 1830 bytes including RET14.
// WB 016816C0 names this method; BFME1 9cbfb551 supplies the quadtree algorithm.
// Target evidence gives 21 tree roots, 24-byte heap records, radius as float
// (caller 00625360), and a lazily initialized three-pointer vector at E09DBC.
// Record field names are structural inferences; provider names below retain
// their established storage identities. Advance the child cursor before the
// half-size calculation to preserve the native preheader and reload schedule.

struct BfmeCoord3D1050
{
	float m_x;
	float m_y;
	float m_z;
};

struct BfmeGeometry1050
{
	unsigned char m_bfmePad00[0x10];
	float m_radius;
};

class BfmeCandidate1050;

struct BfmeNode1050
{
	int m_hasChildren;
	class BfmeLink1050 *m_firstLink;
};

class BfmeLink1050
{
public:
	int m_bfmePad00;
	BfmeCandidate1050 *m_candidate;
	int m_bfmePad08[3];
	BfmeLink1050 *m_next;
};

class BfmeCandidate1050
{
public:
	virtual BfmeGeometry1050 *getGeometry(void) = 0;
	virtual BfmeCoord3D1050 *getPosition(void) = 0;
	virtual int getUnused(void) = 0;
	virtual void *getObject(void) = 0;
};

struct BfmeRegion1050
{
	float m_x0;
	float m_y0;
	float m_bfmePad08;
	float m_x1;
	float m_y1;
};

struct Rva009F56C0Element
{
	int m_key;
	struct BfmeNode1050 *m_node;
	unsigned int m_stride;
	int m_x;
	int m_y;
	int m_size;
};

namespace _STL {
template<> inline void allocator<Rva009F56C0Element>::deallocate(
    Rva009F56C0Element *__p, size_type) const
{
    if (__p != 0) releasePartitionStorage((void *)__p);
}
}

class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float value);
};

class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float value);
};

class Rva009F2AB0Mask
{
public:
	int getMask(void);
};

class Object;

// Partition filter base: allows (0x00625720) runs the chain from this filter
// along the +0x04 links.
class Rva000421C8
{
public:
	bool allows(Object *obj);
};

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
	char m_bfmeUnused;

	S4Cmp009F4BF0(void) : m_bfmeUnused(0) {}

	bool operator()(const S4SortElem24 &left, const S4SortElem24 &right) const
	{
		return left.m_key < right.m_key;
	}
};

typedef float (__cdecl *BfmeDistanceProc1050)(void *, void *, float);
extern BfmeDistanceProc1050 g_partitionDistance[];

typedef _STL::vector<BfmeNode1050> BfmeNodeVec1050;

// Native uses x87 FISTP here. An ordinary C++ cast changes the complete
// caller to 1780 bytes; retain this two-instruction donor conversion only.
__forceinline int bfmeFloatToInt1050(float value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

__forceinline unsigned int bfmeInlineCellX1050(PartitionManagerImpl *manager, float value)
{
	float t = (float)floor((double)((value - *(const float *)&manager->prefix[0]) *
		(float)(unsigned int)manager->mask * manager->scale));
	int i = bfmeFloatToInt1050(t);
	if (i < 0)
		return 0;
	return (unsigned int)i >= (unsigned int)manager->mask ? (unsigned int)manager->mask - 1 : i;
}


// Exact rowed 24-byte copy and vector-growth providers; their historical
// element names describe provider storage, not this query's element identity.
struct Rva00626EF0Element { int words[6]; };
#include "../../Include/Lib/Coord3D.h"
// bfme link decl-only begin
namespace _STL { template <> pair<int, int> * __uninitialized_copy<pair<int, int> const *, pair<int, int> *>(pair<int, int> const *, pair<int, int> const *, pair<int, int> *, __false_type const &); }
// bfme link decl-only end
enum ObjectID;
class FlightDeckBehavior { public: struct FlightDeckInfo { Coord3D m_prep; float m_orientation; int m_runway; ObjectID m_objectInSpace; }; };
// Native growth at 0x00627BC0 releases through GameMemory's 0x00030830
// wrapper, also used by the other vectors here, rather than the CRT import.
namespace _STL {
template<> inline void allocator<FlightDeckBehavior::FlightDeckInfo>::deallocate(
    FlightDeckBehavior::FlightDeckInfo *p, unsigned int) const
{
    if (p) releasePartitionStorage(p);
}
}
class ClosestFlightVector : public _STL::vector<FlightDeckBehavior::FlightDeckInfo> {
public: using _STL::vector<FlightDeckBehavior::FlightDeckInfo>::_M_insert_overflow;
};
namespace _STL {
template<class RandomAccessIterator,class Distance,class Tp,class Compare>
void __pop_heap(RandomAccessIterator,RandomAccessIterator,RandomAccessIterator,Tp,Compare,Distance *);
}
class ClosestWorkView : public _STL::vector<Rva009F56C0Element> {
public:
 __forceinline void clearExact() {
  _M_finish=(Rva009F56C0Element *)_STL::__copy((Rva00626EF0Element *)_M_finish,(Rva00626EF0Element *)_M_finish,(Rva00626EF0Element *)_M_start,_STL::random_access_iterator_tag(),(int*)0);
 }
 __forceinline void appendExact(const Rva009F56C0Element &value) {
  if(_M_finish != _M_end_of_storage._M_data) {
   _STL::_Construct(_M_finish,value);
   ++_M_finish;
  } else {
   ((ClosestFlightVector *)this)->_M_insert_overflow((FlightDeckBehavior::FlightDeckInfo *)_M_finish,*(const FlightDeckBehavior::FlightDeckInfo *)&value,_STL::__false_type(),1,true);
  }
 }
};
void *PartitionManagerImpl::GetClosestObject(int position, float maxDistance, int bounds,
	int distanceType, int filters)
{
	unsigned int filterMask;
	if (distanceType != 0 && distanceType != 2 &&
		distanceType != 1 && distanceType != 3)
		distanceType = 0;
	BfmeDistanceProc1050 distanceProc = g_partitionDistance[distanceType];

	if (filters)
		filterMask = ((Rva009F2AB0Mask *)filters)->getMask() * 2 + 1;
	else
		filterMask = 0xffffffff;

	Rva009F56C0Element current;
	static _STL::vector<Rva009F56C0Element> work;
    ((ClosestWorkView *)&work)->clearExact();
	BfmeNodeVec1050 *tree = reinterpret_cast<BfmeNodeVec1050 *>(trees);

	for (int treeCount = 21; treeCount; --treeCount)
	{
		if (filterMask & 1)
		{
            Rva009F56C0Element seed;
			seed.m_key = 0;
			seed.m_node = tree->begin();
			seed.m_stride = ((BfmeNodeVec1050 *)trees)[0].size() / 4;
			seed.m_y = 0;
			seed.m_x = 0;
			seed.m_size = (unsigned int)mask;
			((ClosestWorkView *)&work)->appendExact(seed);
		}
		++tree;
		filterMask >>= 1;
	}

	float &maxDistanceReal = maxDistance;

	if (maxDistanceReal < 0.00001f)
		return 0;

	float cellExtent = (unsigned int)mask * scale;
	if (maxDistanceReal * cellExtent > 32766.0f)
		maxDistanceReal = 32766.0f / cellExtent;

	float maxDistanceSquared = maxDistanceReal * maxDistanceReal;
	void *closestObject = 0;
	int maxRadius = bfmeFloatToInt1050((float)ceil(cellExtent * maxDistanceReal));
	int maxRadiusSquared = (maxRadius + 1) * (maxRadius + 1);

	BfmeCoord3D1050 *source = (BfmeCoord3D1050 *)position;
	int cellCenterX = ((BfmeHostER *)this)->bfmeIndexER(source->m_x);
	int cellCenterY = ((BfmeHostES *)this)->bfmeIndexES(source->m_y);

	BfmeRegion1050 *region = (BfmeRegion1050 *)bounds;
	int regionX0;
	int regionX1;
	int regionY0;
	int regionY1;
	if (region)
	{
		regionX0 = ((BfmeHostER *)this)->bfmeIndexER(region->m_x0);
		regionX1 = ((BfmeHostER *)this)->bfmeIndexER(region->m_x1);
		regionY0 = ((BfmeHostES *)this)->bfmeIndexES(region->m_y0);
		regionY1 = ((BfmeHostES *)this)->bfmeIndexES(region->m_y1);
	}

	while (!work.empty())
	{
		if (work.front().m_key > maxRadiusSquared)
			break;

		_STL::__pop_heap<S4SortElem24 *, int, S4SortElem24, S4Cmp009F4BF0>((S4SortElem24 *)work.begin(), (S4SortElem24 *)work.end()-1, (S4SortElem24 *)work.end()-1, *((S4SortElem24 *)work.end()-1), S4Cmp009F4BF0(), (int *)0);
		current = work.back();
		work.pop_back();

		for (BfmeLink1050 *link = current.m_node->m_firstLink; link;
			link = link->m_next)
		{
			float distance = distanceProc(source, link->m_candidate, 0);
			if (distance > maxDistanceSquared)
				continue;

			if (region)
			{
				BfmeCoord3D1050 *where = link->m_candidate->getPosition();
				if (where->m_x < region->m_x0)
					continue;
				if (where->m_y < region->m_y0)
					continue;
				if (where->m_x > region->m_x1)
					continue;
				if (where->m_y > region->m_y1)
					continue;
			}

			void *object = link->m_candidate->getObject();
			if (!object)
				continue;
			if (filters && !((Rva000421C8 *)filters)->allows((Object *)object))
				continue;

			maxDistanceSquared = distance;
			closestObject = object;
			BfmeGeometry1050 *geometry = link->m_candidate->getGeometry();
			BfmeCoord3D1050 *candidatePosition = link->m_candidate->getPosition();
			float radiusValue = geometry->m_radius;

			unsigned int xDistance =
				bfmeInlineCellX1050(this, candidatePosition->m_x - radiusValue) - cellCenterX;
			unsigned int xDistanceMaximum =
				bfmeInlineCellX1050(this, candidatePosition->m_x + radiusValue) - cellCenterX;
			unsigned int yDistance = ((BfmeHostES *)this)->bfmeIndexES(
				candidatePosition->m_y - radiusValue) - cellCenterY;
			unsigned int yDistanceMaximum = ((BfmeHostES *)this)->bfmeIndexES(
				candidatePosition->m_y + radiusValue) - cellCenterY;

			if (xDistanceMaximum > xDistance)
				xDistance = xDistanceMaximum;
			if (yDistanceMaximum > yDistance)
				yDistance = yDistanceMaximum;
			maxRadiusSquared = yDistance * yDistance + xDistance * xDistance;
		}

		if (!current.m_node->m_hasChildren)
			continue;

		current.m_node = current.m_node + 1;
		int half = current.m_size / 2;
		for (unsigned int groupIndex = 0; groupIndex < 4;
			++groupIndex, current.m_node += current.m_stride)
		{
			BfmeNode1050 *group = current.m_node;
			if (group->m_firstLink || group->m_hasChildren)
			{
				Rva009F56C0Element child;
				child.m_x = ((groupIndex & 1) ? half : 0) + current.m_x;
				child.m_y = current.m_y + ((groupIndex & 2) ? half : 0);

				int xDistance;
				if (cellCenterX < child.m_x)
				{
					int delta = child.m_x - cellCenterX - 1;
					xDistance = delta * delta;
				}
				else if (cellCenterX >= child.m_x + half)
				{
					int delta = cellCenterX - child.m_x - half;
					xDistance = delta * delta;
				}
				else
					xDistance = 0;

				int yDistance;
				if (cellCenterY < child.m_y)
					yDistance = (child.m_y - cellCenterY - 1) * (child.m_y - cellCenterY - 1);
				else if (cellCenterY >= child.m_y + half)
					yDistance = (cellCenterY - child.m_y - half) * (cellCenterY - child.m_y - half);
				else
					yDistance = 0;

				child.m_key = yDistance + xDistance;
				if (child.m_key <= maxRadiusSquared)
				{
					if (!region || (child.m_x <= regionX1 && child.m_y <= regionY1 &&
						child.m_x + half >= regionX0 && child.m_y + half >= regionY0))
					{
						child.m_node = group;
						child.m_size = half;
						child.m_stride = current.m_stride / 4;
						((ClosestWorkView *)&work)->appendExact(child);
						_STL::__push_heap_aux((S4SortElem24 *)work.begin(), (S4SortElem24 *)work.end(), S4Cmp009F4BF0(), (int *)0, (S4SortElem24 *)0);
					}
				}
			}
		}
	}
	return closestObject;
}
