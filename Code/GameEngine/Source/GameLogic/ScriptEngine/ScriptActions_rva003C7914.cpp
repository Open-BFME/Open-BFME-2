// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva003C7914@ScriptActions@@QAEXABVAsciiString@@PAVParameter@@@Z
// ScriptActions::rva003C7914, retail 0x003C7914, 284 bytes (a team attack on a
// named unit, called from the action dispatcher 0x003CA4BE): the team and the
// victim resolve by name, each failure appending the Zero Hour-style warning
// "WARNING - Team (<name>) not found during execution of script." (or Unit) to
// the script debug messages; every member with an AI then gets the attack
// command 0x003C7653 on the victim from a script (source 1).
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

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x258);
	}
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void rva003C7653(Object *target, CommandSourceType cmdSource);	// 0x003C7653
};

class AIUpdateInterface
{
public:
	unsigned char pad[0x20];
	AICommandInterface command;
};

class Team
{
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, Bool exact);			// 0x003584E9
	Object *getUnitNamed(Parameter *unitParm);				// 0x003588E7
	void AppendDebugMessage(const AsciiString &message, Bool mustAdd);	// 0x00205263
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	void rva003C7914(const AsciiString &teamName, Parameter *victimParm);
};

void ScriptActions::rva003C7914(const AsciiString &teamName, Parameter *victimParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team)
	{
		Object *victim = TheScriptEngine->getUnitNamed(victimParm);
		if (victim)
		{
			for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
			{
				AIUpdateInterface *ai = iter.cur()->getAIUpdateInterface();
				if (ai)
					ai->command.rva003C7653(victim, CMD_FROM_SCRIPT);
			}
		}
		else
		{
			AsciiString message("WARNING - Unit (");
			message += victimParm->getString();
			message += ") not found during execution of script.";
			TheScriptEngine->AppendDebugMessage(message, false);
		}
	}
	else
	{
		AsciiString message("WARNING - Team (");
		message += teamName;
		message += ") not found during execution of script.";
		TheScriptEngine->AppendDebugMessage(message, false);
	}
}
