// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfme2_ascii
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

class GameWindow
{
public:
	Bool winIsHidden(void);
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
};

class PlayerTemplate
{
	unsigned char m_unreconstructed_00[0x140];
	AsciiString m_specialPowerShortcutCommandSet;

public:
	const AsciiString &getSpecialPowerShortcutCommandSet() const
	{
		return m_specialPowerShortcutCommandSet;
	}
};

class Player
{
	unsigned char m_unreconstructed_00[0x34];
	PlayerTemplate *m_playerTemplate;

public:
	PlayerTemplate *getPlayerTemplate() const
	{
		return m_playerTemplate;
	}
	Bool isLocalPlayer(void) const;
	Bool hasScience(ScienceType science) const;
	Bool hasAnyRequiredSciences(const _STL::vector<ScienceType> &) const;
};

class Rva0029FCB4 { public: _STL::vector<ScienceType> rva0029FCB4(); };
class SpecialPowerTemplate {};

typedef _STL::vector<ScienceType> ScienceVec;

class CommandButton
{
	unsigned char m_unreconstructed_00[0x14];
	Int m_command;
	CommandButton *m_next;
	UnsignedInt m_options;
	unsigned char m_unreconstructed_1C[0x24];
	const SpecialPowerTemplate *m_specialPower;
	unsigned char m_unreconstructed_38[0x5C];
	ScienceVec m_science;

public:
	Int getCommandType(void) const
	{
		return m_command;
	}
	CommandButton *getNext(void) const
	{
		return m_next;
	}
	const SpecialPowerTemplate *getSpecialPowerTemplate(void) const
	{
		return m_specialPower;
	}
	const ScienceVec &getScienceVec(void) const
	{
		return m_science;
	}
	signed char getOptions(void) const
	{
		return static_cast<signed char>(m_options);
	}
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class Rva0035B7D9
{
public:
	void rva0035B7D9(Rva0035B7D9 *source, bool notify);
};

class ControlBar
{
	unsigned char m_unreconstructed_00[0x2C];
	CommandButton *m_commandButtons;
	unsigned char m_unreconstructed_2C[0x18];
	GameWindow *m_contextParent;
	unsigned char m_unreconstructed_38[0x5C];
	GameWindow *m_specialPowerShortcutButtons[5];
	GameWindow *m_specialPowerShortcutButtonParents[5];
	Int m_currentlyUsedSpecialPowersButtons;
	unsigned char m_unreconstructed_F8[4];
	GameWindow *m_specialPowerShortcutParent;

public:

	void rva0031DAF8(void);

public:
	void rva0031B210(void);
protected:
	void populateSpecialPowerShortcut(Player *player);

public:
	void setControlCommand(GameWindow *window, const CommandButton *command);
};

extern ControlBar *TheControlBar;
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class Rva0031AF54 { public: void rva0031AF54(bool); };

void GadgetButtonSetAltSound(GameWindow *window, AsciiString sound);

void ControlBar::populateSpecialPowerShortcut(Player *player)
{
	const CommandSet *commandSet;
	Int i;
	Int currentButton = 0;
	const CommandButton *commandButton;
	if (!player || !player->getPlayerTemplate()
			|| !player->isLocalPlayer() || m_currentlyUsedSpecialPowersButtons == 0
			|| !m_specialPowerShortcutButtons || !m_specialPowerShortcutButtonParents)
		return;

	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i)
	{
		if (m_specialPowerShortcutButtons[i])
			m_specialPowerShortcutButtons[i]->winHide(true);
		if (m_specialPowerShortcutButtonParents[i])
			m_specialPowerShortcutButtonParents[i]->winHide(true);
	}

	PlayerTemplate *playerTemplate=player->getPlayerTemplate();
	if ((playerTemplate ? playerTemplate : playerTemplate)->getSpecialPowerShortcutCommandSet().isEmpty())
		return;
	commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&playerTemplate->getSpecialPowerShortcutCommandSet());
	if (!commandSet)
		return;

	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i)
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
					for (CommandButton *purchase = m_commandButtons;
						purchase; purchase = purchase->getNext())
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

		m_specialPowerShortcutButtons[currentButton]->winHide(false);
		m_specialPowerShortcutButtonParents[currentButton]->winHide(false);
		m_specialPowerShortcutButtons[currentButton]->winEnable(true);
		m_specialPowerShortcutButtonParents[currentButton]->winEnable(true);

		setControlCommand(m_specialPowerShortcutButtons[currentButton], commandButton);
		GadgetButtonSetAltSound(m_specialPowerShortcutButtons[currentButton],
			AsciiString("GUIGenShortcutClick"));
		++currentButton;
	}

	if (m_contextParent && !m_contextParent->winIsHidden()
			&& m_specialPowerShortcutParent->winIsHidden())
	{
		rva0031DAF8();
		((Rva0031AF54 *)this)->rva0031AF54(true);
	}
	rva0031B210();
}
