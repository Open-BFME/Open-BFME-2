// cl: /DNDEBUG /MD
// ?processDestroyList@GameWindowManager@@IAEXXZ @0x002C08EF 137B: window-list drain with slot calls and delete
// Evidence: neighbours GadgetButtonImageHelpers 0x002C0505 and linkWindow 0x002C0A89 same flags; GameWindow next +0x1F8 from linkWindow; callers update 0x002C0A74 and winDestroyAll 0x002C1271; callees rowed operator delete 0x0002FD60; virtual slots 49/58/62/65
// Identity: ZH/BFME1 GameWindowManager::processDestroyList (release captor,
// focus and modal head, clear mouse region and grab, GWM_DESTROY, delete).
#include "../../../Include/GameClient/Bfme2GameWindow.h"
class ModalWindow
{
public:
	void *m_vtable; // +0x00
	GameWindow *window; // +0x04
	ModalWindow *next; // +0x08
};
#include "../../../Include/GameClient/GameWindowManager.h"
#include <new>
void GameWindowManager::processDestroyList()
{
	GameWindow *cur = m_destroyList;
	m_destroyList = 0;
	if (!cur)
		return;
	GameWindow *next;
	do {
		next = cur->m_next;
		if (m_mouseCaptor == cur)
			winRelease(cur);
		if (m_keyboardFocus == cur)
			winSetFocus(0);
		if (m_modalHead && cur == m_modalHead->window)
			winUnsetModal(m_modalHead->window);
		if (m_currMouseRgn == cur)
			m_currMouseRgn = 0;
		if (m_grabWindow == cur)
			m_grabWindow = 0;
		winSendSystemMsg(cur, 2, 0, 0);
		// Native scalar-deleting-dtor ABI: slot0(flags=0) returns the
		// allocation pointer consumed by operator delete (2C095F..2C0967).
		typedef void *(GameWindow::*ScalarDeletingDtor)(unsigned int);
		typedef char SingleInheritanceMemberPointer[(sizeof(ScalarDeletingDtor)==sizeof(void *))?1:-1];
		void *p = (cur->*(*(ScalarDeletingDtor **)cur)[0])(0);
		::operator delete(p);
		cur = next;
	} while (next);
}
