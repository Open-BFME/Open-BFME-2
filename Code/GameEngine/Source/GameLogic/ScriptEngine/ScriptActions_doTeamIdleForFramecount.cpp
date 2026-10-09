// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ScriptActions::doTeamIdleForFramecount, retail 0x003C0C71 (125 bytes), called
// from the action dispatcher 0x003CA4BE. The team-wide twin of
// doUnitIdleForFramecount 0x003C9311 (Zero Hour ScriptActions.cpp spelling; the
// BFME2 seconds flag scales the count by the logic frames per second
// 0x00DBA4E4): the team's group (AI::createGroup, Team::getTeamAsAIGroup) is
// ordered idle from a script (groupIdle 0x0076FC23; its centre is queried
// first, 0x0076D035), then the script engine's sequential timer for the team
// is set to the frame count.
extern int g_Va00DBA4E4;

#include "ascii_string.h"
typedef bool Bool;
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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x258);
	}
};

class AICommandInterface
{
public:
	void aiExit(Object *obj, CommandSourceType cmdSource);	// 0x0076F39B
};

class AIUpdateInterface
{
public:
	unsigned char pad[0x20];
	AICommandInterface command;
};

class AIGroup
{
public:
	Bool getCenter(Coord3D *center);			// 0x0036D035
	void groupIdle(CommandSourceType cmdSource);		// 0x0036FC23
};

class AI
{
public:
	AIGroup *createGroup();					// 0x002FEC4B
};
extern AI *TheAI;

class Team
{
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void getTeamAsAIGroup(AIGroup *group);			// 0x003A0F62
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, Bool exact);			// 0x003584E9
	void setSequentialTimer(Team *team, int frames);			// 0x00204002
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamIdleForFramecount(const AsciiString &teamName, int framecount, bool seconds);
};

void ScriptActions::doTeamIdleForFramecount(const AsciiString &teamName, int framecount, bool seconds)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team)
	{
		AIGroup *group = TheAI->createGroup();
		if (group)
		{
			team->getTeamAsAIGroup(group);
			Coord3D center;
			group->getCenter(&center);
			group->groupIdle(CMD_FROM_SCRIPT);
			if (seconds)
				TheScriptEngine->setSequentialTimer(team, framecount * g_Va00DBA4E4);
			else
				TheScriptEngine->setSequentialTimer(team, framecount);
		}
	}
}
