// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Clean donor: reference/open-bfme-1 @575ba2b04743f190f069805fbdc59936123c45da
// game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarInitSpecialPowershortcutBar.cpp.
// Donor names the initialization workflow. WB C30790 keeps its literals and calls
// but exposes no name; existing GameLogic/Player refresh callers prove ControlBar.
// Retain the established address-derived method owner. Target31BAC3..31BD55 RET4
// independently proves five windowsA8/parentsBC/countD0/layoutD4/parentD8;
// Player template34 with name144/count148; window-manager slots80/F0.
// Target uses StringBase::isEmpty and pointer-format overload. Qualified global
// delete reproduces virtual destructor flag0 then global free rather than flag1.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { MAX_SPECIAL_POWER_SHORTCUTS = 5 };
enum { WIN_STATUS_USE_OVERLAY_STATES = 0x00200000 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

// Target string text access is inlined: one Header pointer and text at+8,
// with the compiler empty literal when null. The emptiness test below instead
// calls the existing StringBase<char>::isEmpty worker as witnessed in retail.

static inline const char *inlineStr(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text ? text + 8 : "";
}


class GameWindow
{
public:
	UnsignedInt winSetStatus(UnsignedInt status);
};

// BFME makes WindowLayout virtual: slot 1 is the deleting destructor, slot 4
// hide(Bool), slot 8 destroyWindows (ControlBarPrintPositions.cpp, Shell_doPush.cpp).
class WindowLayout
{
public:
	virtual void runInit(void *) = 0;
	virtual ~WindowLayout();
	virtual void runUpdate(void *) = 0;
	virtual void runShutdown(void *) = 0;
	virtual void hide(Bool hide) = 0;
	virtual void bringForward() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void destroyWindows() = 0;
};

class GameWindowManager
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00C();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01C();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02C();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03C();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04C();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05C();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06C();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07C();
	virtual WindowLayout *winCreateLayout(AsciiString filename); // target80
	virtual void slot084();
	virtual void slot088();
	virtual void slot08C();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09C();
	virtual void slot0A0();
	virtual void slot0A4();
	virtual void slot0A8();
	virtual void slot0AC();
	virtual void slot0B0();
	virtual void slot0B4();
	virtual void slot0B8();
	virtual void slot0BC();
	virtual void slot0C0();
	virtual void slot0C4();
	virtual void slot0C8();
	virtual void slot0CC();
	virtual void slot0D0();
	virtual void slot0D4();
	virtual void slot0D8();
	virtual void slot0DC();
	virtual void slot0E0();
	virtual void slot0E4();
	virtual void slot0E8();
	virtual void slot0EC();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent,NameKeyType id); // targetF0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	const AsciiString &getSpecialPowerShortcutWinName() const { return m_specialPowerShortcutWinName; }
	Int getSpecialPowerShortcutButtonCount() const { return m_specialPowerShortcutButtonCount; }

private:
	char m_unmodelled00[0x144];
	AsciiString m_specialPowerShortcutWinName;     // target+0x144
	Int m_specialPowerShortcutButtonCount;         // target+0x148
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Bool isLocalPlayer() const;
	Bool isPlayerActive() const;

private:
	char m_unmodelled00[0x34];
	const PlayerTemplate *m_playerTemplate;        // target+0x34
};

class ControlBar
{
public:
	void rva0031BAC3(Player *player);

private:
	char m_unmodelled00[0xA8];
	GameWindow *m_specialPowerShortcutButtons[MAX_SPECIAL_POWER_SHORTCUTS];        // target+0xA8
	GameWindow *m_specialPowerShortcutButtonParents[MAX_SPECIAL_POWER_SHORTCUTS];  // target+0xBC
	Int m_currentlyUsedSpecialPowersButtons;                                       // target+0xD0
	WindowLayout *m_specialPowerLayout;                                            // target+0xD4
	GameWindow *m_specialPowerShortcutParent;                                      // target+0xD8
};

void ControlBar::rva0031BAC3(Player *player)
{
	for (Int i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; ++i)
	{
		m_specialPowerShortcutButtonParents[i] = 0;
		m_specialPowerShortcutButtons[i] = 0;
	}

	if (m_specialPowerLayout)
	{
		m_specialPowerLayout->destroyWindows();
		::delete m_specialPowerLayout;
		m_specialPowerLayout = 0;
	}
	m_specialPowerShortcutParent = 0;
	m_currentlyUsedSpecialPowersButtons = 0;
	const PlayerTemplate *pt = player->getPlayerTemplate();

	if (!pt || !player->isLocalPlayer()
			|| pt->getSpecialPowerShortcutButtonCount() == 0
			|| ((const StringBase<char> *)&pt->getSpecialPowerShortcutWinName())->isEmpty()
			|| !player->isPlayerActive())
		return;
	m_currentlyUsedSpecialPowersButtons = pt->getSpecialPowerShortcutButtonCount();
	AsciiString layoutName, tempName, windowName, parentName;
	layoutName = pt->getSpecialPowerShortcutWinName();
	m_specialPowerLayout = TheWindowManager->winCreateLayout(layoutName);
	m_specialPowerLayout->hide(true);

	tempName = layoutName;
	tempName.concat(":GenPowersShortcutBarParent");
	NameKeyType id = TheNameKeyGenerator->nameToKey(tempName);
	m_specialPowerShortcutParent = TheWindowManager->winGetWindowFromId(0, id);

	tempName = layoutName;
	tempName.concat(":ButtonCommand%d");
	parentName = layoutName;
	parentName.concat(":ButtonParent%d");
	Int count = pt->getSpecialPowerShortcutButtonCount();
	m_currentlyUsedSpecialPowersButtons = count < MAX_SPECIAL_POWER_SHORTCUTS ? count : MAX_SPECIAL_POWER_SHORTCUTS;
	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; i++)
	{
		windowName.format(&tempName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		m_specialPowerShortcutButtons[i] =
			TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
		m_specialPowerShortcutButtons[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);

		windowName.format(&parentName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		m_specialPowerShortcutButtonParents[i] =
			TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
	}
}
