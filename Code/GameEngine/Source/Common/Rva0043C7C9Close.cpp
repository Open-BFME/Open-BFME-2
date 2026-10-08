// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva0043C7C9@Rva0043D3DA@@QAEXH@Z, retail 0x0043C7C9, 105 bytes.
// Same gating and +0x2a2 flag as sibling ?rva0043D3DA@Rva0043D3DA@@QAEXH@Z
// @0x0043D3DA (TheGameLogic+0x110==6 with TheInGameUI+0x16 gate); closes the
// window found by rowed Rva00222547Get via pinned invoke "Close" then hides
// background via rowed rva00222F55; second flag at +0x2a3. Evidence: callers
// 0x0043D14B 0x0043D45B; callees row 0x00222547 pin 0x00222A8B row 0x00222F55.
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class Rva0043D3A8
{
public:
	void rva0043D3A8();
private:
	char m_unk0[8];
	_STL::vector<ScienceType> m_sciences;
	int m_unk14;
};

class GameLogic
{
public:
	char m_pad[0x110];
	int m_gameMode;
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	char m_pad[0x16];
	unsigned char m_16;
};

extern InGameUI *TheInGameUI;

class GameWindow
{
public:
	char m_pad[1];
};

GameWindow *Rva00222547Get(GameWindow *w);

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
	void rva00222F55(bool flag);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva0043D3DA
{
public:
	void rva0043C7C9(int unused);
private:
	char m_pad0[0x27c];
	_STL::vector<void *> m_ptrs;
	Rva0043D3A8 m_sub;
	char m_pad1[2];
	bool m_closed;
	bool m_bgHidden;
};

void Rva0043D3DA::rva0043C7C9(int unused)
{
	(void)unused;
	if (TheGameLogic->m_gameMode == 6) {
		if (TheInGameUI->m_16 == 0)
			return;
	}
	if (m_closed)
		return;
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(Rva00222547Get((GameWindow *)this), "Close", 0, 0, 0, 0, 0, 0);
	m_closed = true;
	if (!m_bgHidden) {
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva00222F55(false);
		m_bgHidden = true;
	}
}
