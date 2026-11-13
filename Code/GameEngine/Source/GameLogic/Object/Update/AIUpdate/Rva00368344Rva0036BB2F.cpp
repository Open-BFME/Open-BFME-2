// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
//
// ?rva0036BB2F@Rva00368344@@QAEXPBVWaypoint@@_NH@Z, retail 0x0036BB2F
// (330 bytes, EH, RET 0xC). The GiantBird update's waypoint-path command
// (aiDoCommand 0x0036BC79 calls it for commands 6/0x32 with false and 7/0x33
// with true; its third argument is the command source word, passed on to the
// rowed setGoalWaypoint 0x003E3BFB the way the siblings in Rva00368344.cpp do).
// It is GiantBirdAIUpdateFollowWaypoints.cpp's 0x0036BA77 walk (speed copy
// from the object at +0x1F0, loop flag +0x550, a vector<Coord3D> of the
// waypoint locations) with the 0x003697F9 tail done inline: for a mobile owner
// (Object +0x438 bit 0 clear, rowed 0x002907A1) the machine (+0x30) slot 5 runs,
// its goal position becomes the last point (range FLT_MAX, 0x004D745C), the
// path is assigned to the machine (0x00351759), the goal waypoint is set and
// the machine enters 0x3F7 (plus one when the flag is set).
// Boundary and shape proven by retail bytes; the name stays address-derived.
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
// The path vector as the rowed machine path assignment sees it (STLport vector<Coord3D>).
class Rva0035149F
{
public:
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;
};

struct GiantBirdPathPoint : public Coord3D
{
	GiantBirdPathPoint(const Coord3D &o) throw() { x = o.x; y = o.y; z = o.z; }
};

namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D &); }

#include "../../../../../Include/GameLogic/Waypoint.h"

// Slot 2 of the retail tables is the class-name getter.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../object.h"

class AIStateMachine
{
public:
	void setGoalWaypoint(const Waypoint *goal); // 0x003E3BFB
};

#include "../../../../../Include/Common/Rva00351759.h"

#include "../../../../../Include/Common/StateMachineClass.h"

struct Rva0036BB2FSpeed
{
	char m_unrecovered00[0x48];
	float m_speed; // +0x48
	float getSpeed() const { return m_speed; }
};

class Rva00368344
{
public:
	void rva0036BB2F(const Waypoint *way, bool flag, int cmdSource);
private:
	char m_unrecovered00[0x8];
	Object *m_object; // +0x08
	char m_unrecovered0C[0x30 - 0x0C];
	StateMachine *m_machine; // +0x30
	char m_unrecovered34[0x1F0 - 0x34];
	Rva0036BB2FSpeed *m_speedSource; // +0x1F0
	char m_unrecovered1F4[0x540 - 0x1F4];
	float m_speed; // +0x540
	char m_unrecovered544[0x550 - 0x544];
	bool m_pathLoops; // +0x550
};

void Rva00368344::rva0036BB2F(const Waypoint *way, bool flag, int cmdSource)
{
	if (m_object->m_privateStatus & 1)
		return;
	if (!m_object->isMobile())
		return;
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
	m_machine->clear();
	unsigned int n = (unsigned int)path.size();
	if (n > 0)
	{
		GiantBirdPathPoint last(path[n - 1]);
		StateMachine *machine = m_machine;
		machine->setGoalPosition(&last, 3.402823466e+38f);
	}
	((Rva00351759 *)m_machine)->rva00351759(*(const Rva0035149F *)&path);
	((AIStateMachine *)this)->setGoalWaypoint((const Waypoint *)cmdSource);
	m_machine->setState(0x3F7 + (flag ? 1 : 0));
}
