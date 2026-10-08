// cl: /O1 /DNDEBUG /MD
// ?isPathAvailable@AIUpdateInterface@@QBE_NPBUCoord3D@@@Z @0x00262B53 42B.
// Evidence: thiscall with ret 4 and bool return; global g_Va009FF0F8 AI plus 0x10 pathfinder; callee QuickDoesPathExist pin with object plus from plus to plus 0; neighbours AIUpdateInterface /O1.
// Identity: WorldBuilder's AIUpdate.cpp:3661 asserts in AIUpdateInterface::isPathAvailable,
// whose body is this one (null check, m_object +0x40 position, TheAI->pathfinder()
// +0x10, Pathfinder::QuickDoesPathExist 0x002F477E with a trailing 0); Zero Hour's
// isPathAvailable has the same shape. The +0x38 position offset is retail's.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_38;
};
class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int x);
};
class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_10;
};
extern AI *TheAI;
class AIUpdateInterface
{
public:
	bool isPathAvailable(const Coord3D *destination) const;
private:
	char m_pad[8];
	Object *m_object;
};
bool AIUpdateInterface::isPathAvailable(const Coord3D *destination) const
{
	if (!destination)
		return false;
	Object *obj = m_object;
	Pathfinder *pf = TheAI->m_10;
	return pf->QuickDoesPathExist(obj, &obj->m_38, destination, 0);
}
