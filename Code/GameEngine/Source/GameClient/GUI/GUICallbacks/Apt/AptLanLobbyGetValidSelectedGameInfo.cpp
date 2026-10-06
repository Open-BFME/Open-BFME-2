// cl: /GX-
//
// ?GetValidSelectedGameInfo@AptLanLobby@@QAEHXZ, retail 0x00444165, 75 bytes.
// Identity: WorldBuilder's AptLanLobby.cpp:509 asserts m_listboxGames in
// AptLanLobby::GetValidSelectedGameInfo, whose body makes the same
// GadgetListBoxGetSelected / item-data / LANAPI::ValidateGameInfo
// (0x00449969) calls. The int return is this unit's spelling of the
// LANGameInfo pointer the callers cast it back to.
// __thiscall int method no args reading this+0x6a8 as GameWindow*.
// Calls rowed GadgetListBoxGetSelected then rowed Rva003253BEGet then
// rowed LANAPI::ValidateGameInfo via global 0x00DFE958. Returns game or 0.
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
	friend class AptLanLobby;
public:
	virtual void vft() = 0;
	char m_pad0C[0x0C];
	LANGameInfo *m_games;
protected:
	bool ValidateGameInfo(LANGameInfo *game);
};

extern LANAPI *g_00DFE958;

class AptLanLobby
{
public:
	int GetValidSelectedGameInfo();
private:
	char m_pad[0x6a8];
	GameWindow *m_listboxGames;
};

int AptLanLobby::GetValidSelectedGameInfo()
{
	int sel;
	if (m_listboxGames == 0)
		return 0;
	sel = -1;
	GadgetListBoxGetSelected(m_listboxGames, &sel);
	int game = Rva003253BEGet(m_listboxGames, sel, 3);
	LANGameInfo *info = (LANGameInfo *)game;
	if (!g_00DFE958->ValidateGameInfo(info))
		info = 0;
	return (int)info;
}
// ?g_00DFE958@@3PAVLANAPI@@A: the global at VA 0xdfe958 is ?g_Va009FE958@@3PAUGlobal009FE958@@A.
#pragma comment(linker, "/alternatename:?g_00DFE958@@3PAVLANAPI@@A=?g_Va009FE958@@3PAUGlobal009FE958@@A")
