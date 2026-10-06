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
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	GameWindow *m_C;
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
		m_C = win;
		m_C->winGetSize(&m_18, &m_1C);
		m_C->winGetScreenPosition(&m_10, &m_14);
	}
	m_9 = false;
	update(0);
	m_8 = false;
	m_9 = true;
}
