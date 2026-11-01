// Native GameWindow table C0BBCC slots6/8 compare input callback+1E0.
// Class ownership follows the constructor/table and callback offsets; the
// existing slot placeholders deliberately make no original method-name claim.
// flags: region default (reverse/retail_inventory/flag_regions.csv)
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
class GameWindow;
WindowMsgHandledType LeftHUDInput(GameWindow *, unsigned int, unsigned int, unsigned int);
WindowMsgHandledType GadgetPushButtonInput(GameWindow *, unsigned int, unsigned int, unsigned int);
typedef WindowMsgHandledType (__cdecl *GameWinInputFunc)(GameWindow *, unsigned int, unsigned int, unsigned int);

class WinInstanceData;
#include "../../Include/GameClient/Bfme2WinInstanceData.h"
#include "../../Include/GameClient/Bfme2GameWindow.h"
bool GameWindow::vslot6() const
{
    return m_inputFunc == LeftHUDInput;
}

bool GameWindow::vslot8() const
{
    return m_inputFunc == GadgetPushButtonInput;
}
