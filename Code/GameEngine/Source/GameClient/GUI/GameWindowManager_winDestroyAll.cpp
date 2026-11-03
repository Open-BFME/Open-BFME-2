// cl: /O1 /DNDEBUG /MD
// ?winDestroyAll@GameWindowManager@@UAEHXZ @0x002C124C 46B.
// Walk the window list at +0xC via m_next +0x1F8, destroying each window
// through winDestroy (slot 35, 0x8C), then drain the destroy list and return 0.
// Evidence: vtable slot 36 of 0x007C7C90 (GameWindowManager family), caller
// dtor 0x002C5398 and reset 0x002C0A5C, callee rowed processDestroyList
// 0x002C08EF, prev/next flags. Identity: ZH/BFME1 winDestroyAll.
#include "../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../Include/GameClient/GameWindowManager.h"

int GameWindowManager::winDestroyAll()
{
	GameWindow *win = m_windowList;
	if (win)
	{
		GameWindow *cur = win;
		do
		{
			GameWindow *next = cur->m_next;
			winDestroy(cur);
			cur = next;
		} while (cur);
	}
	processDestroyList();
	return 0;
}
