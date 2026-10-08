// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ScriptActions member at retail 0x003CA322 (179B), WorldBuilder 0x01014EE0
// (unnamed there; it sits beside doCreateUnitRevivalEntryFromDelayedCarryoverHero
// in WB's ScriptActions.cpp). Flags and the ObjectTypes view follow the solo
// fork's ScriptActions_delayedCarryover.cpp, where it was matched with its
// two siblings.

#include "ascii_string.h"
#include <vector>

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	int getListSize() const { return m_objectTypes.size(); }
	void addObjectType(const AsciiString &objectType);

private:
	AsciiString m_listName;
	_STL::vector<AsciiString> m_objectTypes;
};

class Team
{
public:
	void rva003A178D(ObjectTypes *types, int count, Team *otherTeam);
};

class ScriptEngine
{
public:
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	Team *getTeamNamed(AsciiString name, bool);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003CA322(const AsciiString &teamName, int count,
		const AsciiString &objectTypeName, const AsciiString &otherTeamName);
};

// WB 0x01014EE0 unnamed ScriptActions member @0x003CA322 (179B): hand the
// team's 0x003A178D an object-type list (the named list, or a temporary one
// holding just the name), a count and a second team.
void ScriptActions::rva003CA322(const AsciiString &teamName, int count,
	const AsciiString &objectTypeName, const AsciiString &otherTeamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, true);
	if (!team)
		return;
	Team *otherTeam = TheScriptEngine->getTeamNamed(otherTeamName, false);
	if (!otherTeam)
		return;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectTypeName);
	if (types) {
		team->rva003A178D(types, count, otherTeam);
	} else {
		ObjectTypes tempTypes;
		tempTypes.addObjectType(objectTypeName);
		team->rva003A178D(&tempTypes, count, otherTeam);
	}
}
