// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ScriptActions::rva003C2166, retail 0x003C2166 (127 bytes, called from the
// action dispatcher 0x003CA4BE): a team recruitment script action. The named team
// (exact lookup), the thing template and the ObjectTypes list for the type name
// resolve, then Team::rva003A1AA3 (0x003A1AA3: recruit from template or types)
// runs with the script's count and a search radius: the AI data's float at +0x5C
// (TheAI +0x18) while the team has any objects, 1000000.0 when it has none.
// Evidence: sibling two-team wiring ScriptGlueRva003C21E5.cpp.
#include "ascii_string.h"
typedef bool Bool;
class ThingTemplate;
class ObjectTypes;

class Team
{
public:
	Bool hasAnyObjects(Bool onlyLiving);						// 0x0039E042
	int rva003A1AA3(const ThingTemplate *tmpl, ObjectTypes *types, int count, float radius);	// 0x003A1AA3
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class AIData
{
public:
	unsigned char m_pad[0x5C];
	float m_recruitRadius;		// +0x5C
};

class AI
{
public:
	unsigned char m_pad[0x18];
	AIData *m_aiData;		// +0x18
};
extern AI *TheAI;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, Bool exact);				// 0x003584E9
	ObjectTypes *getObjectTypes(const AsciiString &name);				// 0x00357651
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C2166(const AsciiString &teamName, int count, const AsciiString &thingName);
};

void ScriptActions::rva003C2166(const AsciiString &teamName, int count, const AsciiString &thingName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (team)
	{
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(thingName);
		ObjectTypes *types = TheScriptEngine->getObjectTypes(thingName);
		if (team->hasAnyObjects(false))
			team->rva003A1AA3(tmpl, types, count, TheAI->m_aiData->m_recruitRadius);
		else
			team->rva003A1AA3(tmpl, types, count, 1000000.0f);
	}
}
