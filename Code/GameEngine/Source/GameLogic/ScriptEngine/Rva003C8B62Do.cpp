// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?Rva003C8B62Do@@YGXABVAsciiString@@@Z @0x003C8B62 (105B).
// Team wander-in-place via getTeamNamed plus iterate plus chooseLocomotorSet
// slot 0x238 plus aiWanderInPlace. Evidence: callees rowed getTeamNamed
// 0x003584E9 iterate 0x00263864 advance 0x00263526 aiWander 0x003C7853,
// caller 0x003CB94B. Precedent doTeamGuard.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef int LocomotorSetType;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class Object;
class Locomotor;
class Waypoint;
typedef float Real;

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

class AICommandInterface
{
public:
	void aiWanderInPlace(CommandSourceType src);
};

class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
private:
	char m_pad[0x20 - 0x04];
public:
	AICommandInterface m_command;
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C8B62Do(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAI();
		if (!ai)
			continue;
		ai->chooseLocomotorSet(3);
		ai->m_command.aiWanderInPlace(CMD_FROM_SCRIPT);
	}
}
