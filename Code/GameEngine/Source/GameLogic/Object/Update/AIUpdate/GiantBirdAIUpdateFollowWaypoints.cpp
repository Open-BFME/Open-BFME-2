// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
//
// ?privateFollowWaypointPath@GiantBirdAIUpdate@@QAEXPBVWaypoint@@0@Z, retail 0x0036BA77,
// 184 bytes (EH, RET 8). Address-derived name: GiantBirdAIUpdate's own
// follow-path-by-waypoints entry (it sits between the class's destructor
// 0x0036B8E6 and the next GiantBird bodies; owner by placement, not by name).
// Target evidence: it copies the float at +0x48 of the object at AI +0x1F0
// into +0x540 when present, clears the loop flag at +0x550, walks the waypoint
// chain (location at +0xC, first link at +0x20 while the link count at +0x4C
// is nonzero) appending each location to a local vector<Coord3D> through the
// rowed push_back 0x002CE7DC, sets +0x550 when the chain closes back on the
// first waypoint, then hands the vector, no object, the second waypoint and 0
// to the rowed 0x003697F9. Vector element and Waypoint layouts are views of the
// witnessed offsets only.
//
// Shape notes (bytes): retail copies each location member-wise into a fresh
// point (SSE float moves, not dword moves), which a non-POD point type gives;
// the waypoint test after the vector is built is an early return, which keeps
// the register restores in the shared exit after the vector's free (a single
// if-block lets cl hoist them above the free test). /EHs with the bfmealloc
// free keeps the unwind state store retail emits before that free, as in
// AIUpdateInterfacePrivateCommands.cpp.
#include <vector>
#include "Lib/Coord3D.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<Coord3D>::deallocate(Coord3D* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<Coord3D*,Coord3D,allocator<Coord3D> >::deallocate(Coord3D* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<Coord3D>&>(*this),(Coord3D*)0).deallocate(__p,__n);
}
template <> __declspec(dllimport) __forceinline
_Vector_base<Coord3D,allocator<Coord3D> >::~_Vector_base() {
 if (_M_start != 0) _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start);
}
}

class Object;
class Rva0035149F;

// A waypoint location copied member-wise into the path.
struct GiantBirdPathPoint : public Coord3D
{
	GiantBirdPathPoint(const Coord3D &o) throw() { x = o.x; y = o.y; z = o.z; }
};

// Reuse the verified Coord3D push-back specialization at 0x002CE7DC.
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D &); }

#include "../../../../../Include/GameLogic/Waypoint.h"

struct Rva0036BA77Speed
{
	char m_unrecovered00[0x48];
	float m_speed;				///< 0x48
	float getSpeed() const { return m_speed; }
};

class GiantBirdAIUpdate
{
public:
	// 0x003697F9 (Rva003697F9.cpp): follow the built point path.
	void privateFollowPath(const Rva0035149F &path, const Object *object, const Waypoint *goal, int flag);
	void privateFollowWaypointPath(const Waypoint *way, const Waypoint *goal);
private:
	char m_unrecovered000[0x1F0];
	Rva0036BA77Speed *m_speedSource;	///< 0x1F0
	char m_unrecovered1F4[0x540 - 0x1F4];
	float m_speed;						///< 0x540
	char m_unrecovered544[0x550 - 0x544];
	bool m_pathLoops;					///< 0x550
};

void GiantBirdAIUpdate::privateFollowWaypointPath(const Waypoint *way, const Waypoint *goal)
{
	if (m_speedSource)
		m_speed = m_speedSource->getSpeed();
	m_pathLoops = false;
	_STL::vector<Coord3D> path;
	if (!way)
		return;
	const Waypoint *cur = way;
	for (;;)
	{
		GiantBirdPathPoint point(cur->m_location);
		path.push_back(point);
		if (cur->m_numLinks == 0)
			break;
		cur = cur->m_links[0];
		if (cur == way)
		{
			m_pathLoops = true;
			break;
		}
	}
	privateFollowPath(*(const Rva0035149F *)&path, NULL, goal, 0);
}
