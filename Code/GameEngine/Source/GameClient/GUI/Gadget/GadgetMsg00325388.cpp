// cl: /Ob0
//
// ?Rva00325388Send@@YAXPAVGameWindow@@HHH@Z, retail 0x00325388, 54 bytes.
// Free-function WindowManager slot 0xE8 sender: if window null returns,
// else forwards window plus 0x4021 plus locals (arg4 at -8 and arg3 at -4)
// plus arg2 through TheWindowManager at 0x00DFEF1C winSendSystemMsg.
// Callers push 4 args and add esp 0x10. Evidence: rowed Rva00222547Get
// same slot and manager; unblocks 11 frees; prev GadgetListBoxSetColumnWidths
// same dir and flags.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

void Rva00325388Send(GameWindow *window, int a, int b, int c)
{
	struct MsgPair
	{
		int x;
		int y;
	};
	MsgPair p;
	p.x = c;
	p.y = b;
	if (window == 0)
		return;
	TheWindowManager->winSendSystemMsg(window, 0x4021, (WindowMsgData)&p, (WindowMsgData)a);
}

int Rva003253BEGet(GameWindow *window, int a, int b)
{
	struct MsgPair
	{
		int x;
		int y;
	};
	MsgPair p;
	int out = 0;
	p.x = b;
	p.y = a;
	if (window != 0)
		TheWindowManager->winSendSystemMsg(window, 0x4020, (WindowMsgData)&p, (WindowMsgData)&out);
	return out;
}
