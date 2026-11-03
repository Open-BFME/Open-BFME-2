// ??0MainMenuMediumScaleUpTransition@@QAE@XZ
// cl: /MD
//
// ??0MainMenuMediumScaleUpTransition@@QAE@XZ @0x0035DE55 80B: derived ctor calling base
// ??0Rva001DBAA4 at 0x001DBAA4, the shorter sibling of the rowed
// Rva0035E00F ctor 0x0035E206 (Rva0035E00FFinish.cpp, same three levers):
// window +0x10..+0x44 with +0x14 = 3 and +0x28 = -1, vtable 0x00C16574
// (the rowed destructor 0x0035DCF9 and vslots 0x0035DD08/0x0035DD9C share
// it), then the base +4 takes +0x14, +0xC clears and +9 is set.
extern "C" const void *const vtbl_00C16574[];  // ??_7MainMenuMediumScaleUpTransition@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C16574=??_7MainMenuMediumScaleUpTransition@@6B@")

#include "../../../Libraries/Include/Lib/ICoord2D.h"

class GameWindow;
class Rva001DBAA4
{
public:
	Rva001DBAA4();
	virtual ~Rva001DBAA4();
	int m_frameLength; // +0x04 +0x04 +0x04
	bool m_isFinished; // +0x08 +0x08 +0x08
	bool m_isForward; // +0x09 +0x09 +0x09
	bool m_isReversed; // +0x0A +0x0A +0x0a
	char m_pad0B[0x1];
	GameWindow *m_win; // +0x0C +0x0C +0x0c
};
class __declspec(novtable) MainMenuMediumScaleUpTransition : public Rva001DBAA4
{
public:
	MainMenuMediumScaleUpTransition();
	virtual ~MainMenuMediumScaleUpTransition();
	virtual void init(GameWindow *win);
	virtual void update(int frame);

	int m_startFrame;          // +0x10
	int m_endFrame;            // +0x14
	ICoord2D m_pos;            // +0x18
	ICoord2D m_size;           // +0x20
	int m_drawState;           // +0x28
	ICoord2D m_growPos;        // +0x2c
	ICoord2D m_growSize;       // +0x34
	ICoord2D m_incrementSize;  // +0x3c
	GameWindow *m_growWin;     // +0x44
};
MainMenuMediumScaleUpTransition::MainMenuMediumScaleUpTransition()
{
	int *p28 = &m_drawState;
	int *p14 = &m_endFrame;
	m_startFrame = 0;
	m_endFrame = 3;
	*(unsigned int *)this = ((unsigned int)vtbl_00C16574);
	int *p18 = &m_pos.x;
	*p18 = 0;
	m_pos.y = 0;
	m_size.x = 0;
	m_size.y = 0;
	*p28 = -1;
	m_growPos.x = 0;
	m_growPos.y = 0;
	m_growSize.x = 0;
	m_growSize.y = 0;
	m_incrementSize.x = 0;
	m_incrementSize.y = 0;
	m_frameLength = *p14;
	m_growWin = 0;
	m_win = 0;
	m_isForward = true;
}
