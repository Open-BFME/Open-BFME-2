// cl: /DNDEBUG /MD
// ?rva002C0A89@Rva002C0A89@@QAEXPAVGameWindow@@@Z @0x002C0A89 136B: intrusive GameWindow list push-front or insert-after-found
// Evidence: neighbours GadgetButtonImageHelpers 0x002C0505 and GameWindowManager_enableWindowsInRange 0x002C0CED same flags; GameWindow next +0x1F8 prev +0x1FC from GameWindowManager_enableWindowsInRange; this +0xC head +0x10 tail +0x24 node list; callers 0x002C25A6 0x00314083 0x003147B1; no callees
class GameWindow
{
public:
	unsigned char m_pad[0x1F8];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
};
struct List24Node
{
	int m_unk0;
	GameWindow *m_val;
	List24Node *m_next;
};
class Rva002C0A89
{
public:
	void rva002C0A89(GameWindow *win);
	void rva002C0B92(GameWindow *win);
private:
	unsigned char m_pad0[0xC];
	GameWindow *m_head;
	GameWindow *m_tail;
	unsigned char m_pad14[0x24 - 0x14];
	List24Node *m_list;
};
void Rva002C0A89::rva002C0A89(GameWindow *win)
{
	GameWindow *found = 0;
	GameWindow *cur = m_head;
	if (cur) {
		do {
			List24Node *node = m_list;
			while (node) {
				GameWindow *v = node->m_val;
				if (v == cur && v != win)
					found = cur;
				node = node->m_next;
			}
			cur = cur->m_next;
		} while (cur);
	}
	if (!found) {
		win->m_prev = 0;
		win->m_next = m_head;
		if (m_head)
			m_head->m_prev = win;
		else
			m_tail = win;
		m_head = win;
		return;
	}
	win->m_prev = found;
	win->m_next = found->m_next;
	found->m_next = win;
	if (win->m_next)
		win->m_next->m_prev = win;
}
void Rva002C0A89::rva002C0B92(GameWindow *win)
{
	if (win->m_next)
		win->m_next->m_prev = win->m_prev;
	else
		m_tail = win->m_prev;
	if (win->m_prev)
		win->m_prev->m_next = win->m_next;
	else
		m_head = win->m_next;
}
void __stdcall Rva002C0BD7Remove(GameWindow *win)
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
