// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// GameWindow system callback body. The input callback at A0CFF is owned
// once, by W3DGadgetWindowDrawSlots.cpp; both gadget consumers bind it.

// Native GameWindow table C0BBCC slot 2 selects this complete35B body.
// The placeholder method name is retained; this recovers its class/ABI,
// not an original method name. Only the prefix through callback+1E4 is used.
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
#include "../../Include/GameClient/Bfme2GameWindow.h"

WindowMsgHandledType GameWindow::bfmeGoEHCb(
    unsigned int msg, unsigned int mData1, unsigned int mData2)
{
    GameWindowNativeSystemFunc fn = m_system;
    if (fn)
        return fn(this, msg, mData1, mData2);
    return MSG_IGNORED;
}
