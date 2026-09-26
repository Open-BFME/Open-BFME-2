// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?registerTabList@GameWindowManager@@UAEXV?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@@Z @0x002C55AC 63B
// GameWindowManager::registerTabList; BFME1 donor GameWindowManager.cpp registerTabList verbatim (m_tabList.clear then m_tabList=tabList); vtable 0x007C7C90 slot 44 offset 0xB0; slots 42-43 winNextTab/winPrevTab rowed in GameWindowManager_winPrevTab.cpp with m_tabList at +0x30 m_modalHead at +0x24; donor header order winNextTab winPrevTab registerTabList clearTabList; ZH header GameWindowManager.h; no callers; callees rowed int list via ICF pins (clear 0x0023DAA5 assign 0x002C54EE base dtor 0x004EC395); flags need bfmelist/bfmealloc shims for base-dtor call plus /EHs for or -1 state (map-insert precedent).
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
	virtual void registerTabList(GameWindowList tabList);
	virtual void clearTabList(void);
#define W(n) virtual void pad##n() = 0;
	W(46) W(47) W(48)
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

void GameWindowManager::registerTabList(GameWindowList tabList)
{
	m_tabList.clear();
	m_tabList = tabList;
}
