// cl: /O1 /DNDEBUG /MD
// ?enableWindowsInRange@GameWindowManager@@UAEXPAVGameWindow@@HH_N@Z @0x002C0DD0 52B
// GameWindowManager::enableWindowsInRange; BFME1 donor GameWindowManager.cpp enableWindowsInRange verbatim shape; vtable 0x7C7C90 slot 39; calls winGetWindowFromId slot 60 0xF0 and rowed winEnable 0x313BEC.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class GameWindow
{
public:
	Int winHide(Bool hide);
	Int winEnable(Bool enable);

private:
	unsigned char m_pad00[0x1F8];

public:
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37)
#undef V
	virtual void hideWindowsInRange(GameWindow *baseWindow, Int first, Int last, Bool hideFlag);
	virtual void enableWindowsInRange(GameWindow *baseWindow, Int first, Int last, Bool enableFlag);
#define W(n) virtual void pad##n() = 0;
	W(40) W(41) W(42) W(43) W(44) W(45) W(46) W(47)
	W(48) W(49) W(50) W(51) W(52) W(53) W(54) W(55)
	W(56)
#undef W
	virtual void addWindowToParentAtEnd(GameWindow *window, GameWindow *parent);
#define X(n) virtual void pad##n() = 0;
	X(58) X(59)
#undef X
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id) = 0;
};

void GameWindowManager::addWindowToParentAtEnd(GameWindow *window, GameWindow *parent)
{
	if (parent)
	{
		window->m_prev = NULL;
		window->m_next = NULL;
		if (parent->m_child)
		{
			GameWindow *last;

			last = parent->m_child;
			while (last->m_next != NULL)
				last = last->m_next;

			last->m_next = window;
			window->m_prev = last;
		}
		else
			parent->m_child = window;

		window->m_parent = parent;
	}
}

void GameWindowManager::hideWindowsInRange(GameWindow *baseWindow, Int first, Int last, Bool hideFlag)
{
	Int i;
	GameWindow *window;

	for (i = first; i <= last; i++)
	{
		window = winGetWindowFromId(baseWindow, i);
		if (window)
			window->winHide(hideFlag);
	}
}

void GameWindowManager::enableWindowsInRange(GameWindow *baseWindow, Int first, Int last, Bool enableFlag)
{
	Int i;
	GameWindow *window;

	for (i = first; i <= last; i++)
	{
		window = winGetWindowFromId(baseWindow, i);
		if (window)
			window->winEnable(enableFlag);
	}
}
