// cl: /DNDEBUG /MD
// ?rva0031AE13@ControlBar@@QAEXXZ @ 0x0031AE13 128B: ControlBar button-large
// image refresh via TheWindowManager->winGetWindowFromId(NULL,
// TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonLarge")) then
// GadgetButton helpers on +0x250/+0x254/+0x258 when +0x24==2 else
// +0x260/+0x25c/+0x264. Evidence: string literal plus rowed nameToKey plus
// rowed Gadget helpers plus caller 0x0031B0CE family plus neighbours.
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
void GadgetButtonSetHiliteImage_Rva002C04DB(GameWindow *win, const Image *image);
void GadgetButtonSetHiliteImage123_Rva002C0505(GameWindow *win, const Image *image);

class ControlBar
{
public:
	void rva0031AE13();

private:
	char m_pad00[0x24];
	int m_0024;
	char m_pad28[0x250 - 0x28];
	const Image *m_p0250;
	const Image *m_p0254;
	const Image *m_p0258;
	const Image *m_p025C;
	const Image *m_p0260;
	const Image *m_p0264;
};

void ControlBar::rva0031AE13()
{
	GameWindow *win = TheWindowManager->winGetWindowFromId(0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonLarge"));
	if (win == 0)
		return;
	if (m_0024 == 2) {
		GadgetButtonSetEnabledImage_Rva002C0433(win, m_p0254);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, m_p0250);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, m_p0258);
	} else {
		GadgetButtonSetEnabledImage_Rva002C0433(win, m_p0260);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, m_p025C);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, m_p0264);
	}
}
