// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
//
// ?privateFollowPathAppend@GiantBirdAIUpdate@@UAEXPBUCoord3D@@W4CommandSourceType@@@Z,
// retail 0x0036B961 (278 bytes, EH, RET 8). Slot 33 (+0x84) of the GiantBird
// vtable: AIUpdateInterface::privateFollowPathAppend (retail 0x0026E074, the
// slot the Worker vtable lists at the same index) with the bird's flight
// states. It clears the loop flag at +0x550, then: in state 0x3F6 with a
// goal path already queued (the state machine's vector<Coord3D> at +0x3C,
// 12-byte points) it appends the position to that path
// (AIStateMachine::addToGoalPath 0x0035385E); in the other flight states
// (above 0x3E8 and below 0x401 except 0x3ED and 0x3F4) it paths from the
// machine's goal position (+0x24) through the new one; otherwise just to the
// new one. The path goes to slot 30 (+0x78, privateFollowPath) with no ignore
// object, the command source and no production exit, as the base body does.
// The base's voice response is not played. WB has no name for it; the shape
// follows the base body in AIUpdateInterfacePrivateCommands.cpp and the
// sibling GiantBirdAIUpdateFollowWaypoints.cpp.
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

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

// Reuse the verified Coord3D push-back specialization at 0x002CE7DC.
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D &); }

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../../Include/GameLogic/AIStateMachineClass.h"

class GiantBirdAIUpdate : public AIUpdateInterface
{
public:
	virtual void privateFollowPathAppend(const Coord3D *pos, CommandSourceType commandSource);
private:
	char m_unrecovered3E4[0x550 - 0x3E4];
	bool m_pathLoops; // +0x550
};

void GiantBirdAIUpdate::privateFollowPathAppend(const Coord3D *pos, CommandSourceType commandSource)
{
	m_pathLoops = false;
	if (getCurrentStateID() == 0x3F6 && (int)reinterpret_cast<_STL::vector<Coord3D> *>(m_stateMachine->field3C)->size() > 0)
	{
		m_stateMachine->addToGoalPath(pos);
	}
	else if (getCurrentStateID() > 0x3E8 && getCurrentStateID() < 0x401
		&& getCurrentStateID() != 0x3ED && getCurrentStateID() != 0x3F4)
	{
		_STL::vector<Coord3D> path;
		path.push_back(m_stateMachine->m_goalPosition);
		path.push_back(*pos);
		privateFollowPath(reinterpret_cast<const Rva0035149F *>(&path), 0, commandSource, false);
	}
	else
	{
		_STL::vector<Coord3D> path;
		path.push_back(*pos);
		privateFollowPath(reinterpret_cast<const Rva0035149F *>(&path), 0, commandSource, false);
	}
}
