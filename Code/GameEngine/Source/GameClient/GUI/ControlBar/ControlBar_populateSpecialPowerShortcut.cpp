// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// BFME1 semantic donor: ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_populateSpecialPowerShortcut.cpp.
// WB 0x00C30C60 names the BFME2 method. Target boundary 0x0031D85D..0x0031DAF8
// is 667 bytes; every callee is resolved:
// 31B210 / 31DAF8 / 35B7D9 now have rowed providers and the 31B641 call is
// the established ControlBar::setControlCommand owner rather than a new pin.
// Retail retains the PlayerTemplate base in ESI through StringBase::isEmpty
// and adds 0x140 in place for the command-set lookup: the name's address is
// passed straight into findCommandSet's call (a pointer local for it is
// computed into EAX instead).
typedef bool Bool;
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { FALSE = 0, TRUE = 1 };

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum
{
	GUI_COMMAND_PURCHASE_SCIENCE = 0x19,
	NEED_SPECIAL_POWER_SCIENCE = 0x00000080
};

#include "ascii_string.h"
namespace _STL { void __cdecl free(void *); }
#include <vector>

// Match the established ScienceType vector cleanup's actual game allocator:
// _STL::free was only a pin spelling of this verified17-byte provider.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

class GadgetCreateView;
class Image;
class GameWindow;
class WinInstanceData;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
#include "../../../../Include/GameClient/Bfme2GameWindow.h"

class PlayerTemplate
{
public:
    const AsciiString &getSpecialPowerShortcutCommandSet() const { return m_specialPowerShortcutCommandSet; }
    const AsciiString &getSpecialPowerShortcutWinName() const { return m_specialPowerShortcutWinName; }
    int getSpecialPowerShortcutButtonCount() const { return m_specialPowerShortcutButtonCount; }
    const AsciiString &getBeaconTemplate() const { return m_beaconTemplate; }
    char m_pad00[0x138];
    AsciiString commandSet;
    char m_pad13C[4];
    AsciiString m_specialPowerShortcutCommandSet;
    AsciiString m_specialPowerShortcutWinName;
    int m_specialPowerShortcutButtonCount;
    char m_pad14C[0x17C - 0x14C];
    AsciiString m_beaconTemplate;
};

#include "../../../../Include/Common/Player.h"

class Rva0029FCB4 { public: _STL::vector<ScienceType> rva0029FCB4(); };
#include "../../../../Include/Common/SpecialPower.h"

typedef _STL::vector<ScienceType> ScienceVec;

class AsciiString;
class Image;
class SpecialPowerTemplate;
#include "../../../../Include/GameClient/CommandButton.h"

#include "../../../../Include/GameClient/CommandSet.h"

class Rva0035B7D9
{
public:
	void rva0035B7D9(Rva0035B7D9 *source, bool notify);
};

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
class INI;
class Object;
struct Coord3D;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class Drawable;
class WindowLayout;
struct PlayerAITypeEntry;
class Rva000AD6F4;
#include "../../../../Include/GameClient/ControlBar.h"

extern ControlBar *TheControlBar;
struct Rva0041534BIter;
#include "../../../../Include/GameClient/Rva00056F61.h"
#include "../../../../Include/Common/Rva0031D5F8.h"
class Rva0031AF54
{
public:
	void rva0031AF54(bool flag);
	char m_pad00[0x14];
	AnimateWindowManager *m_manager; // +0x14
	char m_pad18[0x90];
	GameWindow *m_list[10]; // +0xA8
	int m_count; // +0xD0
	char m_padD4[0x4];
	GameWindow *m_window; // +0xD8
};

void GadgetButtonSetAltSound(GameWindow *window, AsciiString sound);

void ControlBar::populateSpecialPowerShortcut(Player *player)
{
	const CommandSet *commandSet;
	Int i;
	Int currentButton = 0;
	const CommandButton *commandButton;
	if (!player || !player->getPlayerTemplate()
			|| !player->isLocalPlayer() || fieldD0 == 0
			|| !fieldA8 || !fieldBC)
		return;

	for (i = 0; i < fieldD0; ++i)
	{
		if (fieldA8[i])
			fieldA8[i]->winHide(true);
		if (fieldBC[i])
			fieldBC[i]->winHide(true);
	}

	const PlayerTemplate *playerTemplate=player->getPlayerTemplate();
	if ((playerTemplate ? playerTemplate : playerTemplate)->getSpecialPowerShortcutCommandSet().isEmpty())
		return;
	commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&playerTemplate->getSpecialPowerShortcutCommandSet());
	if (!commandSet)
		return;

	for (i = 0; i < fieldD0; ++i)
	{
		commandButton = commandSet->getCommandButton(i);
		if (!commandButton)
			continue;

		if (commandButton->getOptions() & NEED_SPECIAL_POWER_SCIENCE)
		{
			const SpecialPowerTemplate *power = commandButton->getSpecialPowerTemplate();
			if (power)
			{
                _STL::vector<ScienceType> required=((Rva0029FCB4 *)power)->rva0029FCB4();
                if (!required.empty()) {
				if (!player->hasAnyRequiredSciences(required))
					continue;

				Int bestIndex = -1;
				for (Int scienceIndex = 0;
					scienceIndex < commandButton->getScienceVec().size(); ++scienceIndex)
				{
					ScienceType science = commandButton->getScienceVec()[scienceIndex];
					if (player->hasScience(science))
						bestIndex = scienceIndex;
					else
						break;
				}

				if (bestIndex != -1)
				{
					ScienceType science = commandButton->getScienceVec()[bestIndex];
					for (CommandButton *purchase = field2C;
						purchase; purchase = purchase->friend_getNext())
					{
						if (purchase->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE
								&& !purchase->getScienceVec().empty()
								&& purchase->getScienceVec()[0] == science)
							((Rva0035B7D9 *)commandButton)->rva0035B7D9(
								(Rva0035B7D9 *)purchase, true);
					}
				}
                }
			}
		}

		fieldA8[currentButton]->winHide(false);
		fieldBC[currentButton]->winHide(false);
		fieldA8[currentButton]->winEnable(true);
		fieldBC[currentButton]->winEnable(true);

		setControlCommand(fieldA8[currentButton], commandButton);
		GadgetButtonSetAltSound(fieldA8[currentButton],
			AsciiString("GUIGenShortcutClick"));
		++currentButton;
	}

	if (field48[0] && !field48[0]->winIsHidden()
			&& fieldD8->winIsHidden())
	{
		showSpecialPowerShortcut();
		((Rva0031AF54 *)this)->rva0031AF54(true);
	}
	rva0031B210();
}
