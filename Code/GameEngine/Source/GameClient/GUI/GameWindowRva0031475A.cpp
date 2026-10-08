// cl: /DNDEBUG /MD /EHsc
// ?winBringToTop@GameWindow@@QAEHXZ, retail 0x0031475A, 128 bytes.
// Honest GameWindow method returning 0 or -3: detach path via Remove plus
// manager slot 0xE0, else search manager list via slot 0x94 walking +0x1F8
// for this then B92/A89, then notify +0x210 object via slots 0x1C/0x18.
// Evidence: this+0x200 parent and +0x1F8 next match GameWindow layout in
// GameWindowManager_linkWindow.cpp; rowed unlinkWindow/linkWindow/unlinkChildWindow; TheWindowManager
// ?TheWindowManager@@3PAVGameWindowManager@@A; WIN_ERR codes 0/-3.

class GameWindow;

class GameWindowManager
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual void d36();
	virtual GameWindow *Virtual94();
	virtual void d38(); virtual void d39();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
	virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
	virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
	virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
	virtual void VirtualE0(GameWindow *win, GameWindow *parent);
	void linkWindow(GameWindow *win);
	void unlinkWindow(GameWindow *win);
	void unlinkChildWindow(GameWindow *win);
};

extern GameWindowManager *TheWindowManager;

class Gadget210
{
public:
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
	virtual void g04(); virtual void g05();
	virtual void Virtual18(GameWindow *win);
	virtual void Virtual1C(GameWindow *win);
};

class GameWindow
{
public:
	int winBringToTop();
	int winGetCursorPosition(int *x, int *y);
	int rva003147DA();
	int winHide(bool hide);
private:
	char m_pad00[0x08];
	int m_status;
	char m_pad0C[0x24 - 0x0C];
	int m_cursorX;
	int m_cursorY;
	char m_pad2C[0x1F8 - 0x2C];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
	char m_pad20C[0x210 - 0x208];
	Gadget210 *m_210;
};

int GameWindow::winBringToTop()
{
	GameWindowManager *mgr = TheWindowManager;
	GameWindow *parent = m_parent;
	if (parent != 0) {
		mgr->unlinkChildWindow(this);
		TheWindowManager->VirtualE0(this, parent);
	} else {
		GameWindow *cur = mgr->Virtual94();
		while (cur != this) {
			if (cur == 0)
				return -3;
			cur = cur->m_next;
		}
		TheWindowManager->unlinkWindow(this);
		TheWindowManager->linkWindow(this);
	}
	Gadget210 *g = m_210;
	if (g != 0) {
		g->Virtual1C(this);
		g->Virtual18(this);
	}
	return 0;
}

// ?rva003147DA@GameWindow@@QAEHXZ, retail 0x003147DA, 28 bytes.
// Calls winBringToTop then winHide(false) on success; sets status bit0.
// Evidence: chain caller of 0x0031475A; or [esi+8],1 matches m_status;
// rowed ?winHide@GameWindow@@QAEH_N@Z.

int GameWindow::rva003147DA()
{
	int r = winBringToTop();
	if (r != 0)
		return r;
	m_status |= 1;
	winHide(false);
	return 0;
}

// ZH names plus native IME call at 0x233947 and loads at +0x24/+0x28.
int GameWindow::winGetCursorPosition(int *x, int *y)
{
	if (x) *x = m_cursorX;
	if (y) *y = m_cursorY;
	return 0;
}
