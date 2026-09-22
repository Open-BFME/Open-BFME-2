// ?winHide@GameWindow@@QAEH_N@Z
// partial score=0.98 date=2026-09-22
// cl: /O1 /DNDEBUG /MD
// ?winHide@GameWindow@@QAEH_N@Z @0x00313C64
// Shard TU: ControlBarFields.cpp calls this out-of-line via pin; defining it
// there risks IPO-visibility changes to the rowed caller, so it lives here
// (same-class-in-2-TUs precedent).
//
// BFME1 donor is GameWindowFields.cpp winHide (oldStatus + hide-place +
// windowHiding + changed-gate winSendSystemMsg(this, 0x1B, !hide, 0) +
// unconditional 0x10000000 clear + return 0). BFME2 adds a second
// unconditional winSendSystemMsg(this, 0x1C, 0x10, hidden-bit) sync after
// the clear; retail proves the slot (+0xE8), the args and the order.

class GameWindow;

class WindowManager
{
public:
	virtual void _s00();
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual void _s04();
	virtual void _s05();
	virtual void _s06();
	virtual void _s07();
	virtual void _s08();
	virtual void _s09();
	virtual void _s10();
	virtual void _s11();
	virtual void _s12();
	virtual void _s13();
	virtual void _s14();
	virtual void _s15();
	virtual void _s16();
	virtual void _s17();
	virtual void _s18();
	virtual void _s19();
	virtual void _s20();
	virtual void _s21();
	virtual void _s22();
	virtual void _s23();
	virtual void _s24();
	virtual void _s25();
	virtual void _s26();
	virtual void _s27();
	virtual void _s28();
	virtual void _s29();
	virtual void _s30();
	virtual void _s31();
	virtual void _s32();
	virtual void _s33();
	virtual void _s34();
	virtual void _s35();
	virtual void _s36();
	virtual void _s37();
	virtual void _s38();
	virtual void _s39();
	virtual void windowHiding(GameWindow *window);
	virtual void _s41();
	virtual void _s42();
	virtual void _s43();
	virtual void _s44();
	virtual void _s45();
	virtual void _s46();
	virtual void _s47();
	virtual void _s48();
	virtual void _s49();
	virtual void _s50();
	virtual void _s51();
	virtual void _s52();
	virtual void _s53();
	virtual void _s54();
	virtual void _s55();
	virtual void _s56();
	virtual void _s57();
	virtual void winSendSystemMsg(GameWindow *window, unsigned int msg, int data1, int data2);
};

extern WindowManager *TheWindowManager;

class GameWindow
{
public:
	int winHide(bool hide);

private:
	char m_pad[8];
	unsigned int m_status;
};

int GameWindow::winHide(bool hide)
{
	unsigned int oldStatus = m_status;

	if (hide)
	{
		m_status |= 0x10;
		TheWindowManager->windowHiding(this);
	}
	else
	{
		m_status &= ~0x10;
	}

	if (m_status != oldStatus)
		TheWindowManager->winSendSystemMsg(this, 0x1B, !hide, 0);

	((unsigned char *)this)[0xB] &= 0xEF;

	TheWindowManager->winSendSystemMsg(this, 0x1C, 0x10, (m_status >> 4) & 1);

	return 0;
}
