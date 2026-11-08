// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BBE91Set@ScriptActions@@QAEX_NH@Z @0x003BBE91 66B leaf caller 0x003CC271 globals 0xDFEA3C slots 0xB4 0xBC 0xC0
// Evidence: TheTacticalView triple virtual call with 1 6 and (arg2, arg1?1:-1).
#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;
void ScriptActions::Rva003BBE91Set(bool flag, int v)
{
	TheTacticalView->setViewFilterMode((FilterModes)1);
	TheTacticalView->setViewFilter((FilterTypes)6);
	if (flag)
		TheTacticalView->setFadeParameters(v, 1);
	else
		TheTacticalView->setFadeParameters(v, -1);
}

// ?Rva003BB898@@YGX_N_N@Z @0x003BB898, 85 bytes. The two arguments are
// booleans by their byte loads; adjacent script actions and the table entries
// establish TheTacticalView calls at slots 47 and 45. Exact action name is
// unknown, so retain the address name.
void ScriptActions::Rva003BB898(bool first, bool second)
{
	if (TheTacticalView->setViewFilter((FilterTypes)2))
	{
		int value;
		if (second)
			value = (first ? -1 : 0) + 12;
		else
			value = (first ? -1 : 0) + 10;
		if (!TheTacticalView->setViewFilterMode((FilterModes)value))
			TheTacticalView->setViewFilter((FilterTypes)0);
	}
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
