class GameWindow;
void GadgetListBoxSetListLength(GameWindow* w, int len);
void __cdecl rva00381618(GameWindow* a, int b);

struct Rva005AFC21Class
{
	int m_0;
	int m_4;
	int m_8;
	GameWindow* m_C;

	void rva005AFC21(GameWindow* a1);
};

// cl: -GR- -EHsc-
// ?rva005AFC21@Rva005AFC21Class@@QAEXPAVGameWindow@@@Z @0x005AFC21 43B:
// stores the window, returns early on null, else forwards (window, 1000) to
// the rowed list-length helper and (m_4, m_C) to the pinned cdecl callee.
void Rva005AFC21Class::rva005AFC21(GameWindow* a1)
{
	m_C = a1;
	if (!a1)
		return;
	GadgetListBoxSetListLength(a1, 0x3E8);
	rva00381618(m_C, m_4);
}

// ?rva005AFC4C@Rva005AFC4CClass@@QAEXPAVGameWindow@@@Z @0x005AFC4C 70B: the
// neighbouring list holder's setter (+0x10 window, +0x14 cleared). A non-null
// list box is made multi-select (rowed GadgetListBoxAddMultiSelect), given
// 1000 rows (rowed GadgetListBoxSetListLength) and its list data's +0x12
// flag is set and stored back (rowed winGetUserData/winSetUserData). The
// WorldBuilder twin (0x01518840) is unnamed.
void GadgetListBoxAddMultiSelect(GameWindow *w);

class GameWindow
{
public:
	void *winGetUserData();
	void winSetUserData(void *data);
};

struct Rva005AFC4CListData
{
	unsigned char m_pad00[0x12];
	bool m_12;
};

struct Rva005AFC4CClass
{
	unsigned char m_pad00[0x10];
	GameWindow *m_10;
	int m_14;

	void rva005AFC4C(GameWindow *window);
};

void Rva005AFC4CClass::rva005AFC4C(GameWindow *window)
{
	m_14 = 0;
	m_10 = window;
	if (!window)
		return;
	GadgetListBoxAddMultiSelect(window);
	GadgetListBoxSetListLength(m_10, 1000);
	Rva005AFC4CListData *data = (Rva005AFC4CListData *)m_10->winGetUserData();
	if (data)
	{
		data->m_12 = true;
		m_10->winSetUserData(data);
	}
}
