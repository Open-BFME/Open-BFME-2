// cl: /EHs /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/shims/bfmelist /ICode/GameEngine/Include/GameLogic /I. /ICode/Libraries/Include -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI /Ireference/shims/bfme2_ascii
// stlport
// ?rva0036FAF8@Rva0036FAF8@@QAEXPBVWaypoint@@W4CommandSourceType@@H@Z @0x0036FAF8 95B
// Group forward with m_formationID clear plus mode switch: mode 1 via rowed rva00352F9D
// with 0x7FFFFFFF, mode 0 via rowed aiFollowWaypointPathAsTeam, same list-at-+4
// plus Object+0x258 plus +0x20 subobject loop as AIGroupWaypointMode and BfmeCommand33.
// Evidence: calls 0x00352F9D 0x0036ED4C; callers 0x003BF1D6 0x003BF4BC 0x003BF5EB;
// precedent AIGroupWaypointMode.cpp switch plus AIGroupBfmeCommand33.cpp m_formationID clear.
#include <list>
namespace _STL {template<class T,class L,class R> static __forceinline bool operator!=(const _List_iterator<T,L>&a,const _List_iterator<T,R>&b){return a._M_node!=b._M_node;}}

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Rva00352F9D
{
public:
	void rva00352F9D(const void *waypoint, int intVal, CommandSourceType cmdSource);
};

class AICommandInterface
{
public:
	void aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	union
	{
		AICommandInterface m_commands;
		Rva00352F9D m_rvaHolder;
	};
};

class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x410 - 0x25C];
	int m_formationID;
};

class Rva0036FAF8
{
public:
	void rva0036FAF8(const Waypoint *waypoint, CommandSourceType cmdSource, int mode);
private:
	char m_pad00[4];
	std::list<Object *> m_memberList;
};

void Rva0036FAF8::rva0036FAF8(const Waypoint *waypoint, CommandSourceType cmdSource, int mode)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		obj->m_formationID = 0;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai == 0)
			continue;
		switch (mode)
		{
		case 1:
			reinterpret_cast<Rva00352F9D*>(&ai->m_commands)->rva00352F9D(waypoint, 0x7FFFFFFF, cmdSource);
			break;
		case 0:
			ai->m_commands.aiFollowWaypointPathAsTeam(waypoint, cmdSource);
			break;
		default:
			break;
		}
	}
}
