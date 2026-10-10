// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
//
// ?rva0036BA77@GiantBirdAIUpdate@@QAEXPBVWaypoint@@0@Z, retail 0x0036BA77,
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

class Object;
class Rva0035149F;

// A waypoint location copied member-wise into the path.
struct GiantBirdPathPoint : public Coord3D
{
	GiantBirdPathPoint(const Coord3D &o) throw() { x = o.x; y = o.y; z = o.z; }
};

// Reuse the verified Coord3D push-back specialization at 0x002CE7DC.
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D &); }

class Waypoint
{
public:
	char m_unrecovered00[0xC];
	Coord3D m_location;			///< 0x0C
	char m_unrecovered18[0x20 - 0x18];
	const Waypoint *m_link;		///< 0x20 (first link)
	char m_unrecovered24[0x4C - 0x24];
	int m_numLinks;				///< 0x4C
};

struct Rva0036BA77Speed
{
	char m_unrecovered00[0x48];
	float m_speed;				///< 0x48
	float getSpeed() const { return m_speed; }
};

class Rva003697F9
{
public:
	void rva003697F9(const Rva0035149F &path, const Object *object, const Waypoint *goal, int flag);
};

class GiantBirdAIUpdate
{
public:
	void rva0036BA77(const Waypoint *way, const Waypoint *goal);
private:
	char m_unrecovered000[0x1F0];
	Rva0036BA77Speed *m_speedSource;	///< 0x1F0
	char m_unrecovered1F4[0x540 - 0x1F4];
	float m_speed;						///< 0x540
	char m_unrecovered544[0x550 - 0x544];
	bool m_pathLoops;					///< 0x550
};

void GiantBirdAIUpdate::rva0036BA77(const Waypoint *way, const Waypoint *goal)
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
		cur = cur->m_link;
		if (cur == way)
		{
			m_pathLoops = true;
			break;
		}
	}
	((Rva003697F9 *)this)->rva003697F9(*(const Rva0035149F *)&path, NULL, goal, 0);
}
