// cl: /DNDEBUG /MD
// ?processDestroyList@GameWindowManager@@IAEXXZ @0x002C08EF 137B: window-list drain with slot calls and delete
// Evidence: neighbours GadgetButtonImageHelpers 0x002C0505 and linkWindow 0x002C0A89 same flags; GameWindow next +0x1F8 from linkWindow; callers update 0x002C0A74 and winDestroyAll 0x002C1271; callees rowed operator delete 0x0002FD60; virtual slots 49/58/62/65
// Identity: ZH/BFME1 GameWindowManager::processDestroyList (release captor,
// focus and modal head, clear mouse region and grab, GWM_DESTROY, delete).
class GameWindow
{
public:
	virtual void *slot0(int arg);
private:
	unsigned char m_pad[0x1F8 - 4];
public:
	GameWindow *m_next;
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
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
	virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
	virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
	virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47();
	virtual void p48();
	virtual void winSetFocus(GameWindow *window);
	virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53();
	virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57();
	virtual void winSendSystemMsg(GameWindow *win, int msg, int a, int b);
	virtual void p59(); virtual void p60(); virtual void p61();
	virtual void winRelease(GameWindow *win);
	virtual void p63(); virtual void p64();
	virtual void winUnsetModal(GameWindow *win);
protected:
	void processDestroyList();
private:
	unsigned char m_pad04[0x14 - 4];
	GameWindow *m_destroyList;
	GameWindow *m_currMouseRgn;
	GameWindow *m_mouseCaptor;
	GameWindow *m_keyboardFocus;
	ModalWindow *m_modalHead;
	GameWindow *m_grabWindow;
};
void __cdecl operator delete(void *p);
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
		void *p = cur->slot0(0);
		::operator delete(p);
		cur = next;
	} while (next);
}
