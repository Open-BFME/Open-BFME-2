// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// CommandSet::getCommandButton, retail 0x00409EE8 (51 bytes), after Zero
// Hour's GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference): Zero Hour
// returns m_command[i]. BFME 2 (target evidence) first asks TheGameLogic for
// an override of slot i of the set named at CommandSet +0x10 through
// 0x00246F8E (a GameLogic map lookup keyed by name and slot that writes the
// button and returns true when found; its name is not established), and
// otherwise returns the button array at +0x14.
typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
class CommandButton;

class GameLogic
{
public:
	Bool rva00246F8E(const AsciiString &setName, Int slot, const CommandButton **button);
};
extern GameLogic *TheGameLogic;

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;
private:
	unsigned char m_pad00[0x10];
	AsciiString m_name; // +0x10
	const CommandButton *m_command[1]; // +0x14 (slot count not established)
};

//-------------------------------------------------------------------------------------------------
const CommandButton *CommandSet::getCommandButton(Int i) const
{
	const CommandButton *button;
	if (TheGameLogic && TheGameLogic->rva00246F8E(m_name, i, &button))
		return button;
	return m_command[i];
}
