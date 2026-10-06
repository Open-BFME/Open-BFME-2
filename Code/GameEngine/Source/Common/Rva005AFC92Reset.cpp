// cl: /MD
//
// ?rva005AFC92@Rva005AFC92@@QAE_NXZ, retail 0x005AFC92, 34 bytes. Clears
// +4 via rowed 0x00381C2D then resets +0xC via rowed GadgetListBoxReset
// 0x003247E5 when non-null, returning 1/0. Evidence: chain packet calls
// just-landed 0x00381C2D; caller jmp at 0x0057FD75; same clear-then-reset
// shape as siblings.
void __cdecl Rva00381C2DClear(unsigned int value);

class GameWindow
{
public:
	int winEnable(bool enable);
	bool winIsHidden();
};
void __cdecl GadgetListBoxReset(GameWindow *win);

class Rva005AFC92
{
public:
	bool rva005AFC92();
	void rva005AFCFF();
	bool rva005AFD2E();
private:
	char m_pad00[4];
	unsigned int m_val04;
	GameWindow *m_win08;
	GameWindow *m_win0C;
	GameWindow *m_win10;
};

bool Rva005AFC92::rva005AFC92()
{
	Rva00381C2DClear(m_val04);
	GameWindow *win = m_win0C;
	if (win != 0) {
		GadgetListBoxReset(win);
		return true;
	}
	return false;
}

void Rva005AFC92::rva005AFCFF()
{
	GameWindow *win08 = m_win08;
	if (win08 != 0) {
		win08->winEnable(true);
	}
	GameWindow *win0C = m_win0C;
	if (win0C != 0) {
		win0C->winEnable(true);
	}
	GameWindow *win10 = m_win10;
	if (win10 != 0) {
		win10->winEnable(true);
	}
}

// ?rva005AFD2E@Rva005AFC92@@QAE_NXZ, retail 0x005AFD2E, 21 bytes. Loads
// +0xC window then returns !winIsHidden via rowed 0x00313CD9. Evidence:
// unlock packet caller jmp 0x0057FDAB; neighbours share // cl: /O1 /MD.
bool Rva005AFC92::rva005AFD2E()
{
	GameWindow *win = m_win0C;
	if (win != 0) {
		return !win->winIsHidden();
	}
	return false;
}
