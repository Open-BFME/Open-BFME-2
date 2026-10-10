// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??1AptLoadScreen@@UAE@XZ
// retail 0x0043A396..0x0043A568 (466 bytes), the AptLoadScreen destructor.
//
// Target facts: it installs the AptLoadScreen vftable 0x00C3D50C (the one the
// rowed constructor 0x0043AE44 installs), shuts the +0x10 window layout down
// through its slot 3 and frees it with a destroying call through slot 1 plus
// the global operator delete (0x0002FD60), tears the +0x18 map preview down
// (rowed 0x0057D5E5), drops the "GameLoading:PlayerColor:%d" handlers and the
// "UIClip/Level/%d" and "UIClip/Fellowship/%d" clips for slots 0..7 and the
// "GameLoadingType" handler, restores the Apt player (0x00222F55, slot 19)
// and the audio (TheAudio slot 35), sets "GUI:Level" from the game text, runs
// the "MainMenuToSubMenu" transition backwards (0x005DC345), clears the
// instance global 0x00E0330C, then destroys the preview member (rowed
// 0x0057E3DB) and the window base (rowed 0x00355D66). WorldBuilder 0x0129F700
// names the destructor and its strings (AptLoadScreen.cpp).
//
// Structural inference: the class views below are TU-scoped and declare only
// what this body touches; member and slot names other than the WorldBuilder
// and ledger ones are not claimed as original spellings.
#include "ascii_string.h"
#include "unicode_string.h"

// The window base (rowed destructor 0x00355D66).
class Rva00355D66
{
public:
	virtual ~Rva00355D66();
protected:
	void *m_next;		// +0x04
	void *m_win;		// +0x08
	bool m_flag;		// +0x0C
};

// The embedded map preview's class, by its rowed destructor 0x0057E3DB.
class Rva0057E3DB
{
public:
	virtual ~Rva0057E3DB();
private:
	unsigned char m_unknown04[0x6C];
};

class AptMapPreview
{
public:
	void rva0057D5E5();	// preview teardown
};

// The window layout at +0x10: slot 1 destroys, slot 3 shuts it down.
class Rva0043A396Layout
{
public:
	virtual void slot00();
	virtual ~Rva0043A396Layout();
	virtual void slot08();
	virtual void shutdown(bool);
};

class Rva002244CA
{
public:
	int rva002244CA(const AsciiString *);
};
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *);
};
class Rva00222A8BTarget
{
public:
	void rva00222F55(bool);
};

template <int N> struct LoadSlotTag;
template <int N> class LoadSlots : public LoadSlots<N - 1>
{
public:
	virtual void gap(LoadSlotTag<N> *);
};
template <> class LoadSlots<0>
{
};
class LoadPlayerView : public LoadSlots<19>
{
public:
	virtual void show(int);			// slot 19
};
class LoadAudioView : public LoadSlots<35>
{
public:
	virtual void restore(int, bool, bool);	// slot 35
};
class LoadTextView : public LoadSlots<15>
{
public:
	virtual UnicodeString fetch(const char *, bool *);	// slot 15
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class AudioManager;
extern AudioManager *TheAudio;
class GameTextInterface;
extern GameTextInterface *TheGameText;
class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern int g_Va00E0330C;

// Only the destructor slot is declared, as in the constructor's unit
// (AptLoadScreenCtor.cpp): the vftable this body stores is then the same
// COMDAT copy that unit emits. Retail's vftable 0x00C3D50C has six slots;
// the other five are rowed elsewhere under their own names.
class AptLoadScreen : public Rva00355D66
{
public:
	virtual ~AptLoadScreen();
private:
	Rva0043A396Layout *m_layout;	// +0x10
	void *m_owner;			// +0x14
	Rva0057E3DB m_mapPreview;	// +0x18
	int m_88, m_level, m_90[8], m_ids[8];
	bool m_D0;
};

AptLoadScreen::~AptLoadScreen()
{
	m_layout->shutdown(false);
	::delete m_layout;
	m_layout = 0;
	reinterpret_cast<AptMapPreview *>(&m_mapPreview)->rva0057D5E5();
	AsciiString colorName;
	AsciiString clipName;
	for (int i = 0; i < 8; ++i)
	{
		colorName.format("GameLoading:PlayerColor:%d", i);
		reinterpret_cast<Rva002244CA *>(g_bfmeAptWindowManager)->rva002244CA(&colorName);
		clipName.format("UIClip/Level/%d", i);
		reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&clipName);
		clipName.format("UIClip/Fellowship/%d", i);
		reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&clipName);
	}
	{
		AsciiString typeName("GameLoadingType");
		reinterpret_cast<Rva002244CA *>(g_bfmeAptWindowManager)->rva002244CA(&typeName);
	}
	reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva00222F55(false);
	reinterpret_cast<LoadPlayerView *>(g_bfmeAptWindowManager)->show(1);
	reinterpret_cast<LoadAudioView *>(TheAudio)->restore(2, true, false);
	{
		AsciiString levelName("GUI:Level");
		g_bfmeAptWindowManager->bfmeSetText(levelName,
			reinterpret_cast<LoadTextView *>(TheGameText)->fetch("GUI:Level", 0), false);
	}
	TheTransitionHandler->reverse(AsciiString("MainMenuToSubMenu"));
	g_Va00E0330C = 0;
}
