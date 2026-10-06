// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?init@MainMenuSmallScaleDownTransition@@UAEXPAVGameWindow@@@Z
// retail 0x0035DBF3, 262 bytes. Dedicated TU.
//
// Ported from Open-BFME-1
// Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// MainMenuSmallScaleDownTransition::init: cache the window size/position,
// resolve the Small-suffixed grow marker window by name key, snapshot its
// size/position, run one update step, then derive the two per-frame increments
// and install the window's enabled image as the grow window's enabled image.
// Retail adaptations, all measured from the target bytes:
// winGetSize/winGetScreenPosition stay out-of-line (declared-only here,
// resolved to their matched rows); winGetInstanceData is the rowed disp8 lea
// getter 0x00314046 (same address as the pinned spelling); AsciiString copy
// assignment at 0x366F0 and StringBase concat at 0x5629 are declared-only;
// nameToKey(AsciiString) at 0x9FA65 is declared-only; winGetWindowFromId is
// virtual at slot 0xF0 (60 pads); update is virtual at slot 8;
// winSetEnabledImage is the int-returning out-of-line helper at 0x3143B9;
// the enabled image reads straight out of win+0x48; the divisor is the
// constant 6.

typedef int Int;
typedef unsigned char Bool;

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

struct ICoord2D
{
	Int x;
	Int y;
};

class Image;

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winSetEnabledImage(Int index, const Image *image);
};

class WinInstanceData;

class Rva00314046LeaField
{
public:
	void *get() const;
};

#include "ascii_string.h"


struct SmallScaleDownInstanceData
{
	unsigned char m_pad[0x18c];
	AsciiString m_decoratedNameString;
};

struct SmallScaleDownWindowImages
{
	unsigned char m_pad[0x48];
	const Image *m_enabledImage;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);
};

extern GameWindowManager *TheWindowManager;

class MainMenuSmallScaleDownTransition
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void update(Int frame);
	virtual void init(GameWindow *win);

	Int m_frameLength;			// +0x04
	Bool m_isFinished;			// +0x08
	Bool m_isForward;			// +0x09
	unsigned char m_pad0a[2];
	GameWindow *m_win;			// +0x0c
	ICoord2D m_pos;				// +0x10
	ICoord2D m_size;			// +0x18
	Int m_drawState;			// +0x20
	ICoord2D m_growPos;			// +0x24
	ICoord2D m_growSize;			// +0x2c
	ICoord2D m_incrementSize;		// +0x34
	GameWindow *m_growWin;			// +0x3c
};

void MainMenuSmallScaleDownTransition::init(GameWindow *win)
{
	if (win) {
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);
	}
	AsciiString growWinName;
	growWinName = ((SmallScaleDownInstanceData *)((Rva00314046LeaField *)m_win)->get())->m_decoratedNameString;
	((StringBase<char> &)growWinName).concat("Small");
	m_growWin = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey(growWinName));
	if (!m_growWin)
		return;

	m_growWin->winGetSize(&m_growSize.x, &m_growSize.y);
	m_growWin->winGetScreenPosition(&m_growPos.x, &m_growPos.y);

	m_isForward = FALSE;
	update(0);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_incrementSize.x = (m_growSize.x - m_size.x) / 6;
	m_incrementSize.y = (m_growSize.y - m_size.y) / 6;
	const Image *image = ((const SmallScaleDownWindowImages *)m_win)->m_enabledImage;
	m_growWin->winSetEnabledImage(0, image);
}
