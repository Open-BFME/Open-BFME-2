// ?rva00314056@GameWindow@@QAEHH@Z
// partial score=0.93 date=2026-10-01
// cl: /MD
// ?rva00314056@GameWindow@@QAEHH@Z, retail 0x00314056, 78 bytes.
// Honest GameWindow method: detach from old parent/list then attach.
// Evidence: this+0x200 is GameWindow::m_parent (same offset as
// GameWindow_winGetScreenPosition.cpp); this passed as GameWindow* to
// rowed ?rva002C0A89/?rva002C0B92@Rva002C0A89 and __stdcall
// ?Rva002C0BD7Remove@@YGX; second half virtual call [eax+0xE0] on
// TheWindowManager (?TheWindowManager@@3PAVGameWindowManager@@A);
// returns 0 (xor eax) with ret 4.

class GameWindow;

class Rva002C0A89
{
public:
	void rva002C0A89(GameWindow *win);
	void rva002C0B92(GameWindow *win);
};

void __stdcall Rva002C0BD7Remove(GameWindow *win);

class GameWindowManager
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
	virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
	virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
	virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
	virtual void VirtualE0(GameWindow *win, int arg);
};

extern GameWindowManager *TheWindowManager;

class GameWindow
{
public:
	int rva00314056(int arg);
private:
	char m_pad[0x200];
	GameWindow *m_parent;
};

int GameWindow::rva00314056(int arg)
{
	Rva002C0A89 *mgr = *(Rva002C0A89 * volatile *)&TheWindowManager;
	if (m_parent == 0)
		mgr->rva002C0B92(this);
	else
		Rva002C0BD7Remove(this);
	GameWindowManager *mgr2 = TheWindowManager;
	if (arg == 0) {
		((Rva002C0A89 *)mgr2)->rva002C0A89(this);
		m_parent = 0;
	} else {
		mgr2->VirtualE0(this, arg);
	}
	return 0;
}
