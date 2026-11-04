// cl: /DNDEBUG /MD
// platformsdk
// ?winSetFocus@GameWindowManager@@UAEHPAVGameWindow@@@Z @0x002C0ED5 147B
// GameWindowManager::winSetFocus; vtable 0x7C7C90 slot 49 offset 0xC4; BFME1 donor GameWindowManager.cpp winSetFocus verbatim shape; m_keyboardFocus at +0x20; GWM_INPUT_FOCUS 23 via slot 58 0xE8; NO_FOCUS 0x400 via winGetStatus pin 0x30F45F; parent chain via winGetParent pin 0x3140A4.
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum { WIN_ERR_OK = 0, WIN_STATUS_NO_FOCUS = 0x400, GWM_INPUT_FOCUS = 23 };
#include <windows.h>
#include "../../../Include/GameClient/Bfme2GameWindow.h"
#include "../../../Include/GameClient/GameWindowManager.h"
Int GameWindowManager::winSetFocus(GameWindow *window)
{
    Bool wantsFocus = FALSE;
    if (window) {
        if (window->winGetStatus() & WIN_STATUS_NO_FOCUS)
            return 0;
    }
    if ((m_keyboardFocus) && (m_keyboardFocus != window)) {
        Bool wf;
        winSendSystemMsg(m_keyboardFocus, GWM_INPUT_FOCUS, FALSE, (WindowMsgData)&wf);
    }
    m_keyboardFocus = window;
    if (m_keyboardFocus) {
        for (;;) {
            winSendSystemMsg(window, GWM_INPUT_FOCUS, TRUE, (WindowMsgData)&wantsFocus);
            if (wantsFocus)
                break;
            window = window->winGetParent();
            if (window == NULL)
                break;
        }
    }
    if (wantsFocus == FALSE)
        m_keyboardFocus = NULL;
    return WIN_ERR_OK;
}
