// cl: /O1 /DNDEBUG /MD /EHsc
// ?winSetLoneWindow@GameWindowManager@@UAEXPAVGameWindow@@@Z @0x002C12DC 51B
// GameWindowManager::winSetLoneWindow; BFME1 donor GameWindowManager.cpp winSetLoneWindow verbatim shape; m_loneWindow at +0x2C; GGM_CLOSE 0x4005 via TheWindowManager slot 58 0xE8; vtable 0x7C7C90 slot 52.

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
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51)
#undef V
	virtual void winSetLoneWindow(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(53) W(54) W(55) W(56) W(57)
#undef W
	virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, int mData1, int mData2) = 0;

private:
	unsigned char m_pad04[0x28];
	GameWindow *m_loneWindow;
};

extern GameWindowManager *TheWindowManager;

enum
{
	GGM_CLOSE = 0x4005
};

void GameWindowManager::winSetLoneWindow(GameWindow *window)
{
	if (m_loneWindow == window)
		return;
	if (m_loneWindow)
		TheWindowManager->winSendSystemMsg(m_loneWindow, GGM_CLOSE, 0, 0);
	m_loneWindow = window;
}
