// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Clean donor: reference/open-bfme-1 @575ba2b04743f190f069805fbdc59936123c45da
// game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarInitSpecialPowershortcutBar.cpp.
// Donor names the initialization workflow. WB C30790 keeps its literals and calls
// but exposes no name; existing GameLogic/Player refresh callers prove ControlBar.
// Retain the established address-derived method owner. Target31BAC3..31BD55 RET4
// independently proves five windowsA8/parentsBC/countD0/layoutD4/parentD8;
// Player template34 with name144/count148; window-manager slots80/F0.
// Target uses StringBase::isEmpty and pointer-format overload. Qualified global
// delete reproduces virtual destructor flag0 then global free rather than flag1.
typedef bool Bool;
#include "../../../../Include/Common/NameKeyGenerator.h"
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { MAX_SPECIAL_POWER_SHORTCUTS = 5 };
enum
{
	WIN_STATUS_RVA0031C83D_200 = 0x00000200,
	WIN_STATUS_RVA0031C83D_10000 = 0x00010000,
	WIN_STATUS_RVA0031C83D_20000 = 0x00020000,
	WIN_STATUS_USE_OVERLAY_STATES = 0x00200000,
	WIN_STATUS_RVA0031C83D_20000000 = 0x20000000
};
enum NameKeyType { NAMEKEY_INVALID = 0 };

// Target string text access is inlined: one Header pointer and text at+8,
// with the compiler empty literal when null. The emptiness test below instead
// calls the existing StringBase<char>::isEmpty worker as witnessed in retail.

static inline const char *inlineStr(const AsciiString &asciiString)
{
	const char *text = *reinterpret_cast<const char *const *>(&asciiString);
	return text ? text + 8 : "";
}


class GadgetCreateView;
class Image;
class GameWindow;
class WinInstanceData;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
#include "../../../../Include/GameClient/Bfme2GameWindow.h"

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

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

#include "../../../../Include/Common/PlayerTemplate.h"

#include "../../../../Include/Common/Player.h"

#include "ControlBarMemberTypes.h"
enum CommandButtonMappedBorderType
{
    COMMAND_BUTTON_BORDER_NONE,
    COMMAND_BUTTON_BORDER_BUILD,
    COMMAND_BUTTON_BORDER_UPGRADE,
    COMMAND_BUTTON_BORDER_ACTION,
    COMMAND_BUTTON_BORDER_SYSTEM,
    COMMAND_BUTTON_BORDER_BFME5
};
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};
class CommandButton;
class CommandSet;
class INI;
class Object;
struct Coord3D;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class Drawable;
class vector;
struct PlayerAITypeEntry;
class Rva000AD6F4;
#include "../../../../Include/GameClient/ControlBar.h"

void ControlBar::rva0031BAC3(Player *player)
{
	for (Int i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; ++i)
	{
		fieldBC[i] = 0;
		fieldA8[i] = 0;
	}

	if (fieldD4)
	{
		fieldD4->destroyWindows();
		::delete fieldD4;
		fieldD4 = 0;
	}
	fieldD8 = 0;
	fieldD0 = 0;
	const PlayerTemplate *pt = player->getPlayerTemplate();

	if (!pt || !player->isLocalPlayer()
			|| pt->getSpecialPowerShortcutButtonCount() == 0
			|| ((const StringBase<char> *)&pt->getSpecialPowerShortcutWinName())->isEmpty()
			|| !player->isPlayerActive())
		return;
	fieldD0 = pt->getSpecialPowerShortcutButtonCount();
	AsciiString layoutName, tempName, windowName, parentName;
	layoutName = pt->getSpecialPowerShortcutWinName();
	fieldD4 = TheWindowManager->winCreateLayout(layoutName);
	fieldD4->hide(true);

	tempName = layoutName;
	reinterpret_cast<StringBase<char> *>(&tempName)->concat(":GenPowersShortcutBarParent");
	NameKeyType id = TheNameKeyGenerator->nameToKey(tempName);
	fieldD8 = TheWindowManager->winGetWindowFromId(0, id);

	tempName = layoutName;
	reinterpret_cast<StringBase<char> *>(&tempName)->concat(":ButtonCommand%d");
	parentName = layoutName;
	reinterpret_cast<StringBase<char> *>(&parentName)->concat(":ButtonParent%d");
	Int count = pt->getSpecialPowerShortcutButtonCount();
	fieldD0 = count < MAX_SPECIAL_POWER_SHORTCUTS ? count : MAX_SPECIAL_POWER_SHORTCUTS;
	for (i = 0; i < fieldD0; i++)
	{
		windowName.format(&tempName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		fieldA8[i] =
			TheWindowManager->winGetWindowFromId(fieldD8, id);
		fieldA8[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);

		windowName.format(&parentName, i + 1);
		id = TheNameKeyGenerator->nameToKey(inlineStr(windowName));
		fieldBC[i] =
			TheWindowManager->winGetWindowFromId(fieldD8, id);
	}
}
