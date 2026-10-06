// cl: /DNDEBUG /MD
//
// ?rva003236C4@Rva003236C4@@QAEHH@Z, retail 0x003236C4, 36 bytes.
// __thiscall int method with 1 int arg reading this+0 as GameWindow*.
// Calls rowed winGetUserData then rowed Rva003253BEGet just landed.
// Evidence: chain lane calls 0x003253BE; callers 0x00323D1F 0x0043ED13.

class GameWindow
{
public:
	void *winGetUserData();
};

int Rva003253BEGet(GameWindow *window, int a, int b);

struct Rva003236C4Data
{
	char m_pad[8];
	GameWindow *m_win;
};

class Rva003236C4
{
public:
	int rva003236C4(int a);
private:
	GameWindow *m_win;
};

int Rva003236C4::rva003236C4(int a)
{
	if (m_win == 0)
		return 0;
	Rva003236C4Data *data = (Rva003236C4Data *)m_win->winGetUserData();
	GameWindow *v = data->m_win;
	return Rva003253BEGet(v, a, 0);
}
