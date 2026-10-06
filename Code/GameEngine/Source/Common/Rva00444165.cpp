// cl: /GX-
//
// ?rva00444165@Rva00444165@@QAEHXZ, retail 0x00444165, 75 bytes.
// __thiscall int method no args reading this+0x6a8 as GameWindow*.
// Calls rowed GadgetListBoxGetSelected then rowed Rva003253BEGet then
// rowed LANAPI::rva00449969 via global 0x00DFE958. Returns game or 0.
// Evidence: chain lane calls 0x003253BE; callers 0x00444704 0x0044489F.

class GameWindow
{
public:
	void *winGetUserData();
};

void GadgetListBoxGetSelected(GameWindow *listbox, int *selectList);
int Rva003253BEGet(GameWindow *window, int a, int b);

class LANGameInfo
{
public:
	char m_pad[0xF5C];
	LANGameInfo *m_next;
};

class LANAPI
{
	friend class Rva00444165;
public:
	virtual void vft() = 0;
	char m_pad0C[0x0C];
	LANGameInfo *m_games;
protected:
	bool rva00449969(LANGameInfo *game);
};

extern LANAPI *g_00DFE958;

class Rva00444165
{
public:
	int rva00444165();
private:
	char m_pad[0x6a8];
	GameWindow *m_win6a8;
};

int Rva00444165::rva00444165()
{
	int sel;
	if (m_win6a8 == 0)
		return 0;
	sel = -1;
	GadgetListBoxGetSelected(m_win6a8, &sel);
	int game = Rva003253BEGet(m_win6a8, sel, 3);
	LANGameInfo *info = (LANGameInfo *)game;
	if (!g_00DFE958->rva00449969(info))
		info = 0;
	return (int)info;
}
// ?g_00DFE958@@3PAVLANAPI@@A: the global at VA 0xdfe958 is ?g_Va009FE958@@3PAUGlobal009FE958@@A.
#pragma comment(linker, "/alternatename:?g_00DFE958@@3PAVLANAPI@@A=?g_Va009FE958@@3PAUGlobal009FE958@@A")
