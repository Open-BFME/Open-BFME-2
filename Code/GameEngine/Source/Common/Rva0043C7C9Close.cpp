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
	void rva0043D5CB(ScienceType science);

private:
	char m_unk0[8];
	_STL::vector<ScienceType> m_sciences;
	int m_unk14;
};

#include "GameLogicObjectLookupView.h"

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

class AptPlayer { public: static int GetLevelIndex(GameWindow *window); };

class Rva00222A8BTarget
{
public:
	int invoke(void *window, const char *function, int argc, const char *arg,
		void *arg1, void *arg2, void *arg3, void *arg4);
	void rva00222F55(bool flag);
	void rva002233A6(int mode);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva0043D3DA
{
public:
	void rva0043C7C9(int unused);
	void rva0043D3DA(int unused);

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
	if (TheGameLogic->m_110 == 6) {
		if (TheInGameUI->m_16 == 0)
			return;
	}
	if (m_closed)
		return;
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "Close", 0, 0, 0, 0, 0, 0);
	m_closed = true;
	if (!m_bgHidden) {
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva00222F55(false);
		m_bgHidden = true;
	}
}
