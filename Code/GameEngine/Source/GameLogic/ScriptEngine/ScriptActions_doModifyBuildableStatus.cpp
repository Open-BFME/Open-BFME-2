// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?doModifyBuildableStatus@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BC4AB 38B: script set buildable override via template lookup.
// Evidence: push [esp+4] mov ecx,[0xDFF000]=g_009FF000 call rowed rva002D06CA 0x002D06CA test eax je ret 8; push [esp+8] mov ecx,[0xFE78C]=TheGameLogic push eax call rowed setBuildableStatusOverride 0x00246F71; caller 0x003CD142; sibling Rva003BC5CESet same (AsciiString,int) stdcall shape.
#include "ascii_string.h"

class ThingTemplate;
#include "../../../Include/Common/ThingFactory.h"
extern class ThingFactory *TheThingFactory;

class ThingTemplate;
enum BuildableStatus
{
	BUILDABLE_STATUS_UNKNOWN = 0
};
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

void ScriptActions::doModifyBuildableStatus(const AsciiString &name, int status)
{
	void *tt = (void *)TheThingFactory->findTemplate(name);
	if (tt == 0)
		return;
	TheGameLogic->setBuildableStatusOverride((const ThingTemplate *)tt, (BuildableStatus)status);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
