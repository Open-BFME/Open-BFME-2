// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
// ?winPrevTab@GameWindowManager@@UAEXPAVGameWindow@@@Z @0x002C5473 123B
// GameWindowManager::winPrevTab; BFME1 donor GameWindowManager.cpp winPrevTab verbatim; m_tabList at +0x30 m_modalHead at +0x24; vtable 0x7C7C90 slot 43 offset 0xAC; calls winSetFocus slot 49 0xC4 and winSetLoneWindow slot 52 0xD0.
#include <list>

class GameWindow;

typedef _STL::list<GameWindow *> GameWindowList;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
#undef V
	virtual void winNextTab(GameWindow *window);
	virtual void winPrevTab(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(44) W(45) W(46) W(47) W(48)
#undef W
	virtual int winSetFocus(GameWindow *window);
#define X(n) virtual void pad##n() = 0;
	X(50) X(51)
#undef X
	virtual void winSetLoneWindow(GameWindow *window);

private:
	unsigned char m_pad04[0x20];
	void *m_modalHead;
	unsigned char m_pad28[0x08];
	GameWindowList m_tabList;
};

void GameWindowManager::winNextTab(GameWindow *window)
{
	if (m_tabList.size() == 0 || m_modalHead)
		return;

	GameWindowList::iterator it = m_tabList.begin();
	while (it != m_tabList.end())
	{
		if (*it == window)
		{
			it++;
			break;
		}
		it++;
	}
	if (it != m_tabList.end())
		winSetFocus(*it);
	else
	{
		winSetFocus(*m_tabList.begin());
	}
	winSetLoneWindow(0);
}

void GameWindowManager::winPrevTab(GameWindow *window)
{
	if (m_tabList.size() == 0 || m_modalHead)
		return;

	GameWindowList::reverse_iterator it = m_tabList.rbegin();
	while (it != m_tabList.rend())
	{
		if (*it == window)
		{
			it++;
			break;
		}
		it++;
	}
	if (it != m_tabList.rend())
		winSetFocus(*it);
	else
	{
		winSetFocus(*m_tabList.rbegin());
	}
	winSetLoneWindow(0);
}
