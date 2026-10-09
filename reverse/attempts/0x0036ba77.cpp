// ?rva0036BA77@GiantBirdAIUpdate@@QAEXPBVWaypoint@@0@Z
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0036BA77@GiantBirdAIUpdate@@QAEXPBVWaypoint@@0@Z, retail 0x0036BA77,
// 184 bytes (EH, RET 8). Address-derived name: GiantBirdAIUpdate's own
// follow-path-by-waypoints entry. Target evidence: it copies the float at +0x48
// of the object at AI +0x1F0 into +0x540 when present, clears the loop flag at
// +0x550, walks the waypoint chain (location at +0xC, first link at +0x20 while
// the link count at +0x4C is nonzero) appending each location to a local
// vector<Coord3D> through the rowed push_back 0x002CE7DC, sets +0x550 when the
// chain closes back on the first waypoint, then hands the vector, no object, the
// second waypoint and 0 to the rowed 0x003697F9. Vector element and Waypoint
// layouts are views of the witnessed offsets only.
#include <vector>
// A TU-local Coord3D with a member-wise copy (the rowed vector<Coord3D>
// push_back 0x002CE7DC is built from the same spelling); the canonical header
// has no copy constructor and would copy through REP MOVS.
struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &o) throw() : x(o.x), y(o.y), z(o.z) {}
};
void Rva00030830FreeAllocation(void *);

class Object;

class Waypoint
{
public:
	char m_pad0[0xC];
	Coord3D m_location; // +0x0C
	char m_pad18[0x20 - 0x18];
	const Waypoint *m_next; // +0x20 (first link)
	char m_pad24[0x4C - 0x24];
	int m_numLinks; // +0x4C
};

namespace _STL {
template<> void vector<Coord3D>::push_back(const Coord3D &);
template<> inline void allocator<Coord3D>::deallocate(Coord3D *p, size_t) const { if (p) ::Rva00030830FreeAllocation(p); }
}

class Rva0035149F;

struct Rva1F0Object
{
	char m_pad[0x48];
	float m_48;
	float get48() const { return m_48; }
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
	char m_pad[0x1F0];
	Rva1F0Object *m_1F0;
	char m_pad1F4[0x540 - 0x1F4];
	float m_540;
	char m_pad544[0x550 - 0x544];
	bool m_550;
};

void GiantBirdAIUpdate::rva0036BA77(const Waypoint *way, const Waypoint *goal)
{
	const int zero = 0;
	if (m_1F0 != (Rva1F0Object *)zero)
		m_540 = m_1F0->get48();
	m_550 = zero != 0;
	_STL::vector<Coord3D> path;
	if (way != (const Waypoint *)zero)
	{
		const Waypoint *cur = way;
		for (;;)
		{
			Coord3D point = cur->m_location;
			path.push_back(point);
			if (cur->m_numLinks == zero)
				break;
			cur = cur->m_next;
			if (cur == way)
			{
				m_550 = true;
				break;
			}
		}
		((Rva003697F9 *)this)->rva003697F9(*(const Rva0035149F *)&path, (const Object *)zero, goal, zero);
	}
}
