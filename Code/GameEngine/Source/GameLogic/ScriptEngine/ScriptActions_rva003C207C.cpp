// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::rva003C207C, retail 0x003C207C (78B): looks the team up by
// its parameter's name (rowed getTeamNamed) and the unit by its parameter
// (rowed getUnitNamed), then hands the unit's ObjectID (+0x74) and the bool
// argument (the WorldBuilder twin 0x010144E0 reads it as a byte) to the
// rowed Team::rva003A23A5.
#include "ascii_string.h"

class Object
{
public:
	int getID() const { return m_id; }
private:
	unsigned char m_pad[0x74];
	int m_id; // +0x74
};

class Team
{
public:
	void rva003A23A5(int objectID, bool value);
};

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_pad[0x10];
	AsciiString m_string; // +0x10
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
	Object *getUnitNamed(Parameter *unitParam);
};
extern class ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C207C(Parameter *pTeam, Parameter *pUnit, bool value);
};

void ScriptActions::rva003C207C(Parameter *pTeam, Parameter *pUnit, bool value)
{
	Team *team = TheScriptEngine->getTeamNamed(pTeam->getString(), false);
	if (!team)
		return;
	Object *obj = TheScriptEngine->getUnitNamed(pUnit);
	if (!obj)
		return;
	team->rva003A23A5(obj->getID(), value);
}
