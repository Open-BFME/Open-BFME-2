// ?doTeamHuntWithCommandButton@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.98 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
//
// ScriptActions::doTeamHuntWithCommandButton, retail 0x003C3C0A (619B; ret 8)
// Target identity: executeAction case TEAM_HUNT_WITH_COMMAND_BUTTON calls it
// on the ScriptActions instance with parameters 0 and 1's strings; BFME 1's
// ScriptActionsTeamHuntWithCommandButton.cpp is the donor for the name and
// flow.
// Target body: the team by name (getTeamNamed 0x003584E9), the button by the
// ability name (findCommandButton 0x0031BE3C), whose command type (+0x14)
// must be 23 or 27, or 24 or 38 with a special power (+0x44) and an option
// (+0x1C) bit 0-2; otherwise the error is appended (AppendDebugMessage
// 0x00205263). Each team member (iterate_TeamMemberList 0x00263864, advance
// 0x00263526) with a +0x258 interface looks its command set up through the
// rowed 0x00290E67 string and 0x0031D5F8 lookup on TheControlBar, scans its 32
// buttons (getCommandButton 0x00409EE8) for the button, and for those four
// types hands the ability to the module found by the static
// "CommandButtonHuntUpdate" key (nameToKey 0x00148E1A, findModule 0x0028B6D6,
// rowed 0x0049575A); a member without the button or the module gets an error
// naming its template (+0x04, name at +0x64).
// Target differences from the donor: command types 23/24/27/38 for the
// donor's 22/23/26/36, 32 command-set slots, the template read without the
// override chain, and the address-named set lookup. Donor-carried: the
// special-power / option / AI-update meaning of +0x44, +0x1C and +0x258, and
// the hunt-update meaning of the 0x0049575A call.
#include "ascii_string.h"

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

class CommandButton
{
public:
	Int getCommandType() const { return m_command; }
	const void *getSpecialPowerTemplate() const { return m_specialPower; }
	unsigned int getOptions() const { return m_options; }
private:
	unsigned char m_pad00[0x14];
	Int m_command;			// +0x14
	unsigned char m_pad18[4];
	unsigned int m_options;		// +0x1C
	unsigned char m_pad20[0x24];
	const void *m_specialPower;	// +0x44
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;	// 0x00409EE8
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
};
extern ControlBar *TheControlBar;

// The rowed 0x0031D5F8 lookup on TheControlBar (BFME 1: findCommandSet).
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};

// The rowed 0x0049575A hunt-update call (BFME 1: setCommandButton).
class Rva0049575A
{
public:
	void rva0049575A(const AsciiString *ability);
};

class Module;

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	unsigned char m_pad00[0x64];
	AsciiString m_name;	// +0x64
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	void *getAIUpdateInterface() const { return m_ai; }
	const AsciiString *rva00290E67() const;
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
private:
	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x250];
	void *m_ai;				// +0x258
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();		// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	unsigned char m_rest[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
	void AppendDebugMessage(const AsciiString &msg, bool pause);	// 0x00205263
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamHuntWithCommandButton(const AsciiString &teamName, const AsciiString &ability);
};

void ScriptActions::doTeamHuntWithCommandButton(const AsciiString &teamName, const AsciiString &ability)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;
	const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
	if (!commandButton)
		return;

	switch (commandButton->getCommandType())
	{
	case 24:
	case 38:
		if (commandButton->getSpecialPowerTemplate()) {
			if (commandButton->getOptions() & 7)
				break;
			AsciiString msg = "ERROR-Team hunt with command button - cannot hunt with ability ";
			msg += ability;
			TheScriptEngine->AppendDebugMessage(msg, false);
			return;
		}
		return;
	case 23:
	case 27:
		break;
	default:
	{
		AsciiString msg = "ERROR-Team hunt with command button - cannot hunt with ability ";
		msg += ability;
		TheScriptEngine->AppendDebugMessage(msg, false);
		return;
	}
	}

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj->getAIUpdateInterface())
			continue;

		bool foundCommand = false;
		const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
		if (commandSet) {
			for (Int i = 0; i < 32; ++i) {
				const CommandButton *aCommandButton = commandSet->getCommandButton(i);
				if (commandButton == aCommandButton) {
					foundCommand = true;
					break;
				}
			}
		}
		if (!foundCommand) {
			AsciiString msg = "Error - Team hunt with command button - unit type '";
			msg += obj->getTemplate()->getName().str();
			msg += "' is not valid for ability ";
			msg += ability;
			TheScriptEngine->AppendDebugMessage(msg, false);
			continue;
		}

		switch (commandButton->getCommandType())
		{
		case 23:
		case 24:
		case 27:
		case 38:
		{
			static NameKeyType key_CommandButtonHuntUpdate = TheNameKeyGenerator->nameToKey("CommandButtonHuntUpdate");
			Rva0049575A *huntUpdate = (Rva0049575A *)obj->findModule(key_CommandButtonHuntUpdate);
			if (huntUpdate) {
				huntUpdate->rva0049575A(&ability);
			} else {
				AsciiString msg = "Error - Team hunt with command button - unit type '";
				msg += obj->getTemplate()->getName().str();
				msg += "' requires CommandButtonHuntUpdate in .ini definition to hunt with ";
				msg += ability;
				TheScriptEngine->AppendDebugMessage(msg, false);
			}
			break;
		}
		}
	}
}
