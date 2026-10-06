// cl: /O1 /DNDEBUG /MD
// ?winDestroyAll@GameWindowManager@@UAEHXZ @0x002C124C 46B.
// Walk the window list at +0xC via m_next +0x1F8, destroying each window
// through winDestroy (slot 35, 0x8C), then drain the destroy list and return 0.
// Evidence: vtable slot 36 of 0x007C7C90 (GameWindowManager family), caller
// dtor 0x002C5398 and reset 0x002C0A5C, callee rowed processDestroyList
// 0x002C08EF, prev/next flags. Identity: ZH/BFME1 winDestroyAll.
class GameWindow
{
public:
	unsigned char m_pad0[0x08];
	unsigned int m_status;
	unsigned char m_padC[0x1EC];
	GameWindow *m_next;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34)
#undef V
	virtual int winDestroy(GameWindow *window) = 0;
	virtual int winDestroyAll();
protected:
	void processDestroyList();
private:
	char m_pad04[8];
	GameWindow *m_windowList;
};

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
