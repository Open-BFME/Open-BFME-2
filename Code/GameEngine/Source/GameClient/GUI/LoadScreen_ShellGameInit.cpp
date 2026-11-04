// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// platformsdk
// ?init@Rva00355DC5@@UAEXPAVGameInfo@@@Z @0x00356541 455B: Zero Hour's
// ShellGameLoadScreen::init (LoadScreen.cpp), vslot 2 of vtable 0x00814E74
// (class of ??1Rva00355DC5@@UAE@XZ, so the class keeps its address name).
// Target evidence: the ShellGameLoadScreen.wnd literals (ProgressLoad,
// StaticTextLegal, TitleScreen, FadeWholeScreen), m_win +8 and m_progressBar
// +0x10 as in LoadScreenUpdates' view, the wait loop calling LoadScreen::update
// 0x00355FF9 with Sleep(100) for 3000ms, and the LOD byte getter 0x002026C7
// in place of didMemPass. BFME2's winCreateFromScript (TheWindowManager slot
// 31) takes two more pointer arguments, passed null here; the donor's
// function-static firstLoad (TRUE) is data at 0x009BFAA4. BFME2 also runs
// the FadeWholeScreen transition in reverse once the title image is set.
#include <windows.h>
#include "ascii_string.h"

class GameWindow;
class GameInfo;
class Image;
class NameKeyGenerator;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../../Include/GameClient/Bfme2GameWindow.h"

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString groupName);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva002026C7ByteField
{
public:
	unsigned char get() const;
};

class GameLODManager;
extern GameLODManager *TheGameLODManager;

#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

void GadgetProgressBarSetProgress(GameWindow *g, int progress);

class LoadScreen
{
public:
	virtual void update(int percent);
};

class ProgressIndicator
{
public:
	virtual ~ProgressIndicator() throw();
	ProgressIndicator *m_next; // +0x04
};

class Rva00355D66 : public ProgressIndicator
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
	GameWindow *m_progressBar; // +0x10
};

void Rva00355DC5::init(GameInfo *game)
{
	static int firstLoad = 1;
	GameWindow *win = 0;
	DWORD showTime = 0;
	m_win = TheWindowManager->winCreateFromScript(AsciiString("Menus/ShellGameLoadScreen.wnd"), 0, 0);
	m_win->winHide(false);
	m_win->winBringToTop();
	m_progressBar = TheWindowManager->winGetWindowFromId(m_win, TheNameKeyGenerator->nameToKey(AsciiString("ShellGameLoadScreen.wnd:ProgressLoad")));
	GadgetProgressBarSetProgress(m_progressBar, 0);
	m_progressBar->winHide(true);
	if (m_win && firstLoad && TheGameLODManager && ((Rva002026C7ByteField *)TheGameLODManager)->get()) {
		m_win->winSetEnabledImage(0, TheMappedImageCollection->findImageByName(AsciiString("TitleScreen")));
		TheTransitionHandler->reverse(AsciiString("FadeWholeScreen"));
		TheWritableGlobalData->field0D36 = false;
		win = TheWindowManager->winGetWindowFromId(m_win, TheNameKeyGenerator->nameToKey(AsciiString("ShellGameLoadScreen.wnd:StaticTextLegal")));
		if (win)
			win->winHide(false);
		firstLoad = 0;
		showTime = timeGetTime();
		while (showTime + 3000 > timeGetTime()) {
			((LoadScreen *)this)->LoadScreen::update(0);
			Sleep(100);
		}
	}
	m_progressBar->winHide(false);
}
