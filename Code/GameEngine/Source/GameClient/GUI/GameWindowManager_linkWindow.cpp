// cl: /DNDEBUG /MD
// GameWindowManager::linkWindow @0x002C0A89 136B, unlinkWindow @0x002C0B92 69B,
// unlinkChildWindow @0x002C0BD7 110B: the master window list and child links.
// Evidence: neighbours GadgetButtonImageHelpers 0x002C0505 and GameWindowManager_enableWindowsInRange 0x002C0CED same flags; GameWindow next +0x1F8 prev +0x1FC from GameWindowManager_enableWindowsInRange; window list head +0xC tail +0x10, modal head +0x24; callers 0x002C25A6 0x00314083 0x003147B1 and winDestroy 0x002C1173; no callees.
// Identity: ZH/BFME1 GameWindowManager.cpp linkWindow (insert behind the last
// modal window, else push front), unlinkWindow and unlinkChildWindow bodies;
// the modal entry is ZH's ModalWindow {vtable, window, next}.
class GameWindow
{
public:
	unsigned char m_pad[0x1F8];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
};
struct ModalWindow
{
	void *m_vtable;
	GameWindow *window;
	ModalWindow *next;
};
class GameWindowManager
{
public:
	void linkWindow(GameWindow *win);
	void unlinkWindow(GameWindow *win);
	void unlinkChildWindow(GameWindow *win);
private:
	unsigned char m_pad0[0xC];
	GameWindow *m_windowList;
	GameWindow *m_windowTail;
	unsigned char m_pad14[0x24 - 0x14];
	ModalWindow *m_modalHead;
};
void GameWindowManager::linkWindow(GameWindow *win)
{
	GameWindow *found = 0;
	GameWindow *cur = m_windowList;
	if (cur) {
		do {
			ModalWindow *node = m_modalHead;
			while (node) {
				GameWindow *v = node->window;
				if (v == cur && v != win)
					found = cur;
				node = node->next;
			}
			cur = cur->m_next;
		} while (cur);
	}
	if (!found) {
		win->m_prev = 0;
		win->m_next = m_windowList;
		if (m_windowList)
			m_windowList->m_prev = win;
		else
			m_windowTail = win;
		m_windowList = win;
		return;
	}
	win->m_prev = found;
	win->m_next = found->m_next;
	found->m_next = win;
	if (win->m_next)
		win->m_next->m_prev = win;
}
void GameWindowManager::unlinkWindow(GameWindow *win)
{
	if (win->m_next)
		win->m_next->m_prev = win->m_prev;
	else
		m_windowTail = win->m_prev;
	if (win->m_prev)
		win->m_prev->m_next = win->m_next;
	else
		m_windowList = win->m_next;
}
void GameWindowManager::unlinkChildWindow(GameWindow *win)
{
	if (win->m_prev) {
		win->m_prev->m_next = win->m_next;
		if (win->m_next)
			win->m_next->m_prev = win->m_prev;
	} else {
		if (win->m_next) {
			win->m_parent->m_child = win->m_next;
			win->m_next->m_prev = win->m_prev;
			win->m_next = 0;
		} else {
			win->m_parent->m_child = 0;
		}
	}
	win->m_parent = 0;
}
