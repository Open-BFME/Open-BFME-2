// cl: /DNDEBUG /MD /EHsc
// ?Rva0041154FHide@@YAXXZ, retail 0x0041154F 90B.
// Window-video table walk over global at 0x00E02FE4 via first 0x00427195 and
// rowed next 0x00411084, hiding visible windows and setting status 0x10000000.
// Same first/next shape as Rva00411523Walk; node GameWindow at +0x18 flag at +0x2C.
// Evidence: winIsHidden 0x313CD9 winHide 0x313C64 winSetStatus 0x313CE3 caller 0x22246C.
class Rva000411084
{
public:
	void *next();
	void *m_current;
	void *m_owner;
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iter);
};

extern Rva000427195 g_00E02FE4;

class GameWindow
{
public:
	bool winIsHidden();
	int winHide(bool hide);
	unsigned int winSetStatus(unsigned int status);
};

struct Rva0041154FNode
{
	char m_pad[0x18];
	GameWindow *m_18;
	char m_pad2[0x2C - 0x18 - 4];
	unsigned char m_2C;
};

void Rva0041154FHide()
{
	Rva000411084 iter;
	g_00E02FE4.first(&iter);
	while (iter.m_current != 0) {
		Rva0041154FNode *node = (Rva0041154FNode *)iter.m_current;
		if (node->m_2C == 0) {
			GameWindow *win = node->m_18;
			if (win != 0) {
				if (!win->winIsHidden()) {
					win->winHide(true);
					win->winSetStatus(0x10000000);
				}
			}
		}
		iter.next();
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00E02FE4@@3VRva000427195@@A=?g_Va00E02FE4@@3URva004114EFGlobalTable@@A")
