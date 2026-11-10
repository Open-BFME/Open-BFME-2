// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
//
// ScriptActions::doRemoveCommandBarButton, retail 0x003C5CF9 (279B; ret 8).
// Target identity: executeAction case 311 (COMMANDBAR_REMOVE_BUTTON_OBJECTTYPE)
// calls it with parameter 0's and parameter 1's strings, as Zero Hour's
// ScriptActions.cpp does. The target body looks the template up through the
// pinned ThingFactory::findTemplate (0x002D06CA), finds the command set named
// by template+0x70 with ControlBar::findCommandSet (0x0031D5F8) and, unlike
// the donor, overrides every one of the 32 slots whose button name equals the
// argument (no break) through 0x0024792F with TheGameLogic and a NULL button
// (the donor's setControlBarOverride). It then repeats that for the command
// set (+0x118, CommandSetUpgradeModuleData's CommandSet) of every module data
// in the template's module info at +0x2E4 whose slot-23 virtual returns one;
// the null test of the set inside both slot loops is target evidence for the
// shared per-set loop. Structural inference: the slot-23 name and the module
// info's role are not established by the target.
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef int Int;

enum { MAX_COMMANDS_PER_SET = 32 };

#include "../../../Include/GameClient/CommandButton.h"

#include "../../../Include/GameClient/CommandSet.h"

class CommandSetUpgradeModuleData
{
public:
	const AsciiString &getCommandSet() const { return m_commandSet; }
private:
	unsigned char m_pad[0x118];
	AsciiString m_commandSet;	// +0x118
};

class ModuleData
{
public:
	virtual void v00() const; virtual void v01() const; virtual void v02() const; virtual void v03() const;
	virtual void v04() const; virtual void v05() const; virtual void v06() const; virtual void v07() const;
	virtual void v08() const; virtual void v09() const; virtual void v10() const; virtual void v11() const;
	virtual void v12() const; virtual void v13() const; virtual void v14() const; virtual void v15() const;
	virtual void v16() const; virtual void v17() const; virtual void v18() const; virtual void v19() const;
	virtual void v20() const; virtual void v21() const; virtual void v22() const;
	virtual const CommandSetUpgradeModuleData *getAsCommandSetUpgradeModuleData() const;	// slot 23 (+0x5C)
};

#include "../../../Include/Common/ModuleInfoClass.h"

class ThingTemplate
{
public:
	const AsciiString &friend_getCommandSetString() const { return m_commandSetString; }
	const ModuleInfo &getBehaviorModuleInfo() const { return m_behaviorModuleInfo; }
private:
	unsigned char m_pad00[0x70];
	AsciiString m_commandSetString;	// +0x70
	unsigned char m_pad74[0x2E4 - 0x74];
	ModuleInfo m_behaviorModuleInfo;	// +0x2E4
};

#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../Include/Common/Rva0031D5F8.h"
#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

extern GameLogic *TheGameLogic;

class ScriptActions
{
protected:
	void doRemoveCommandBarButton(const AsciiString &buttonName, const AsciiString &objectType);
};

static __forceinline void removeCommandSetButton(const AsciiString &commandSetName, const AsciiString &buttonName)
{
	const CommandSet *cs = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&commandSetName);
	for (Int i = 0; i < MAX_COMMANDS_PER_SET; ++i)
	{
		if (cs && cs->getCommandButton(i) && cs->getCommandButton(i)->getName() == buttonName)
		{
			TheGameLogic->setControlBarOverride(commandSetName, i, NULL);
		}
	}
}

void ScriptActions::doRemoveCommandBarButton(const AsciiString &buttonName, const AsciiString &objectType)
{
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(objectType);
	if (!thingTemplate) {
		return;
	}

	removeCommandSetButton(thingTemplate->friend_getCommandSetString(), buttonName);

	const ModuleInfo &mi = thingTemplate->getBehaviorModuleInfo();
	for (Int j = 0; j < mi.getCount(); ++j)
	{
		const ModuleData *md = mi.getNthData(j);
		if (!md)
			continue;
		const CommandSetUpgradeModuleData *upgradeData = md->getAsCommandSetUpgradeModuleData();
		if (!upgradeData)
			continue;
		removeCommandSetButton(upgradeData->getCommandSet(), buttonName);
	}
}
