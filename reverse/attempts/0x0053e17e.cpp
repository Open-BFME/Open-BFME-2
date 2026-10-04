// ?rva0053E17E@Rva0053E17E@@QAEXIM@Z
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva0053E17E@Rva0053E17E@@QAEXIM@Z @0x0053E17E 312B
// OCL timer display update: two static NameKeys plus window lookups plus minutes/seconds div plus GameText fetch plus UnicodeString format plus SetText plus ProgressBar percent via kF7C plus save total at +0x7C. Evidence: rowed nameToKey 0x00148E1A winGet 0xF0 fetch 0x44 format 0x006CB660 copy 0x00037050 SetText 0x00321552 SetProgress 0x003215FB release 0x00036E70; strings ControlBar.wnd OCLTimerStaticText ProgressBar CONTROLBAR OCLTimerDesc Padding; globals TheNameKeyGenerator TheWindowManager TheGameText kF7C; caller 0x0053E333; neighbour ControlBarUpdateConstruction pattern.
#include "unicode_string.h"
typedef int Int;
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
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
	virtual void pad40(); virtual void pad41(); virtual void pad42(); virtual void pad43();
	virtual void pad44(); virtual void pad45(); virtual void pad46(); virtual void pad47();
	virtual void pad48(); virtual void pad49(); virtual void pad50(); virtual void pad51();
	virtual void pad52(); virtual void pad53(); virtual void pad54(); virtual void pad55();
	virtual void pad56(); virtual void pad57(); virtual void pad58(); virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);
};
extern GameWindowManager *TheWindowManager;
class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;
void __cdecl GadgetStaticTextSetText(GameWindow *win, UnicodeString text);
void __cdecl GadgetProgressBarSetProgress(GameWindow *win, int progress);
extern "C" float kF7C;
class Rva0053E17E
{
public:
	void rva0053E17E(unsigned int total, float frac);
private:
	char m_pad[0x7C];
	int m_7C;
};
void Rva0053E17E::rva0053E17E(unsigned int total, float frac)
{
	UnicodeString text;
	static unsigned int s_text = TheNameKeyGenerator->nameToKey("ControlBar.wnd:OCLTimerStaticText");
	GameWindow *textWin = TheWindowManager->winGetWindowFromId(0, (Int)s_text);
	static unsigned int s_bar = TheNameKeyGenerator->nameToKey("ControlBar.wnd:OCLTimerProgressBar");
	GameWindow *barWin = TheWindowManager->winGetWindowFromId(0, (Int)s_bar);
	unsigned int minutes = total / 60;
	int seconds = (int)(total - minutes * 60);
	text.format(TheGameText->slot44(seconds >= 10 ? "CONTROLBAR:OCLTimerDesc" : "CONTROLBAR:OCLTimerDescWithPadding", 0), (int)minutes, seconds);
	GadgetStaticTextSetText(textWin, text);
	GadgetProgressBarSetProgress(barWin, (int)(frac * kF7C));
	m_7C = (int)total;
}
