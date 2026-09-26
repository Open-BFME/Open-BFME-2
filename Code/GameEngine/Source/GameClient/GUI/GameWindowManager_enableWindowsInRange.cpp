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
	Int winGetWindowId();
	GameWindow *winGetParent();

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
	W(40) W(41) W(42) W(43) W(44) W(45) W(46)
	virtual Int rva002C0F68(Bool a, Bool b);
	W(48) W(49) W(50) W(51) W(52) W(53) W(54) W(55)
	W(56)
#undef W
	virtual void addWindowToParentAtEnd(GameWindow *window, GameWindow *parent);
#define X(n) virtual void pad##n() = 0;
	X(58)
	virtual Int slot59(GameWindow *win, Int arg, Int a, Int b);
#undef X
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);

private:
	unsigned char m_pad04[8];
	GameWindow *m_windowList;
	unsigned char m_pad10[0x20 - 0x10];
	GameWindow *m_window20;
};

GameWindow *GameWindowManager::winGetWindowFromId(GameWindow *window, Int id)
{
	if (window == NULL)
		window = m_windowList;

	for (; window; window = window->m_next)
	{
		if (window->winGetWindowId() == id)
			return window;
		else if (window->m_child)
		{
			GameWindow *child = winGetWindowFromId(window->m_child, id);

			if (child)
				return child;
		}
	}

	return NULL;
}

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

// ?rva002C0F68@GameWindowManager@@UAEH_N0@Z @0x002C0F68 97B
// GameWindowManager slot 47 (0xBC) of vtable 0x7C7C90; walks parent chain via winGetParent and tries slot59 (0xEC) with 21; member at +0x20.
Int GameWindowManager::rva002C0F68(Bool a, Bool b)
{
	Int result = 0;
	GameWindow *cur2;
	GameWindow *cur = m_window20;
	if (!cur)
		goto done;
	if (!a)
		goto done;
	cur2 = cur;
	{
		Int bb = b;
		Int ab = a;
		result = 1;
		goto tryIt;
	loop:
		cur2 = cur2->winGetParent();
		if (!cur2) {
			result = 0;
			goto done;
		}
	tryIt:
		if (slot59(cur2, 21, ab, bb))
			goto done;
		else
			goto loop;
	}
done:
	return result;
}
