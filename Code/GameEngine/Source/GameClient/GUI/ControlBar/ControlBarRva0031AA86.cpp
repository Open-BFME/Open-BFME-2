// cl: /DNDEBUG /MD
// ?rva0031AA86@ControlBar@@QAEHXZ @ 0x0031AA86 152B: ControlBar ButtonGeneral
// refresh via TheWindowManager->winGetWindowFromId(NULL,
// TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral")) then
// GadgetButtonSetEnabledImage on +0x270/+0x274 blinked by frame%period.
// Evidence: string literal plus rowed nameToKey plus rowed Gadget helper
// plus caller 0x0031E25E plus ControlBar sibling 0x0031AE13 layout.
class Image;

class GameWindow
{
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
};

extern GameWindowManager *TheWindowManager;

void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *win, const Image *image);

struct MoneyInner
{
	char m_pad00[0x24];
	int m_money;
};

class PlayerList
{
public:
	char m_pad00[0x10];
	MoneyInner *m_p0010;
};

extern PlayerList *ThePlayerList;

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_0040;
};

extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

class ControlBar
{
public:
	int rva0031AA86();

private:
	char m_pad00[0x270];
	const Image *m_p0270;
	const Image *m_p0274;
	unsigned char m_0278;
	char m_pad279[0x27c - 0x279];
	int m_027C;
};

int ControlBar::rva0031AA86()
{
	int money = ThePlayerList->m_p0010->m_money;
	if (m_027C <= money && money > 0)
		m_027C = money;
	else
		m_0278 = 0;
	GameWindow *win = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
	if (win == 0)
		return 0;
	if (m_0278 == 0) {
		GadgetButtonSetEnabledImage_Rva002C0433(win, m_p0270);
		return 0;
	}
	unsigned int frame = TheGameLogic->m_0040;
	int period = g_Va00DBA4E4;
	if (frame % (unsigned int)period > (unsigned int)(period / 2))
		GadgetButtonSetEnabledImage_Rva002C0433(win, m_p0274);
	else
		GadgetButtonSetEnabledImage_Rva002C0433(win, m_p0270);
	return 0;
}
