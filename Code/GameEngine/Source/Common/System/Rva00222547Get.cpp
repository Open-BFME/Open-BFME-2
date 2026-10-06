// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00222547Get@@YAPAVGameWindow@@PAV1@@Z, retail 0x00222547, 80 bytes.
// Resolves GameWindow callback owner via TheWindowManager slot 58 0xE8
// (winSendSystemMsg msg 29 data 2000) walking parents via winGetParent
// (ICF twin of Get_Flags at 0x003140A4). Evidence: callers 0x0043C8E4
// 0x0043C7FB push this plus 7 shared invoke args reusing stack (pop ecx
// then push eax for invoke which rets 0x20); returns -1 on null 14 when
// parents exhaust else [out+0x274]; TheWindowManager at 0x00DFEF1C.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class GameWindow
{
public:
	GameWindow *winGetParent();
};

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

struct Rva00222547Out
{
	char m_pad[0x274];
	GameWindow *m_result;
};

GameWindow *Rva00222547Get(GameWindow *w)
{
	if (w == 0)
		return (GameWindow *)-1;
	Rva00222547Out *out = 0;
	for (;;)
	{
		if (w == 0)
			return (GameWindow *)14;
		TheWindowManager->winSendSystemMsg(w, 29, 2000, (WindowMsgData)&out);
		w = w->winGetParent();
		if (out == 0)
			continue;
		return out->m_result;
	}
}
