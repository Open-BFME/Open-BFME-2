// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// BFME2's online quick match screen Apt callbacks, 0x005BA344 onward, and
// the login screen's CancelLogin, bound by these names
// ("AptOnline::OnlineQuickMatch::StartSimple" ...) as member pointers by
// the screens' registrations; that binding is their only reference. The
// scope and classes are named for the strings. "AptOnlineQuickMatch::
// InitGadgets" is bound by the same registration on the same object as
// the "AptOnline::OnlineQuickMatch::" callbacks, so it joins that class.

// Rva00516E92Enable.cpp's 0x00516E92.
void Rva00516E92Enable();

#include <string.h>

#include "ascii_string.h"
#include "../../../../../Include/GameClient/Bfme2GameWindow.h"
#include "../../../../../Include/GameClient/Image.h"

#include "../../../../../Include/GameNetwork/MultiplayerColorDefinition.h"
#include "../../../../../Include/GameNetwork/MultiplayerSettingsClass.h"
extern MultiplayerSettings *TheMultiplayerSettings;
#include "../../../../../Include/Common/QuickMatchPreferencesClass.h"
#include "../../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
class Rva00323619 {public:void rva00323642();void rva00323619(int);};
class Rva003235B8 {public:int rva003235B8(const Image*,int,int,int);};
class Rva003236A0 {public:void rva003236A0(int,int);};
class BfmeThing925D {public:void bfmeGo925D(void*);};
void GadgetComboBoxReset(GameWindow *comboBox);

// Native 7B719 stores the non-owning window pointer and returns this.
// Use the existing window-wrapper constructor owner for that exact operation;
// the quick-match member's original spelling remains its named callback view.
class OnlineQuickMatchWindowRef { public: GameWindow *m_window; };
class Rva00323674 { public: Rva00323674(GameWindow *); };

// Native 2C5761 is the rowed thiscall GameWindowManager::rva002C5761 (it
// ignores ECX and returns with RET4); the caller loads the manager.
#include "../../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

namespace AptOnline
{
class OnlineQuickMatch
{
public:
	void StartSimple(const char *unused);
	void PlayGame(const char *unused);
	void OnFoundMovieDone(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

	// Unrowed 0x005BA803, pinned by address.
	void rva005BA803();

private:
	unsigned char m_pad00[0x58];
	GameWindow *m_window; // +0x58
	unsigned char m_pad5c[0x60 - 0x5C];
	int m_state; // +0x60
	unsigned char m_pad64[0x79 - 0x64];
	bool m_simple; // +0x79
	bool m_foundMovie; // +0x7A
	unsigned char m_pad7b[0x7C - 0x7B];
	unsigned int m_gadgets; // +0x7C, which gadgets are linked
	OnlineQuickMatchWindowRef m_color; // +0x80
	GameWindow *m_numPlayers; // +0x84
	GameWindow *m_side; // +0x88
	GameWindow *m_connectionSpeed; // +0x8C
	GameWindow *m_ladder; // +0x90
};

class Login
{
public:
	void CancelLogin(const char *unused);
};
}

// Retail 0x005BA344, 7 bytes: "AptOnline::OnlineQuickMatch::StartSimple".
void AptOnline::OnlineQuickMatch::StartSimple(const char *unused)
{
	m_simple = true;
}

// Retail 0x005BA34B, 14 bytes: "AptOnline::OnlineQuickMatch::PlayGame".
void AptOnline::OnlineQuickMatch::PlayGame(const char *unused)
{
	m_simple = true;
	m_state = 1;
}

// Retail 0x005BA359, 20 bytes: "AptOnline::OnlineQuickMatch::OnFoundMovieDone".
void AptOnline::OnlineQuickMatch::OnFoundMovieDone(const char *unused)
{
	m_state = 2;
	if (m_foundMovie)
		m_foundMovie = false;
}

// Retail 0x005BA94A, 225 bytes: "AptOnlineQuickMatch::InitGadgets" keeps
// the screen's gadgets (emptying its combo boxes), records each as linked,
// and has the window manager rework the screen's window.
void AptOnline::OnlineQuickMatch::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "OnlineQuickMatch::Color") == 0)
	{
		((Rva00323674 *)&m_color)->Rva00323674::Rva00323674(window);
		rva005BA803();
		m_gadgets |= 0x01;
	}
	else if (strcmp(name, "OnlineQuickMatch::NumOfPlayers") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x04;
		m_numPlayers = window;
	}
	else if (strcmp(name, "OnlineQuickMatch::Side") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x20;
		m_side = window;
	}
	else if (strcmp(name, "OnlineQuickMatch::ConnectionSpeed") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x40;
		m_connectionSpeed = window;
	}
	else if (strcmp(name, "OnlineQuickMatch::Ladder") == 0)
	{
		GadgetComboBoxReset(window);
		m_gadgets |= 0x80;
		m_ladder = window;
	}
	TheWindowManager->rva002C5761(m_window);
}

// Retail 0x0056DCB7, 8 bytes: "AptOnline::Login::CancelLogin".
void AptOnline::Login::CancelLogin(const char *unused)
{
	Rva00516E92Enable();
}

// The matched named InitGadgets5BA94A binds the Color window then calls
// 5BA803. Native299B RET0 proves method on the same OnlineQuickMatch object.
// Each helper's existing one-window storage view independently agrees with
// the color reference prefix. These are direct provider calls, no PMF alias.
void AptOnline::OnlineQuickMatch::rva005BA803() {
 int *count=&TheMultiplayerSettings->m_numColors;
 if(!*count)*count=TheMultiplayerSettings->slot38;
 int colors=*count;
 OnlineQuickMatchWindowRef *combo=&m_color;
 ((Rva00323619*)combo)->rva00323642();
 int width,height;combo->m_window->winGetSize(&width,&height);
 int screenWidth=TheWritableGlobalData->m_xResolution;
 int boxWidth=((width-(screenWidth*32)/1024)*1024)/screenWidth;
 for(int i=0;i<colors;++i) {
  MultiplayerColorDefinition *color=TheMultiplayerSettings->getColor(i);
  if(color) {
   static const Image *whiteBox=TheMappedImageCollection->findImageByName(AsciiString("AptWhiteBox"));
   int entry=((Rva003235B8*)combo)->rva003235B8(whiteBox,boxWidth,20,color->m_color);
   ((Rva003236A0*)combo)->rva003236A0(entry,i);
  }
 }
 ((Rva00323619*)combo)->rva00323619(colors*30);
 ((BfmeThing925D*)combo)->bfmeGo925D((void*)((QuickMatchPreferences*)((char*)this+0x64))->getColor());
}
