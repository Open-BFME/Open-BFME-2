// cl: /DNDEBUG /MD
// ?Rva0050E776Send@@YAHPAVGameWindow@@H@Z @0x0050E776
// (30B): sends 0x400D via TheWindowManager slot 58 winSendSystemMsg.
// Identity via TheWindowManager plus 0x400D plus slot 0xE8 (precedent
// GameWindowManager_winSetFocus) plus caller 0x0050F2A6; cdecl 2 args.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

class GameWindow {
public:
	unsigned char m_pad[8];
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
	virtual void *winGetFocus();
#undef V
	virtual Int winSetFocus(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(50) W(51) W(52) W(53) W(54) W(55) W(56) W(57)
#undef W
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
};

extern GameWindowManager *TheWindowManager;

int __cdecl Rva0050E776Send(GameWindow *window, int data)
{
	return TheWindowManager->winSendSystemMsg(window, 0x400D, (WindowMsgData)data, 0);
}
