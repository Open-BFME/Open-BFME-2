// ?init@Rva00355DC5@@UAEXPAVGameInfo@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?init@Rva00355DC5@@UAEXPAVGameInfo@@@Z @0x00356541 455B
// vslot 2 (offset 0x8) of vtable 0x00814E74 (class of ??1Rva00355DC5@@UAE@XZ).
// Evidence: ShellGameLoadScreen strings (Menus/ShellGameLoadScreen.wnd,
// ProgressLoad, StaticTextLegal, TitleScreen, FadeWholeScreen), m_win +8 and
// m_progressBar +0x10 layout matching LoadScreenUpdates ShellGame view,
// wait loop calling pinned LoadScreen::update 0x00355FF9 with Sleep(100) for
// 3000ms, firstLoad global 0x009BFAA4, LOD byte getter 0x002026C7.
#include "ascii_string.h"

class GameWindow;
class GameInfo;
class Image;
class NameKeyGenerator;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class GameWindow
{
public:
	int winHide(bool hide);
	int rva0031475A();
	int winSetEnabledImage(int index, const Image *image);
};

class GameWindowManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual GameWindow *winCreateFromScript(AsciiString file); // +0x7c slot31
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual GameWindow *winGetWindowFromId(GameWindow *win, int id); // +0xf0 slot60
};

extern GameWindowManager *TheWindowManager;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *g_00DFF078;

class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString groupName);
};

class AudioManager;
extern AudioManager *TheAudio;

class Rva002026C7ByteField
{
public:
	unsigned char get() const;
};

class GameLODManager;
extern GameLODManager *TheGameLODManager;

class GlobalData
{
public:
	unsigned char m_pad[0xD36];
	bool m_breakTheMovie;
};
extern GlobalData *TheWritableGlobalData;

extern int g_00DBFAA4;

void GadgetProgressBarSetProgress(GameWindow *g, int progress);

class LoadScreen
{
public:
	virtual void update(int percent);
};

extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long ms);

class Gen_004902A0
{
public:
	virtual ~Gen_004902A0();
	Gen_004902A0 *m_next;
};

class Rva00355D66 : public Gen_004902A0
{
public:
	virtual ~Rva00355D66();
protected:
	GameWindow *m_win;
private:
	bool m_flag;
};

class Rva00355DC5 : public Rva00355D66
{
public:
	virtual void init(GameInfo *game);
private:
	GameWindow *m_progressBar;
};

// ?init@Rva00355DC5@@UAEXPAVGameInfo@@@Z present-unmatched
void Rva00355DC5::init(GameInfo *game)
{
	GameWindow *win = 0;
	unsigned int showTime = 0;
	m_win = TheWindowManager->winCreateFromScript(AsciiString("Menus/ShellGameLoadScreen.wnd"));
	m_win->winHide(false);
	m_win->rva0031475A();
	m_progressBar = TheWindowManager->winGetWindowFromId(m_win, TheNameKeyGenerator->nameToKey(AsciiString("ShellGameLoadScreen.wnd:ProgressLoad")));
	GadgetProgressBarSetProgress(m_progressBar, 0);
	m_progressBar->winHide(true);
	if (m_win && g_00DBFAA4 && TheGameLODManager && ((Rva002026C7ByteField *)TheGameLODManager)->get()) {
		m_win->winSetEnabledImage(0, g_00DFF078->findImageByName(AsciiString("TitleScreen")));
		((GameWindowTransitionsHandler *)TheAudio)->reverse(AsciiString("FadeWholeScreen"));
		TheWritableGlobalData->m_breakTheMovie = false;
		win = TheWindowManager->winGetWindowFromId(m_win, TheNameKeyGenerator->nameToKey(AsciiString("ShellGameLoadScreen.wnd:StaticTextLegal")));
		if (win)
			win->winHide(false);
		g_00DBFAA4 = 0;
		showTime = timeGetTime();
		while (showTime + 3000 > timeGetTime()) {
			((LoadScreen *)this)->LoadScreen::update(0);
			Sleep(100);
		}
	}
	m_progressBar->winHide(false);
}
