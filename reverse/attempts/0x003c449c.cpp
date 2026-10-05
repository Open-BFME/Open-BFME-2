// ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
// partial score=0.75 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z,
// retail 0x003C449C, 212 bytes (called from the action dispatcher 0x003CA4BE
// at 0x003CCDC1 for TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE, index
// 272; the ZH lift lane names this body doTeamUseCommandButtonOnNearestObjectType).
// Zero Hour's doTeamUseCommandButtonOnNearestObjectType as BFME2 builds it,
// without the AIGroup: the team's centroid stands in for the group centre,
// the ObjectTypes/single-template split runs through the script helper
// 0x003C24F0, and every ready member is commanded through the 0x003BE11C
// helper instead of one group command. The named twin 0x003C42B9 (case 429)
// shares both helpers and the same template-off-result load.
//
// Target facts: the case passes getParameter(2/1/0) as strings; the body
// gates on getTeamNamed 0x003584E9, ControlBar::findCommandButton 0x0031BE3C
// and ScriptEngine::getObjectTypes 0x00357651. The types path nests the
// centroid call inside the 0x003C24F0 argument list (the three zero/template
// pushes precede it, the position push follows its EAX), so the centroid is
// declared here with the EAX-returning spelling the existing by-value pin
// already proves; the single-template path takes ThingFactory::findTemplate
// 0x002D06CA. Both paths join on one template: the types path reads it off
// Object+0x04 (the same +0x04 template member TeamGetTeamAsAIGroup.cpp
// models), the single path takes findTemplate's result. The member loop is
// the rowed iterate 0x00263864 plus the rowed
// Rva001705A0DlinkIterator advance 0x00263526 with inlined done/cur, gated by
// CommandButton::isReady 0x0035B069, commanding through the pinned __cdecl
// free-function spelling of 0x003BE11C (caller cleanup; both dispatch call
// sites hold the member in ESI across the call).
#include "ascii_string.h"

typedef int Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Player;
class ObjectTypes;
class ThingTemplate;

class Object
{
public:
	unsigned char m_head[4];
	const ThingTemplate *m_template;	// +0x04
};

class CommandButton
{
public:
	bool isReady(const Object *obj) const;	// 0x0035B069
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
};
extern ControlBar *TheControlBar;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// The rowed 32-byte body at 0x263526 (TU-local call-site ABI view; see
// TeamGetTeamAsAIGroup.cpp).
template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
public:
	void advance();	// 0x00263526
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
	Coord3D *rva0039DA2A(Coord3D *center) const;	// 0x0039DA2A
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
	ObjectTypes *getObjectTypes(const AsciiString &name);	// 0x00357651
};
extern ScriptEngine *TheScriptEngine;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

void rva003BE11C(const ThingTemplate *tmpl, const CommandButton *button);	// 0x003BE11C

class ScriptActions
{
public:
	Object *rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag);	// 0x003C24F0
protected:
	void doTeamUseCommandButtonOnNearestObjectType(const AsciiString &teamName,
		const AsciiString &commandAbility, const AsciiString &objectType);
};

void ScriptActions::doTeamUseCommandButtonOnNearestObjectType(const AsciiString &teamName,
	const AsciiString &commandAbility, const AsciiString &objectType)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;
	const ThingTemplate *tmpl;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		Coord3D pos;
		Object *best = rva003C24F0(team->rva0039DA2A(&pos), types, 0, false);
		if (!best)
			return;
		tmpl = best->m_template;
	} else {
		tmpl = TheThingFactory->findTemplate(objectType);
	}
	if (!tmpl)
		return;
	DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList();
	for (DLINK_ITERATOR<Object> iter = it; iter.cur() != 0;
		reinterpret_cast<Rva001705A0DlinkIterator<Object> *>(&iter)->advance()) {
		if (commandButton->isReady(iter.cur()))
			rva003BE11C(tmpl, commandButton);
	}
}
