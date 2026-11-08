// Donor874e38488 game/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp
// supplies waypoint-path traversal and list ownership. Target diagnostic BFB230
// independently names buildBeacons; retail283E9C..283FAA fixes list+64 slot84
// and three-zero debug stream. Native waypoints share0C/1C/20/4C/60 accesses.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
namespace _STL {void __cdecl free(void *) throw(...);}
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseBeaconStorage(void *storage)
{
	_STL::free(storage);
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef float Real;
typedef int Int;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
// bfme link decl-only begin
namespace _STL { template <> _List_node<Coord3D> * list<Coord3D, allocator<Coord3D> >::_M_create_node(Coord3D const &); }
// bfme link decl-only end
// Retail inlines list<Coord3D>'s node deallocate everywhere and has no
// out-of-line copy; another unit's copy is first in link order, so dllimport
// keeps this unit's inline-only.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<Coord3D> >::deallocate(_List_node<Coord3D> *__p, size_t) const
{ if (__p != 0) releaseBeaconStorage((void *)__p); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<Coord3D> *, _List_node<Coord3D>, allocator<_List_node<Coord3D> > >::deallocate(_List_node<Coord3D> *__p, size_t __n)
{ allocator<_List_node<Coord3D> >::deallocate(__p, __n); }
}

typedef _STL::list<Coord3D> Coord3DList;
namespace _STL {
template <> inline void allocator<_List_node<Coord3DList> >::deallocate(_List_node<Coord3DList> *__p, size_t) const
{ if (__p != 0) releaseBeaconStorage((void *)__p); }
}

// Target outer nodes own a coordinate list: clear283002 calls its5B
// destructor200667 and copy construction in282843 calls coordinate-list copy2820DD.
typedef Coord3DList BeaconPath00283E9C;

// Layout shared with the matched TerrainLogic::newMap: the location is at
// +0x0c and the all-waypoints link at +0x1c.  The remaining reads keep
// offset-derived names; no witness names them.
class Waypoint
{
public:
	Waypoint *getNext(void) const
	{
		return m_next;
	}

	Waypoint *getPtr20(void) const
	{
		return m_ptr_20;
	}

	Int getDword4C(void) const
	{
		return m_dword_4c;
	}

	Int getDword60(void) const
	{
		return m_dword_60;
	}

	unsigned char m_unreconstructed_00[0x0c];
	Coord3D m_location;
	unsigned char m_unreconstructed_18[4];
	Waypoint *m_next;
	Waypoint *m_ptr_20;
	unsigned char m_unreconstructed_24[0x28];
	Int m_dword_4c;
	unsigned char m_unreconstructed_50[0x10];
	Int m_dword_60;
};


#include "../../Common/debug.h"

extern Debug *theDebug;
#define TheDebug theDebug
extern void _bfme_debugRecordCallsite(int kind);
extern bool bfmeRva000387C0(void);

#include "../../../Include/GameLogic/TerrainLogic.h"

void TerrainLogic::buildBeacons(void)
{
	field64.clear();

	for (Waypoint *start = getFirstWaypoint(); start != 0; start = start->getNext())
	{
		if (start->getDword60() != 5)
			continue;

		BeaconPath00283E9C path;

		for (Waypoint *way = start;;)
		{
			Coord3D point;
			point.x = way->m_location.x;
			point.y = way->m_location.y;
			point.z = way->m_location.z;
			path.push_front(point);

			Int links = way->getDword4C();
			if (links == 0)
				break;

			if (links != 1)
			{
				if (bfmeRva000387C0())
				{
					_bfme_debugRecordCallsite(1);
					TheDebug->SkipNext();
					(TheDebug->CrashBegin(0, 0, 0) << "TerrainLogic::buildBeacons - A beacon waypoint path has more than one link. Not allowed.").CrashDone(2);
				}

				path.clear();
				break;
			}

			way = way->getPtr20();
			if (way == start)
				break;
			if (way == 0)
				break;
		}

		if (!path.empty())
			field64.push_front(path);
	}
}
