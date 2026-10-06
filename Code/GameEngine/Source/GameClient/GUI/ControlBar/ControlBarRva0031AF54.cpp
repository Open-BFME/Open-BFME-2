// ?rva0031AF54@Rva0031AF54@@QAEX_N@Z
// partial score=0.92 date=2026-09-30
// cl: /DNDEBUG /MD
// ?rva0031AF54@Rva0031AF54@@QAEX_N@Z @0x0031AF54 120B: search 10-window list at +0xA8 count +0xD0 for first with userData then animate via manager +0x14 and window +0xD8. Evidence: packet disasm with rowed winGetUserData 0x005C4ACD and registerGameWindow 0x0053B843 reverseAnimateWindow 0x0053B417 and virtual slot 9 at +0x24.
class GameWindow
{
public:
	void *winGetUserData();
};

enum AnimTypes
{
	WIN_ANIMATION_NONE = 0,
	WIN_ANIMATION_SLIDE_RIGHT,
	WIN_ANIMATION_SLIDE_RIGHT_FAST,
	WIN_ANIMATION_SLIDE_LEFT,
	WIN_ANIMATION_SLIDE_TOP,
	WIN_ANIMATION_SLIDE_BOTTOM,
	WIN_ANIMATION_SPIRAL,
	WIN_ANIMATION_SLIDE_BOTTOM_TIMED,
	WIN_ANIMATION_SLIDE_TOP_FAST,
	WIN_ANIMATION_COUNT
};

class AnimateWindowManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void unknown09();
	void registerGameWindow(GameWindow *win, AnimTypes animType, bool needsToFinish, unsigned int ms, unsigned int delayMs);
	void reverseAnimateWindow();
};

class Rva0031AF54
{
public:
	void rva0031AF54(bool flag);

	unsigned char m_pad00[0x14];
	AnimateWindowManager *m_manager;
	unsigned char m_pad18[0x90];
	GameWindow *m_list[10];
	int m_count;
	int m_unkD4;
	GameWindow *m_window;
};

void Rva0031AF54::rva0031AF54(bool flag)
{
	if (m_window == 0)
		return;
	if (m_manager == 0)
		return;
	if (m_count == 0)
		return;
	int i = 0;
	for (; i < m_count; ++i) {
		if (m_list[i]->winGetUserData() == 0)
			continue;
		if (flag) {
			m_manager->unknown09();
			m_manager->registerGameWindow(m_window, WIN_ANIMATION_SLIDE_RIGHT, true, 500, 0);
		} else {
			m_manager->reverseAnimateWindow();
		}
		break;
	}
}
