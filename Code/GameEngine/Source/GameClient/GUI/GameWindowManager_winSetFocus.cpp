// cl: /DNDEBUG /MD
// ?winSetFocus@GameWindowManager@@UAEHPAVGameWindow@@@Z @0x002C0ED5 147B
// GameWindowManager::winSetFocus; vtable 0x7C7C90 slot 49 offset 0xC4; BFME1 donor GameWindowManager.cpp winSetFocus verbatim shape; m_keyboardFocus at +0x20; GWM_INPUT_FOCUS 23 via slot 58 0xE8; NO_FOCUS 0x400 via winGetStatus pin 0x30F45F; parent chain via winGetParent pin 0x3140A4.
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum { WIN_ERR_OK = 0, WIN_STATUS_NO_FOCUS = 0x400, GWM_INPUT_FOCUS = 23 };
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif
#ifndef NULL
#define NULL 0
#endif
class GameWindow {
public:
    UnsignedInt winGetStatus();
    GameWindow *winGetParent();
};
class GameWindowManager {
public:
#define V(n) virtual void pad##n() = 0;
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
    V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
    V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
    V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
    V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
    virtual GameWindow *winGetFocus();
#undef V
    virtual Int winSetFocus(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
    W(50) W(51) W(52) W(53) W(54) W(55) W(56) W(57)
#undef W
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
private:
    unsigned char m_pad04[8];
    GameWindow *m_windowList;
    unsigned char m_pad10[0x20 - 0x10];
    GameWindow *m_keyboardFocus;
};
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
