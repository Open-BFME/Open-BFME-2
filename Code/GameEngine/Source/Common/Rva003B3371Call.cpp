// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva003B3371Call@@YAXH@Z @0x003B3371 81B. Free cdecl void(int): if global
// ScriptEngine at 0x009FE16C is set, builds AsciiString temp from table
// 0x009C1050[index] via pinned AsciiString(PBD) at 0x00037BA0, calls rowed
// ScriptEngine::rva00357DD2, destroys temp via releaseBuffer. Evidence:
// rowed StringBase ctor plus rowed rva00357DD2 plus releaseBuffer; 6 callers.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class ScriptEngine
{
public:
	void rva00357DD2(const AsciiString &s);
};
extern ScriptEngine *TheScriptEngine;
// G009C1050: matched DIR32 witness places the pointer table at VA 0x00DC1050
// (.data). Retail contains 35 string pointers through Cine_Insane; the scalar
// sequence begins at VA 0x00DC10DC. Preserve the pointed-to text consumed by
// AsciiString, without asserting retail literal-address identity.
const char *G009C1050[] = {
	"ShellMainMenuCampaignPushed",
	"ShellMainMenuCampaignHighlighted",
	"ShellMainMenuCampaignUnhighlighted",
	"ShellMainMenuSkirmishPushed",
	"ShellMainMenuSkirmishHighlighted",
	"ShellMainMenuSkirmishUnhighlighted",
	"ShellMainMenuOptionsPushed",
	"ShellMainMenuOptionsHighlighted",
	"ShellMainMenuOptionsUnhighlighted",
	"ShellMainMenuOnlinePushed",
	"ShellMainMenuOnlineHighlighted",
	"ShellMainMenuOnlineUnhighlighted",
	"ShellMainMenuNetworkPushed",
	"ShellMainMenuNetworkHighlighted",
	"ShellMainMenuNetworkUnhighlighted",
	"ShellMainMenuExitPushed",
	"ShellMainMenuExitHighlighted",
	"ShellMainMenuExitUnhighlighted",
	"ShellGeneralsOnlineLogin",
	"ShellGeneralsOnlineLogout",
	"ShellGeneralsOnlineEnteredFromGame",
	"ShellOptionsOpened",
	"ShellOptionsClosed",
	"ShellSkirmishOpened",
	"ShellSkirmishClosed",
	"ShellSkirmishEnteredFromGame",
	"ShellLANOpened",
	"ShellLANClosed",
	"ShellLANEnteredFromGame",
	"Subtle",
	"Normal",
	"Strong",
	"Severe",
	"Cine_Extreme",
	"Cine_Insane"
};

void __cdecl Rva003B3371Call(int index)
{
	if (TheScriptEngine == 0)
		return;
	AsciiString tmp(G009C1050[index]);
	TheScriptEngine->rva00357DD2(tmp);
}
