// cl: /MD
// ?rva0035EDA1@Rva0035EE66@@UAEXPAVGameWindow@@@Z @ 0x0035EDA1 68B: slot 1 init of vtable 0x0081661C.
// Same shape as ButtonFlashTransition::init in FamilyTailDtors1DBAC3.cpp but without Gradient tail:
// store win to +0xC, winGetSize into +0x18/+0x1C, winGetScreenPosition into +0x10/+0x14,
// clear +0x9, update(0) via slot 2, clear +0x8, set +0x9. Evidence: vtable 0x0081661C slot 1
// plus rowed winGetSize 0x00313BC6 and winGetScreenPosition 0x00313B3C.
class GameWindow
{
public:
	int winGetSize(int *width, int *height);
	int winGetScreenPosition(int *x, int *y);
};

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

class Rva0035EE66 : public Rva001DBAA4
{
public:
	virtual ~Rva0035EE66();
	virtual void rva0035EDA1(GameWindow *win);
	virtual void update(int frame);
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

void Rva0035EE66::rva0035EDA1(GameWindow *win)
{
	if (win) {
		m_win = win;
		m_win->winGetSize(&m_18, &m_1C);
		m_win->winGetScreenPosition(&m_10, &m_14);
	}
	m_isForward = false;
	update(0);
	m_isFinished = false;
	m_isForward = true;
}
