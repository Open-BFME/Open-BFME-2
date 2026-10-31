// cl: /DNDEBUG /MD
// platformsdk
// ?enableWindowsInRange@GameWindowManager@@UAEXPAVGameWindow@@HH_N@Z @0x002C0DD0 52B
// GameWindowManager::enableWindowsInRange; BFME1 donor GameWindowManager.cpp enableWindowsInRange verbatim shape; vtable 0x7C7C90 slot 39; calls winGetWindowFromId slot 60 0xF0 and rowed winEnable 0x313BEC.

#include <windows.h>

typedef int Int;
typedef bool Bool;

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

#include "../../../Include/GameClient/GameWindowManager.h"

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
	GameWindow *cur = m_keyboardFocus;
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
		if (winSendInputMsg(cur2, 21, ab, bb))
			goto done;
		else
			goto loop;
	}
done:
	return result;
}
