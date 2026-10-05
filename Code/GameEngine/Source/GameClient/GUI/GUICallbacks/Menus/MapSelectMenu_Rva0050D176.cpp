// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2gwm /Ireference/shims/bfme_namekey /O1 /G7 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
// ?Rva0050D176Set@@YAXXZ @ 0x0050D176 377B: MapSelect AI-difficulty radio refresh via parent window and ScriptEngine difficulty field; evidence: string literals MapSelectMenuParent/Easy/Medium/HardAI plus rowed nameToKey/winGet/GadgetRadioSetSelection plus caller 0x0050D541 plus neighbours MapSelectMenu_Rva0050CEAB/MapSelectMenuInput.
#include "PreRTS.h"
#include "Common/GameEngine.h"
#include "GameLogic/ScriptEngine.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetRadioButton.h"

class BfmeScriptDiffView
{
public:
	char m_pad[0x1A4C4];
	int m_diff;
};

extern ScriptEngine *g_Va009FE16C;
extern int g_00DD12D8;
// g_00DD12D8: matched references place it at VA 0xdd12d8 (zero-filled .bss).
int g_00DD12D8;

void Rva0050D176Set()
{
	AsciiString parentName("MapSelectMenu.wnd:MapSelectMenuParent");
	NameKeyType parentID = TheNameKeyGenerator->nameToKey(parentName);
	GameWindow *parent = TheWindowManager->winGetWindowFromId(0, parentID);
	ScriptEngine *se = g_Va009FE16C;
	if (se == 0) {
		g_00DD12D8 = 0;
	} else {
		int diff = ((BfmeScriptDiffView *)se)->m_diff;
		switch (diff) {
			case 0: {
				NameKeyType id = TheNameKeyGenerator->nameToKey(AsciiString("MapSelectMenu.wnd:RadioButtonEasyAI"));
				GameWindow *win = TheWindowManager->winGetWindowFromId(parent, id);
				GadgetRadioSetSelection(win, false);
				g_00DD12D8 = 0;
				break;
			}
			case 1: {
				NameKeyType id = TheNameKeyGenerator->nameToKey(AsciiString("MapSelectMenu.wnd:RadioButtonMediumAI"));
				GameWindow *win = TheWindowManager->winGetWindowFromId(parent, id);
				GadgetRadioSetSelection(win, false);
				g_00DD12D8 = 1;
				break;
			}
			case 2: {
				NameKeyType id = TheNameKeyGenerator->nameToKey(AsciiString("MapSelectMenu.wnd:RadioButtonHardAI"));
				GameWindow *win = TheWindowManager->winGetWindowFromId(parent, id);
				GadgetRadioSetSelection(win, false);
				g_00DD12D8 = 2;
				break;
			}
		}
	}
}
