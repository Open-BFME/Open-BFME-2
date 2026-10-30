// cl: /Ireference/shims/bfme2_ascii /MD
// Twelve derived destructors sharing one shape: clear the field at +0xC,
// restore the class vtable, and tail-call the base destructor at 0x1DBAC3.
// Unidentified owners keep address names. The base uses the rowed
// Rva001DBAA4 identity and its proven 16-byte layout; deleting dtors follow.
// vslot 0x0035DD9C (?Rva0035DD9C@MainMenuMediumScaleUpTransition@@UAEXXZ, 33B, slot 3 offset 0xC
// of vtable 0x00816574): hide windows at +0xC and +0x44 via rowed winHide
// 0x00313C64; clears +0x8/+0x9. Evidence: vtable 0x00816574.
// vslot 0x0035DD08 (?update@MainMenuMediumScaleUpTransition@@UAEXH@Z, 148B, slot 2 offset 0x8
// of vtable 0x00816574): range-select hide via rowed winHide 0x00313C64;
// sets +0x28 to -1 then to index in middle range. Evidence: vtable 0x00816574.
// vslot 0x0035E0F7 (?update@Rva0035E00F@@UAEXH@Z, 142B, slot 2 offset 0x8
// of vtable 0x00816594): same range-select shape with second window at +0x4C
// (not +0x44); first equality branch hides only m_44. Evidence: vtable
// 0x00816594 slot 2 plus rowed winHide 0x00313C64.
// vslot 0x0035E97E (?init@ButtonFlashTransition@@UAEXPAVGameWindow@@@Z, 135B,
// slot 1 offset 0x4 of vtable 0x008165F0): BFME1 ButtonFlash init reuse;
// Gradient image to +0x24 via StringBase/findImage; update(0) via slot 2.
// Evidence: donor GameWindowTransitionsStyles plus string Gradient plus
// vtable 0x008165F0 slot 1 plus winGetSize/Position rows.

// Same base view as Rva001DBAA4Ctor.cpp: native constructor 1DBAA4
// initializes +4/+8/+9/+A/+C and the derived virtuals use +C as a window.
class GameWindow;

class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    GameWindow *m_C; // +0x0C: shared window slot, used by the derived transitions.
};

class GameWindow
{
public:
	int winHide(bool hide);
	int winGetSize(int *width, int *height);
	int winGetScreenPosition(int *x, int *y);
};

class Rva0035D47B : public Rva001DBAA4 { public: virtual ~Rva0035D47B(); };
Rva0035D47B::~Rva0035D47B() { m_C = 0; }
void famgenDelete(Rva0035D47B *p) { delete p; }

class ScoreScaleUpTransition : public Rva001DBAA4 { public: virtual ~ScoreScaleUpTransition(); };
ScoreScaleUpTransition::~ScoreScaleUpTransition() { m_C = 0; }
void famgenDelete(ScoreScaleUpTransition *scoreScaleUpTransition) { delete scoreScaleUpTransition; }

class Rva0035DA01 : public Rva001DBAA4 { public: virtual ~Rva0035DA01(); };
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0035DA01::~Rva0035DA01() { m_C = 0; }

// ?bfmeAnchorRva0035DA01Dtor absent-from-retail
void bfmeAnchorRva0035DA01Dtor(Rva0035DA01 *transition)
{
	transition->Rva0035DA01::~Rva0035DA01();
}
void famgenDelete(Rva0035DA01 *transition) { delete transition; }

class Rva0035D74A : public Rva001DBAA4 { public: virtual ~Rva0035D74A(); int m_pad10[9]; int m_field34; };
Rva0035D74A::~Rva0035D74A() { m_C = 0; m_field34 = 0; }
void famgenDelete(Rva0035D74A *transition) { delete transition; }

class MainMenuMediumScaleUpTransition : public Rva001DBAA4
{
public:
	virtual ~MainMenuMediumScaleUpTransition();
	virtual void slot1();
	virtual void update(int index);
	virtual void Rva0035DD9C();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
private:
	int m_10;
	int m_14;
	char m_pad18[0x28 - 0x18];
	int m_28;
	char m_pad2C[0x44 - 0x2C];
	GameWindow *m_44;
};
MainMenuMediumScaleUpTransition::~MainMenuMediumScaleUpTransition() { m_C = 0; }
void famgenDelete(MainMenuMediumScaleUpTransition *mainMenuMediumScaleUpTransition) { delete mainMenuMediumScaleUpTransition; }

void MainMenuMediumScaleUpTransition::Rva0035DD9C()
{
	GameWindow *gameWindow = m_C;
	m_8 = false;
	m_9 = false;
	gameWindow->winHide(true);
	m_44->winHide(true);
}

void MainMenuMediumScaleUpTransition::update(int index)
{
	m_28 = -1;
	if (index < m_10)
		return;
	if (index > m_14)
		return;
	if (index == m_10) {
		if (!m_9 && m_C != 0 && m_44 != 0) {
			m_C->winHide(false);
			m_44->winHide(true);
			m_8 = true;
		}
	} else if (index == m_14) {
		if (m_9 && m_C != 0 && m_44 != 0) {
			m_C->winHide(true);
			m_44->winHide(false);
			m_8 = true;
		}
	}
	if (index <= m_10)
		return;
	if (index >= m_14)
		return;
	if (m_C != 0)
		m_C->winHide(true);
	if (m_44 != 0)
		m_44->winHide(true);
	m_28 = index;
}

class Rva0035E00F : public Rva001DBAA4
{
public:
	virtual ~Rva0035E00F();
	virtual void slot1();
	virtual void update(int index);
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
private:
	int m_10;
	int m_14;
	char m_pad18[0x28 - 0x18];
	int m_28;
	char m_pad2C[0x4C - 0x2C];
	GameWindow *m_44;
};
Rva0035E00F::~Rva0035E00F() { m_C = 0; }
void famgenDelete(Rva0035E00F *transition) { delete transition; }

void Rva0035E00F::update(int index)
{
	m_28 = -1;
	if (index < m_10)
		return;
	if (index > m_14)
		return;
	if (index == m_10) {
		if (!m_9 && m_C != 0 && m_44 != 0) {
			m_44->winHide(true);
			m_8 = true;
		}
	} else if (index == m_14) {
		if (m_9 && m_C != 0 && m_44 != 0) {
			m_C->winHide(true);
			m_44->winHide(false);
			m_8 = true;
		}
	}
	if (index <= m_10)
		return;
	if (index >= m_14)
		return;
	if (m_C != 0)
		m_C->winHide(true);
	if (m_44 != 0)
		m_44->winHide(true);
	m_28 = index;
}

class Rva0035E2E6 : public Rva001DBAA4 { public: virtual ~Rva0035E2E6(); };
Rva0035E2E6::~Rva0035E2E6() { m_C = 0; }
void famgenDelete(Rva0035E2E6 *transition) { delete transition; }

class Rva0035E60B : public Rva001DBAA4 { public: virtual ~Rva0035E60B(); };
Rva0035E60B::~Rva0035E60B() { m_C = 0; }
void famgenDelete(Rva0035E60B *transition) { delete transition; }

// ?init@ButtonFlashTransition@@UAEXPAVGameWindow@@@Z @ 0x0035E97E (135B):
// slot 1 offset 0x4 of vtable 0x008165F0 (class of ??1Rva0035E60B@@UAE@XZ).
// Direct reuse of open-bfme-1 ButtonFlashTransition::init
// (GameWindowTransitionsStyles.cpp + ButtonFlashTransition_init_Thunk.cpp):
// winGetSize/Position into +0x18/+0x1C/+0x10/+0x14, update(0) via slot 2,
// isFinished/isForward at +8/+9, Gradient image to +0x24 via rowed
// StringBase ctor 0x37BA0, findImage 0x2D92F6 and pinned dtor 0x36410.
#include "../../../Libraries/Include/Lib/ICoord2D.h"

#include "ascii_string.h"


class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;
// TheMappedImageCollection: matched references place it at VA 0xdff078 (zero-filled .bss).
ImageCollection * TheMappedImageCollection;

class Transition
{
public:
	virtual ~Transition();
	virtual void init(GameWindow *) = 0;
	virtual void update(int) = 0;
	virtual void reverse() = 0;
	virtual void draw() = 0;
	virtual void skip() = 0;

protected:
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	unsigned char m_pad0b;
	GameWindow *m_win;
};

class ButtonFlashTransition : public Transition
{
public:
	virtual void init(GameWindow *);

protected:
	ICoord2D m_pos;
	ICoord2D m_size;
	int m_drawState;
	const Image *m_gradient;
};

void ButtonFlashTransition::init(GameWindow *win)
{
	if (win) {
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);
	}
	m_isForward = false;
	update(0);
	m_isFinished = false;
	m_isForward = true;
	AsciiString gradient("Gradient");
	m_gradient = TheMappedImageCollection->findImageByName(gradient);
}

class Rva0035EE66 : public Rva001DBAA4 { public: virtual ~Rva0035EE66(); };
Rva0035EE66::~Rva0035EE66() { m_C = 0; }
void famgenDelete(Rva0035EE66 *transition) { delete transition; }

class Rva0035F1D0 : public Rva001DBAA4 { public: virtual ~Rva0035F1D0(); };
Rva0035F1D0::~Rva0035F1D0() { m_C = 0; }
void famgenDelete(Rva0035F1D0 *transition) { delete transition; }

class Rva0035F4A6 : public Rva001DBAA4 { public: virtual ~Rva0035F4A6(); };
Rva0035F4A6::~Rva0035F4A6() { m_C = 0; }
void famgenDelete(Rva0035F4A6 *transition) { delete transition; }

class Rva0035FA2A : public Rva001DBAA4 { public: virtual ~Rva0035FA2A(); };
Rva0035FA2A::~Rva0035FA2A() { m_C = 0; }
void famgenDelete(Rva0035FA2A *transition) { delete transition; }

// Same virtuals as Rva0035FF76Ctor.cpp's view, so both units emit one
// ??_7Rva0035FF76@@6B@ (its slots resolve as in that unit).
class Rva0035FF76 : public Rva001DBAA4
{
public:
	virtual ~Rva0035FF76();
	virtual void init(void *win);
	virtual void update(int frame);
	virtual void reverse() = 0;
	virtual void draw();
	virtual void skip();
	virtual bool isFinished() = 0;
	virtual int getFrameLength();
};
Rva0035FF76::~Rva0035FF76() { m_C = 0; }
void famgenDelete(Rva0035FF76 *transition) { delete transition; }


// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot1@MainMenuMediumScaleUpTransition@@UAEXXZ=?init@MainMenuMediumScaleUpTransition@@UAEXPAVGameWindow@@@Z")
#pragma comment(linker, "/alternatename:?slot5@MainMenuMediumScaleUpTransition@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot7@MainMenuMediumScaleUpTransition@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot1@Rva0035E00F@@UAEXXZ=?init@MainMenuScaleUpTransition@@UAEXPAVGameWindow@@@Z")
#pragma comment(linker, "/alternatename:?slot5@Rva0035E00F@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot7@Rva0035E00F@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot3@Rva0035E00F@@UAEXXZ=?rva0035D1BD@Rva0035D1BD@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot4@MainMenuMediumScaleUpTransition@@UAEXXZ=?draw@MainMenuMediumScaleUpTransition@@UAEXXZ")
#pragma comment(linker, "/alternatename:?slot4@Rva0035E00F@@UAEXXZ=?draw@MainMenuScaleUpTransition@@UAEXXZ")
#pragma comment(linker, "/alternatename:?slot6@MainMenuMediumScaleUpTransition@@UAEXXZ=?rva0035D1E7@Rva0035D1E7@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot6@Rva0035E00F@@UAEXXZ=?rva0035D1E7@Rva0035D1E7@@QAEXXZ")
