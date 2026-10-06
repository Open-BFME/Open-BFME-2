// cl: /DNDEBUG /MD
//
// ?rva003236E8@Rva003236E8@@QAEHXZ, retail 0x003236E8, 24 bytes.
// __thiscall int method with no args reading this+0 as GameWindow*.
// Calls rowed winGetUserData then rowed GadgetListBoxGetNumEntries.
// Evidence: callees rowed 0x005C4ACD winGetUserData plus 0x0032475A GadgetListBoxGetNumEntries; prev/next same flags.

class GameWindow
{
public:
	void *winGetUserData();
};

int GadgetListBoxGetNumEntries(GameWindow *window);

struct Rva003236E8Data
{
	char m_pad[8];
	GameWindow *m_win;
};

class Rva003236E8
{
public:
	int rva003236E8();
private:
	GameWindow *m_win;
};

int Rva003236E8::rva003236E8()
{
	if (m_win == 0)
		return 0;
	Rva003236E8Data *data = (Rva003236E8Data *)m_win->winGetUserData();
	return GadgetListBoxGetNumEntries(data->m_win);
}
