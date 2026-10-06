// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doTeamGuardForFramecount@ScriptActions@@IAEXABVAsciiString@@H_N@Z @0x003C9363 161B.
// Team guard for framecount: resolve team by name, guard each member at its
// position via rowed aiGuardPosition, then set sequential timer on the team.
// Evidence: rowed iterate 0x00263864, rowed advance 0x00263526, rowed guard
// 0x0036F46A, rowed setSequentialTimer Team overload 0x00204002, pin getTeamNamed
// 0x003584E9, factor 0x00DBA4E4, TheScriptEngine 0x00DFE16C; unblocks none.
extern int g_Va00DBA4E4;

#include "ascii_string.h"
typedef bool Bool;
struct Coord3D { float x, y, z; };
class Object;
class AIUpdateInterface;
template<class OBJCLASS> class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

enum GuardMode { GUARDMODE_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x258);
	}
private:
	char m_pad00[0x38];
public:
	Coord3D m_position;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, Bool b);
	void setSequentialTimer(Team *team, int frames);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamGuardForFramecount(const AsciiString &teamName, int framecount, bool seconds);
};

void ScriptActions::doTeamGuardForFramecount(const AsciiString &teamName, int framecount, bool seconds)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (!team)
		return;
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	while (!iter.done()) {
		Object *object = iter.cur();
		AIUpdateInterface *ai = object->getAIUpdateInterface();
		if (ai) {
			Coord3D position;
			position.x = object->m_position.x;
			position.y = object->m_position.y;
			position.z = object->m_position.z;
			ai->m_command.aiGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
		}
		iter.advance();
	}
	if (seconds)
		TheScriptEngine->setSequentialTimer(team, framecount * g_Va00DBA4E4);
	else
		TheScriptEngine->setSequentialTimer(team, framecount);
}
